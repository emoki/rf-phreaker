/*******************************************************************************
  ed_access_class.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __ED_ACCESS_CLASS_H
#define __ED_ACCESS_CLASS_H
#ifndef __cplusplus
#error "You need a C++ compiler for the 'EnDec access' library!"
#endif
#include "ed_access_util.h"

#define TED_ACC_UNDEFINED           0
#define TED_ACC_BASE                1
#define TED_ACC_REFERENCE           2
#define TED_ACC_STRUCTUREDELEMENT   3
#define TED_ACC_STRUCTURED          4
#define TED_ACC_STRUCT              5
#define TED_ACC_UNION               6
#define TED_ACC_INTEGER             7
#define TED_ACC_BINARY              8
#define TED_ACC_SEQUENCE            9
#define TED_ACC_ENUMERATED         10

class TEDDataBase;

/*==============================================================================
	Base class for all the data descriptor classes
==============================================================================*/
class TEDClassBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassBase (const char* _className): className (_className) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassBase (const TEDClassBase& b) {operator= (b);}

		/*--------------------------------------------------------------------------
			DESTRUCTOR
		--------------------------------------------------------------------------*/
		virtual ~TEDClassBase () {}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDClassBase* Clone () const = 0;

		/*--------------------------------------------------------------------------
			Creates with new a default instance of this type.
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* NewInstance () const = 0;

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDClassBase& operator= (const TEDClassBase& b) {className = b.className; return *this;}

		/*--------------------------------------------------------------------------
			Get the class name
		--------------------------------------------------------------------------*/
		const char* GetClassName () const {return className;}

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_BASE;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {return type == GetType ();}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, bool explode, unsigned indent) const = 0;
#endif
	protected:
		// Name of the class
		TEDString className;
};

/*==============================================================================
	Reference to other class object.
	This class holds a pointer to another TEDClassBase which can be either owned
	or just pointed.
==============================================================================*/
class TEDClassReference {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassReference (): referenced (NULL), owned (false) {}
		TEDClassReference (const TEDClassBase* _referenced, bool _owned): 
			referenced (_referenced), owned (_owned) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassReference (const TEDClassReference& b): referenced (NULL), owned (false) {operator= (b);}

		/*--------------------------------------------------------------------------
			DESTRUCTOR
		--------------------------------------------------------------------------*/
		virtual ~TEDClassReference () {DeleteAll ();}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDClassReference* Clone () const {return new TEDClassReference (*this);}

		/*--------------------------------------------------------------------------
			Creates with new a default instance of this type.
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* NewInstance () const {return referenced->NewInstance ();}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDClassReference& operator= (const TEDClassReference& b) {
			DeleteAll ();
			if (b.owned) {
				if (b.referenced != NULL)	referenced = b.referenced->Clone ();
			}
			else referenced = b.referenced;
			owned = b.owned;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Get the referenced class
		--------------------------------------------------------------------------*/
		const TEDClassBase& GetClass () const {assert (referenced != NULL); return *referenced;}
		const TEDClassBase* GetClassPtr () const {assert (referenced != NULL); return referenced;}

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_REFERENCE;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {return (type == GetType ());}

		/*--------------------------------------------------------------------------
		Returns true if this class it owns.
		--------------------------------------------------------------------------*/
		bool GetIsOwned () const {return owned;}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		void Print (ostream& out, bool explode, unsigned indent) const;
#endif

	protected:
		/*--------------------------------------------------------------------------
			Removes the reference and deletes everything
		--------------------------------------------------------------------------*/
		void DeleteAll () {
			if (owned && (referenced != NULL)) delete referenced;
			referenced = NULL;
			owned = false;
		}

		// Referenced class
		const TEDClassBase* referenced;

		// True if owned, false otherwise
		bool owned;
};


/*==============================================================================
	Element of the the structured data types. Each one of these is a struct or
	union field.
==============================================================================*/
class TEDClassStructuredElement {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassStructuredElement (const char* _fieldName, const TEDClassReference& _fieldClass, bool _isOptional=false):
			fieldName (_fieldName), fieldClass (_fieldClass), isOptional (_isOptional) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassStructuredElement (const TEDClassStructuredElement& b)
			{operator= (b);}

		/*--------------------------------------------------------------------------
			DESTRUCTOR
		--------------------------------------------------------------------------*/
		virtual ~TEDClassStructuredElement () {}

		/*--------------------------------------------------------------------------
			Operator =
		--------------------------------------------------------------------------*/
		TEDClassStructuredElement& operator= (const TEDClassStructuredElement& b) {
			fieldName = b.fieldName;
			fieldClass = b.fieldClass;
			isOptional = b.isOptional;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Clone method
		--------------------------------------------------------------------------*/
		TEDClassStructuredElement* Clone () const {return new TEDClassStructuredElement (*this);}

		/*--------------------------------------------------------------------------
			Return internal info
		--------------------------------------------------------------------------*/
		const char* GetFieldName () const {return fieldName.Get ();}
		const TEDClassBase& GetFieldClass () const {return fieldClass.GetClass ();}
		const TEDClassBase* GetFieldClassPtr () const {return &(fieldClass.GetClass ());}
		bool GetIsOptional () const {return isOptional;}

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_STRUCTUREDELEMENT;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {return (type == GetType ());}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, bool explode, unsigned indent) const;
#endif
	
		const TEDClassReference & GetClassReference () const {return fieldClass;}

	protected:
		// Name of the field
		TEDString fieldName;
		// Associated data
		TEDClassReference fieldClass;
		// True if the item is optional
		bool isOptional;
};

/*==============================================================================
	Base class for all the structured-like data elements (structs and unions)
==============================================================================*/
class TEDClassStructured: public TEDClassBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassStructured (const char* _className): TEDClassBase (_className) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassStructured (const TEDClassStructured& b): TEDClassBase (b) {
			elements = b.elements;
		}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDClassStructured& operator= (const TEDClassStructured& b) {
			TEDClassBase::operator= (b);
			elements = b.elements;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDClassBase* Clone () const = 0;
		
		/*--------------------------------------------------------------------------
			Returns the number of structure elements
		--------------------------------------------------------------------------*/
		unsigned Count () const {return elements.Count ();}

		/*--------------------------------------------------------------------------
			Returns information on the element at n-th position
		--------------------------------------------------------------------------*/
		const TEDClassStructuredElement& GetFieldInfo (unsigned n) const {return (elements[n]);}

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_STRUCTURED;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {if (type == GetType ()) return true; return TEDClassBase::IsA (type);}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, bool explode, unsigned indent) const = 0;
#endif

	protected:
		// Internal array of items
		TEDArray <TEDClassStructuredElement> elements;
};

/*==============================================================================
	Class for "struct" data elements
==============================================================================*/
class TEDClassStruct: public TEDClassStructured {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassStruct (const char* _className): TEDClassStructured (_className) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassStruct (const TEDClassStruct& b): TEDClassStructured (b) {}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDClassStruct& operator= (const TEDClassStruct& b) {
			TEDClassStructured::operator= (b);
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDClassBase* Clone () const {return new TEDClassStruct (*this);}

		/*--------------------------------------------------------------------------
			Creates with new a default instance of this type.
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* NewInstance () const;

		/*--------------------------------------------------------------------------
			Adds an entry to the structure
		--------------------------------------------------------------------------*/
		void AddField (const char* fieldName, const TEDClassReference& fieldClass, bool isOptional) {
			elements.Add (new TEDClassStructuredElement (fieldName, fieldClass, isOptional));
		}

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_STRUCT;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {if (type == GetType ()) return true; return TEDClassStructured::IsA (type);}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, bool explode, unsigned indent) const;
#endif
};

/*==============================================================================
	Class for "union" data elements
==============================================================================*/
class TEDClassUnion: public TEDClassStructured {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassUnion (const char* _className): TEDClassStructured (_className) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassUnion (const TEDClassUnion& b): TEDClassStructured (b) {}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDClassUnion& operator= (const TEDClassUnion& b) {
			TEDClassStructured::operator= (b);
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDClassBase* Clone () const {return new TEDClassUnion (*this);}

		/*--------------------------------------------------------------------------
			Creates with new a default instance of this type.
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* NewInstance () const;

		/*--------------------------------------------------------------------------
			Adds an entry to the union
		--------------------------------------------------------------------------*/
		void AddField (const char* fieldName, const TEDClassReference& fieldClass) {
			TEDClassStructuredElement* el = new TEDClassStructuredElement (fieldName, fieldClass, true);
			elements.Add (el);
		}

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_UNION;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {if (type == GetType ()) return true; return TEDClassStructured::IsA (type);}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, bool explode, unsigned indent) const;
#endif
};

/*==============================================================================
	Base class for integers
==============================================================================*/
class TEDClassInteger: public TEDClassBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassInteger (const char* _className, unsigned _bitSize): TEDClassBase (_className), bitSize (_bitSize) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassInteger (const TEDClassInteger& b): TEDClassBase (b) {
			bitSize = b.bitSize;
		}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDClassInteger& operator= (const TEDClassInteger& b) {
			TEDClassBase::operator= (b);
			bitSize = b.bitSize;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDClassBase* Clone () const {return new TEDClassInteger (*this);}

		/*--------------------------------------------------------------------------
			Creates with new a default instance of this type.
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* NewInstance () const;

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_INTEGER;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {if (type == GetType ()) return true; return TEDClassBase::IsA (type);}

		/*--------------------------------------------------------------------------
			Returns the bit size
		--------------------------------------------------------------------------*/
		unsigned GetBitSize () const {return bitSize;}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, bool explode, unsigned indent) const;
#endif
	protected:
		// Internal value
		unsigned bitSize;
};

/*==============================================================================
	Base class for enumerated integers
==============================================================================*/
class TEDClassEnumerated: public TEDClassInteger {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassEnumerated (const char* _className, unsigned _bitSize): TEDClassInteger (_className, _bitSize) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassEnumerated (const TEDClassEnumerated& b): TEDClassInteger (b), labels (b.labels), defaultLabel (b.defaultLabel) {}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDClassEnumerated& operator= (const TEDClassEnumerated& b) {
			TEDClassInteger::operator= (b);
			labels = b.labels;
			defaultLabel = b.defaultLabel;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDClassBase* Clone () const {return new TEDClassEnumerated (*this);}

		/*--------------------------------------------------------------------------
			Creates with new a default instance of this type.
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* NewInstance () const;

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_ENUMERATED;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {if (type == GetType ()) return true; return TEDClassInteger::IsA (type);}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, bool explode, unsigned indent) const;
#endif

		/*--------------------------------------------------------------------------
			Add a label
		--------------------------------------------------------------------------*/
		void AddLabel (const char* label, int value);

		/*--------------------------------------------------------------------------
			Set the default value
		--------------------------------------------------------------------------*/
		void SetDefaultLabel (const char* label);

		/*--------------------------------------------------------------------------
			Returns the string associated to the default label or "NULL" if none
			has been defined.
		--------------------------------------------------------------------------*/
		const char* GetDefaultLabel () const {return defaultLabel;}

		/*--------------------------------------------------------------------------
			Returns the number of labels
		--------------------------------------------------------------------------*/
		unsigned Count () const {return labels.Count ();}

		/*--------------------------------------------------------------------------
			Returns the value associated to the label at position p
		--------------------------------------------------------------------------*/
		int GetValue (unsigned p) const {return labels [p].value;}

		/*--------------------------------------------------------------------------
			Returns the string associated to the label at position p
		--------------------------------------------------------------------------*/
		const char* GetLabel (unsigned p) const {return labels [p].label;}

	protected:
		/*--------------------------------------------------------------------------
			This structure describes internally an enumeration label
		--------------------------------------------------------------------------*/
		struct TEDClassEnumeratedEntry {
			TEDClassEnumeratedEntry (const char* _label, int _value): label (_label), value (_value) {}
			TEDClassEnumeratedEntry (const TEDClassEnumeratedEntry& e) {operator= (e);}
			TEDClassEnumeratedEntry& operator= (const TEDClassEnumeratedEntry& e) {label=e.label; value=e.value; return *this;}
			TEDClassEnumeratedEntry* Clone () const {return new TEDClassEnumeratedEntry (*this);}

			TEDString label;
			int value;
		};

		/*--------------------------------------------------------------------------
			Array mapping labels and values
		--------------------------------------------------------------------------*/
		TEDArray <TEDClassEnumeratedEntry> labels;

		/*--------------------------------------------------------------------------
			Default value
		--------------------------------------------------------------------------*/
		TEDString defaultLabel;
};

/*--------------------------------------------------------------------------
	Add a label
--------------------------------------------------------------------------*/
inline void TEDClassEnumerated::AddLabel (const char* label, int value) 
{
	labels.Add (new TEDClassEnumeratedEntry (label, value));
}

/*--------------------------------------------------------------------------
	Set the default value
--------------------------------------------------------------------------*/
inline void TEDClassEnumerated::SetDefaultLabel (const char* label)
{
	defaultLabel = label;
}

/*==============================================================================
	Base class for binary values
==============================================================================*/
class TEDClassBinary: public TEDClassBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassBinary (const char* _className, unsigned _maxBits, bool _isFixed): 
			TEDClassBase (_className), maxBits (_maxBits), isFixed (_isFixed) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassBinary (const TEDClassBinary& b): TEDClassBase (b) {
			maxBits = b.maxBits;
			isFixed = b.isFixed;
		}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDClassBinary& operator= (const TEDClassBinary& b) {
			TEDClassBase::operator= (b);
			maxBits = b.maxBits;
			isFixed = b.isFixed;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDClassBase* Clone () const {return new TEDClassBinary (*this);}

		/*--------------------------------------------------------------------------
			Creates with new a default instance of this type.
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* NewInstance () const;

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_BINARY;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {if (type == GetType ()) return true; return TEDClassBase::IsA (type);}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, bool explode, unsigned indent) const;
#endif
		
		/*--------------------------------------------------------------------------
			Returns the max bits
		--------------------------------------------------------------------------*/
		unsigned GetMaxBits () const {return maxBits;}
		bool GetIsFixed () const {return isFixed;}

	protected:
		// Internal value
		unsigned maxBits;
		bool isFixed;
};

/*==============================================================================
	Base class for binary values
==============================================================================*/
class TEDClassSequence: public TEDClassBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassSequence (const char* _className, const TEDClassReference& _sequencedClass, unsigned _maxItems, bool _isFixed): 
			TEDClassBase (_className), maxItems (_maxItems), isFixed (_isFixed), sequencedClass (_sequencedClass) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDClassSequence (const TEDClassSequence& b): TEDClassBase (b) {
			maxItems = b.maxItems;
			isFixed = b.isFixed;
			sequencedClass = b.sequencedClass;
		}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDClassSequence& operator= (const TEDClassSequence& b) {
			TEDClassBase::operator= (b);
			maxItems = b.maxItems;
			isFixed = b.isFixed;
			sequencedClass = b.sequencedClass;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDClassBase* Clone () const {return new TEDClassSequence (*this);}

		/*--------------------------------------------------------------------------
			Creates with new a default instance of this type.
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* NewInstance () const;

		/*--------------------------------------------------------------------------
			Returns the sequenced class
		--------------------------------------------------------------------------*/
		const TEDClassBase* GetSequencedClass () const {return sequencedClass.GetClassPtr ();}

		/*--------------------------------------------------------------------------
			Returns the type of the object
		--------------------------------------------------------------------------*/
		virtual int GetType () const {return TED_ACC_SEQUENCE;}

		/*--------------------------------------------------------------------------
			Returns true if this class is of the given type or derives from it.
		--------------------------------------------------------------------------*/
		virtual bool IsA (int type) const {if (type == GetType ()) return true; return TEDClassBase::IsA (type);}

		/*--------------------------------------------------------------------------
			True if the size is fixed
		--------------------------------------------------------------------------*/
		bool GetIsFixed () const {return isFixed;}

		/*--------------------------------------------------------------------------
			Returns the max number of items or the fixed value if is fixed.
		--------------------------------------------------------------------------*/
		unsigned GetMaxItems () const {return maxItems;}

		/*--------------------------------------------------------------------------
		Returns TEDClassReference.
		--------------------------------------------------------------------------*/
		const TEDClassReference & GetClassReference () const {return sequencedClass;}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, bool explode, unsigned indent) const;
#endif

	protected:
		// Maximum number of items
		unsigned maxItems;

		// True if the sequence has a fixed number of items (i.e. maxItems).
		// False if the sequence has a variable number of items (from 0 to maxItems)
		bool isFixed;

		// Type descriptor of the class here contained
		TEDClassReference sequencedClass;
};

#endif

