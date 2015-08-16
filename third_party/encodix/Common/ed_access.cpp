/*******************************************************************************
  ed_access.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "ed_access.h"
#include <string.h>
extern "C" {
#include "ed_lib.h"
}

/*--------------------------------------------------------------------------
	Set the class name
--------------------------------------------------------------------------*/
void TEDString::Set (const char* newText)
{
	if (text != NULL) {
		delete [] text;
		text = NULL;
	}

	if (newText != NULL) {
		text = new char [strlen (newText)+1];
		strcpy (text, newText);
	}
}

#ifndef ED_NO_ACCESS_DEBUG
#define INDENT TEDAccessIndent(indent)
#define INDENTP(a) TEDAccessIndent(a)
class TEDAccessIndent {
	public:
		TEDAccessIndent (unsigned _indent): indent (_indent) {}
		unsigned indent;
};

ostream& operator<< (ostream& o, const TEDAccessIndent& k)
{
	unsigned i;
	for (i=0; i<k.indent; i++) o << "  ";
	return o;
}

#ifndef ED_NO_ACCESS_LOCATOR

/*--------------------------------------------------------------------------
	Prints the locator
--------------------------------------------------------------------------*/
static const char* ED_PRINT_LOCATOR (ostream& out, const TEDDataBase* db, const char* addIfNotEmpty)
{
	int offset;
	offset = db->GetLocatorOffset ();
	if (offset != ED_ACCESS_MISSING_LOCATOR) {
		out << "LOC:[" << offset << "," << db->GetLocatorLength () << "]" << addIfNotEmpty;
	}
	return "";
}
#else
#define ED_PRINT_LOCATOR(out,db,addIfNotEmpty) ""
#endif

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDClassReference::Print (ostream& out, bool explode, unsigned indent) const
{
	if (referenced == NULL) out << INDENT << "UNDEFINED" << endl;
	else {
		if (owned || explode) referenced->Print (out, explode, indent);
		else out << INDENT << "->" << referenced->GetClassName () << endl;
	}
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDClassStructuredElement::Print (ostream& out, bool explode, unsigned indent) const
{
	out << INDENT << fieldName;
	if (isOptional) out << " OPTIONAL";
	out << ":" << endl;
	fieldClass.Print (out, explode, indent+1);
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDClassStruct::Print (ostream& out, bool explode, unsigned indent) const
{
	unsigned i;
	out << INDENT << "struct " << className << " {" << endl;
	for (i=0; i<elements.Count (); i++) {elements [i].Print (out, explode, indent+1);}
	out << INDENT << "}" << endl;
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDClassUnion::Print (ostream& out, bool explode, unsigned indent) const
{
	unsigned i;
	out << INDENT << "union " << className << " {" << endl;
	for (i=0; i<elements.Count (); i++) {elements [i].Print (out, explode, indent+1);}
	out << INDENT << "}" << endl;
}


/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDClassBinary::Print (ostream& out, bool explode, unsigned indent) const
{
	ED_WARNING_REMOVER (explode);
	out << INDENT << className << " (binary, max " << maxBits << " bits, " << (isFixed? "fixed":"dynamic") << ")" << endl;
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDClassInteger::Print (ostream& out, bool explode, unsigned indent) const
{
	ED_WARNING_REMOVER (explode);
	out << INDENT << className << " (int, " << bitSize << " bits)" << endl;
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDClassEnumerated::Print (ostream& out, bool explode, unsigned indent) const
{
	ED_WARNING_REMOVER (explode);
	out << INDENT << className << " (int, " << bitSize << " bits) ENUMERATED" << endl;
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDClassSequence::Print (ostream& out, bool explode, unsigned indent) const
{
	out << INDENT << className << " array [" << (isFixed? "" : "0..") << maxItems << "] of:" << endl;
	sequencedClass.Print (out, explode, indent+1);
}

/*--------------------------------------------------------------------------
	CONSTRUCTOR
--------------------------------------------------------------------------*/
TEDDataStruct::TEDDataStruct (const TEDClassStruct* _itsClass): 
	itsClass (_itsClass), elements (NULL) 
{
	assert (itsClass);
	PrepareElements ();
	unsigned i;
	for (i=0; i<itsClass->Count (); i++) {
		if (!itsClass->GetFieldInfo (i).GetIsOptional ()) {
			SetElement (i, itsClass->GetFieldInfo (i).GetFieldClass ().NewInstance ());
		}
	}
}

/*--------------------------------------------------------------------------
	Set the data element at the given position
--------------------------------------------------------------------------*/
void TEDDataStruct::SetElement (unsigned position, TEDDataBase* newElement)
{
	assert (position < itsClass->Count ());
	if (elements == NULL) PrepareElements ();
	if (elements [position] != NULL) delete elements [position];
	elements [position] = newElement;
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDDataStruct::Print (ostream& out, unsigned indent) const
{
	unsigned i;
	out << ED_PRINT_LOCATOR(out,this," ") << "{" << endl;
	for (i=0; i<itsClass->Count (); i++) {
		const TEDClassStructuredElement& field = itsClass->GetFieldInfo (i);
		out << INDENTP(indent+1) << field.GetFieldName () << ": ";
		if (elements [i]) {
			elements [i]->Print (out, indent+1);
			out << endl;
		}
		else out << "MISSING" << endl;
	}
	out << INDENT << "}" << endl;
}

/*--------------------------------------------------------------------------
	CONSTRUCTOR
--------------------------------------------------------------------------*/
TEDDataUnion::TEDDataUnion (const TEDClassUnion* _itsClass): 
	itsClass (_itsClass), element (NULL), activeEntry (ED_ACCESS_UNION_UNSET)
{
	assert (itsClass);
	if (activeEntry == ED_ACCESS_UNION_UNSET) {
		SetElement (activeEntry, NULL);
	}
	else {
		SetElement (activeEntry, itsClass->GetFieldInfo (activeEntry).GetFieldClass ().NewInstance ());
	}
}

/*--------------------------------------------------------------------------
	Set the data element at the given position
--------------------------------------------------------------------------*/
void TEDDataUnion::SetElement (unsigned position, TEDDataBase* newElement)
{
	assert (position < itsClass->Count () || position == ED_ACCESS_UNION_UNSET);
	if (element != NULL) delete element;
	element = newElement;
	activeEntry = position;
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDDataUnion::Print (ostream& out, unsigned indent) const
{
	if (element == NULL) out << ED_PRINT_LOCATOR(out,this," ") << "NOT SET";
	else {
		const TEDClassStructuredElement& field = itsClass->GetFieldInfo (activeEntry);
		out << ED_PRINT_LOCATOR(out,this," ") << field.GetFieldName () << ": ";
		element->Print (out, indent+1);
	}
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDDataInteger::Print (ostream& out, unsigned indent) const
{
	ED_WARNING_REMOVER (indent);
	out << ED_PRINT_LOCATOR(out,this," ") << value;
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDDataEnumerated::Print (ostream& out, unsigned indent) const
{
	const TEDClassEnumerated* Class = (const TEDClassEnumerated*)(GetClass ());

	// Find the label if any
	unsigned i;
	ED_WARNING_REMOVER (indent);
	out << ED_PRINT_LOCATOR(out,this," ");
	for (i=0; i<Class->Count (); i++) {
		if (Class->GetValue (i) == GetValue ()) {
			out << Class->GetLabel (i) << " (" << (unsigned)GetValue () << ")";
			return;
		}
	}
	
	if (Class->GetDefaultLabel ()) {
		out << Class->GetDefaultLabel () << " (" << (unsigned)GetValue () << ")";
	} else {
		out << (unsigned)GetValue ();
	}
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDDataBinary::Print (ostream& out, unsigned indent) const
{
	unsigned i;
	const char* Hex = "0123456789ABCDEF";
	ED_WARNING_REMOVER (indent);

	out << ED_PRINT_LOCATOR(out,this," ");
	for (i=0; i<(GetUsedBits ()+7)/8; i++) {
		ED_BYTE Value = GetValue () [i];
		out << (i? " " : "") << Hex [Value >> 4] << Hex [Value & 0x0F];
	}
}


/*--------------------------------------------------------------------------
	DEFAULT CONSTRUCTOR
--------------------------------------------------------------------------*/
TEDDataBinary::TEDDataBinary (const TEDClassBinary* _itsClass):
	itsClass (_itsClass), data (NULL), usedBits (0U), allocatedBytes (0U)
{
	if (itsClass->GetIsFixed ()) {
		PrepareData (itsClass->GetMaxBits ());
		usedBits = itsClass->GetMaxBits ();
	}
}

/*--------------------------------------------------------------------------
	Set the data
--------------------------------------------------------------------------*/
void TEDDataBinary::Set (const ED_BYTE* newData, unsigned newUsedBits)
{
	//assert (newUsedBits <= itsClass->GetMaxBits ());
	PrepareData (newUsedBits);
	EDCopyBits (data, 0UL, newData, 0UL, newUsedBits);
	usedBits = newUsedBits;
}

/*--------------------------------------------------------------------------
	CONSTRUCTOR
--------------------------------------------------------------------------*/
TEDDataSequence::TEDDataSequence (const TEDClassSequence* _itsClass): 
	itsClass (_itsClass) 
{
	assert (itsClass);
	if (itsClass->GetIsFixed ()) {
		unsigned i;
		for (i=0; i<itsClass->GetMaxItems (); i++) {
			AddElement (itsClass->GetSequencedClass ()->NewInstance ());
		}
	}
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void TEDDataSequence::Print (ostream& out, unsigned indent) const
{
	unsigned i;
	out << ED_PRINT_LOCATOR(out,this," ") << "[" << endl;
	indent++;
	for (i=0; i<elements.Count (); i++) {
		out << INDENT;
		elements [i].Print (out, indent+1);
		if (i < (elements.Count ()-1)) out << ",";
		out << endl;
	}
	indent--;
	out << INDENT << "]";
}


/*--------------------------------------------------------------------------
	Creates with new a default instance of this type.
--------------------------------------------------------------------------*/
TEDDataBase* TEDClassStruct::NewInstance () const
{
	return new TEDDataStruct (this);
}


/*--------------------------------------------------------------------------
	Creates with new a default instance of this type.
--------------------------------------------------------------------------*/
TEDDataBase* TEDClassUnion::NewInstance () const
{
	return new TEDDataUnion (this);
}


/*--------------------------------------------------------------------------
	Creates with new a default instance of this type.
--------------------------------------------------------------------------*/
TEDDataBase* TEDClassInteger::NewInstance () const
{
	return new TEDDataInteger (this, 0);
}


/*--------------------------------------------------------------------------
	Creates with new a default instance of this type.
--------------------------------------------------------------------------*/
TEDDataBase* TEDClassEnumerated::NewInstance () const
{
	return new TEDDataEnumerated (this, 0);
}


/*--------------------------------------------------------------------------
	Creates with new a default instance of this type.
--------------------------------------------------------------------------*/
TEDDataBase* TEDClassBinary::NewInstance () const
{
	return new TEDDataBinary (this);
}


/*--------------------------------------------------------------------------
	Creates with new a default instance of this type.
--------------------------------------------------------------------------*/
TEDDataBase* TEDClassSequence::NewInstance () const
{
	return new TEDDataSequence (this);
}


#endif
