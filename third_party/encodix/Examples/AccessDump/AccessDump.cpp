/**************************************************************************
	Access Dump Example - (c) Dafocus 2007	
**************************************************************************/
#include "AccessDump.h"


extern TAccessDumpCustom* AccessDumpCustomTable = NULL;

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void AccessDump_DataStruct (const TEDDataStruct* Data, ostream& out, unsigned indent)
{
	const TEDClassStruct* Class = (const TEDClassStruct*)(Data->GetClass ());

	unsigned i;
	out << "{" << endl;
	for (i=0; i<Class->Count (); i++) {
		const TEDClassStructuredElement& field = Class->GetFieldInfo (i);
		out << INDENTP(indent+1) << field.GetFieldName () << ": ";
		if (Data->GetElement (i)) {
			AccessDump (Data->GetElement (i), out, indent+1);
			out << endl;
		}
		else out << "MISSING" << endl;
	}
	out << INDENT << "}" << endl;
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void AccessDump_DataUnion (const TEDDataUnion* Data, ostream& out, unsigned indent)
{
	const TEDClassUnion* Class = (const TEDClassUnion*)(Data->GetClass ());

	const TEDClassStructuredElement& field = Class->GetFieldInfo (Data->GetActiveEntry ());
	out << field.GetFieldName () << ": ";
	AccessDump (Data->GetElement (), out, indent+1);
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void AccessDump_DataInteger (const TEDDataInteger* Data, ostream& out, unsigned indent)
{
	Data->Print (out, indent);
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void AccessDump_DataEnumerated (const TEDDataEnumerated* Data, ostream& out, unsigned indent)
{
	Data->Print (out, indent);
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void AccessDump_DataBinary (const TEDDataBinary* Data, ostream& out, unsigned indent)
{
	Data->Print (out, indent);
}

/*--------------------------------------------------------------------------
	Print the data on the given ostream, for debugging purposes
--------------------------------------------------------------------------*/
void AccessDump_DataSequence (const TEDDataSequence* Data, ostream& out, unsigned indent)
{
	unsigned i;
	out << "[" << endl;
	indent++;
	for (i=0; i<Data->Count (); i++) {
		out << INDENT;
		AccessDump (Data->GetElement (i), out, indent+1);
		if (i < (Data->Count ()-1)) out << ",";
		out << endl;
	}
	indent--;
	out << INDENT << "]";
}


/*=========================================================================
	Executes the dump of a TEDDataBase using a custom implementation
=========================================================================*/
void AccessDump (const TEDDataBase* Data, ostream& out, unsigned indent, bool avoidCustom)
{
	const TEDClassBase* Class = Data->GetClass ();
	if (AccessDumpCustomTable && !avoidCustom) {
		int i;
		for (i=0; AccessDumpCustomTable [i].CustomAccessDump != NULL; i++) {
			if (Class == *(AccessDumpCustomTable [i].ClassPointer)) {
				AccessDumpCustomTable [i].CustomAccessDump (Data, out, indent);
				return;
			}
		}
	}
	switch (Class->GetType ()) {
		case TED_ACC_STRUCT    : AccessDump_DataStruct     ((const TEDDataStruct    *)Data, out, indent); break;
		case TED_ACC_UNION     : AccessDump_DataUnion      ((const TEDDataUnion     *)Data, out, indent); break;
		case TED_ACC_INTEGER   : AccessDump_DataInteger    ((const TEDDataInteger   *)Data, out, indent); break;
		case TED_ACC_BINARY    : AccessDump_DataBinary     ((const TEDDataBinary    *)Data, out, indent); break;
		case TED_ACC_SEQUENCE  : AccessDump_DataSequence   ((const TEDDataSequence  *)Data, out, indent); break;
		case TED_ACC_ENUMERATED: AccessDump_DataEnumerated ((const TEDDataEnumerated*)Data, out, indent); break;
		default: assert (0); // Invalid case
	}
}

