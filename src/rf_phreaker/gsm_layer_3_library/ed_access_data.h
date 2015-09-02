/*******************************************************************************
  ed_access_data.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __ED_ACCESS_DATA_H
#define __ED_ACCESS_DATA_H
#ifndef __cplusplus
#error "You need a C++ compiler for the 'EnDec access' library!"
#endif

#ifndef __ED_ACCESS_H
#error "This include must be included within ed_access.h only"
#endif

#include "ed_access_util.h"
#define ED_ACCESS_MISSING_LOCATOR -1
#define ED_ACCESS_UNION_UNSET 0xFFFFFFFFU


/*==============================================================================
	Base class for all the data descriptor classes
==============================================================================*/
class TEDDataBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataBase () 
#ifndef ED_NO_ACCESS_LOCATOR
			: DataLocator (0)
#endif
		{}
		/*--------------------------------------------------------------------------
			DESTRUCTOR
		--------------------------------------------------------------------------*/
		virtual ~TEDDataBase () {}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* Clone () const = 0;

		/*--------------------------------------------------------------------------
			Return information on the class
		--------------------------------------------------------------------------*/
		virtual const TEDClassBase* GetClass () const = 0;

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, unsigned indent) const = 0;
#endif

#ifndef ED_NO_ACCESS_LOCATOR
		/*--------------------------------------------------------------------------
			Position where this item has been decoded
		--------------------------------------------------------------------------*/
		ED_LOCATOR DataLocator;

		/*--------------------------------------------------------------------------
			Returns the offset in bits where the locator is or 
			ED_ACCESS_MISSING_LOCATOR if not found.
		--------------------------------------------------------------------------*/
		int GetLocatorOffset () const {return (ED_LOCATOR_IS_VALID (&DataLocator) ? ED_LOCATOR_GET_OFFSET (&DataLocator) : ED_ACCESS_MISSING_LOCATOR);}

		/*--------------------------------------------------------------------------
			Returns the length in bits where the locator is or 
			ED_ACCESS_MISSING_LOCATOR if not found.
		--------------------------------------------------------------------------*/
		int GetLocatorLength () const {return (ED_LOCATOR_IS_VALID (&DataLocator) ? ED_LOCATOR_GET_LENGTH (&DataLocator) : ED_ACCESS_MISSING_LOCATOR);}
#endif
};



/*==============================================================================
	Class for "struct" data elements
==============================================================================*/
class TEDDataStruct: public TEDDataBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataStruct (const TEDClassStruct* _itsClass);

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataStruct (const TEDDataStruct& b): elements (NULL) {operator= (b);}
		/*--------------------------------------------------------------------------
			DESTRUCTOR
		--------------------------------------------------------------------------*/
		~TEDDataStruct () {DeleteAll ();}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDDataStruct& operator= (const TEDDataStruct& b) {
			TEDDataBase::operator= (b);
			itsClass = b.itsClass;
			PrepareElements ();
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* Clone () const {return new TEDDataStruct (*this);}

		/*--------------------------------------------------------------------------
			Set the data element at the given position
		--------------------------------------------------------------------------*/
		void SetElement (unsigned position, TEDDataBase* newElement);

		/*--------------------------------------------------------------------------
			Returns the element at the given position
		--------------------------------------------------------------------------*/
		TEDDataBase* GetElement (unsigned position) {assert (position<itsClass->Count ()); if (!elements) return NULL; return elements[position];}
		const TEDDataBase* GetElement (unsigned position) const {assert (position<itsClass->Count ()); if (!elements) return NULL; return elements[position];}
		
		/*--------------------------------------------------------------------------
			Returns true if the given element is present
		--------------------------------------------------------------------------*/
		bool IsPresent (unsigned position) const {
			assert (position<itsClass->Count ());
			if (!elements) return false;
			return (elements[position] != NULL);
		}

		/*--------------------------------------------------------------------------
			Return information on the class
		--------------------------------------------------------------------------*/
		virtual const TEDClassBase* GetClass () const {return itsClass;}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, unsigned indent) const;
#endif
	
	protected:
		// Prepare elements
		void PrepareElements () {
			DeleteAll ();
			elements = new TEDDataBase* [itsClass->Count ()];
			unsigned i;
			for (i=0; i<itsClass->Count (); i++) elements [i] = NULL;
		}

		// Delete all
		void DeleteAll ()	{
			if (elements != NULL) {
				unsigned i;
				for (i=0; i<itsClass->Count (); i++) if (elements [i] != NULL) delete elements [i];
				delete [] elements;
				elements = NULL;
			}
		}

		// Related structure
		const TEDClassStruct* itsClass;

		// Array of struct elements. They are paired with the structure
		TEDDataBase** elements;
};

/*==============================================================================
	Class for "union" data elements
==============================================================================*/
class TEDDataUnion: public TEDDataBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataUnion (const TEDClassUnion* _itsClass);

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataUnion (const TEDDataUnion& b): TEDDataBase (b), element (NULL) {operator= (b);}

		/*--------------------------------------------------------------------------
			DESTRUCTOR
		--------------------------------------------------------------------------*/
		~TEDDataUnion () {if (element) delete element;}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDDataUnion& operator= (const TEDDataUnion& b) {
			TEDDataBase::operator= (b);
			if (element) delete element;
			if (b.element) element = b.element->Clone ();
			else element = NULL;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* Clone () const {return new TEDDataUnion (*this);}

		/*--------------------------------------------------------------------------
			Set the data element at the given position
		--------------------------------------------------------------------------*/
		void SetElement (unsigned position, TEDDataBase* newElement);

		/*--------------------------------------------------------------------------
			Returns the currently set element
		--------------------------------------------------------------------------*/
		TEDDataBase* GetElement () {assert (element != NULL); return element;}
		const TEDDataBase* GetElement () const {assert (element != NULL); return element;}
		unsigned GetActiveEntry () const {return activeEntry;}

		/*--------------------------------------------------------------------------
			Return information on the class
		--------------------------------------------------------------------------*/
		virtual const TEDClassBase* GetClass () const {return itsClass;}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, unsigned indent) const;
#endif

	protected:
		// Related structure
		const TEDClassUnion* itsClass;

		// Array of struct elements. They are paired with the structure
		TEDDataBase* element;

		// Active entry in the union
		unsigned activeEntry;
};

/*==============================================================================
	Base class for integers
==============================================================================*/
class TEDDataInteger: public TEDDataBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataInteger (const TEDClassInteger* _itsClass, ED_EXLONG _value): value (_value), itsClass (_itsClass) {assert (itsClass);}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataInteger (const TEDDataInteger& b): TEDDataBase (b) {
			value = b.value;
		}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDDataInteger& operator= (const TEDDataInteger& b) {
			TEDDataBase::operator= (b);
			itsClass = b.itsClass;
			value = b.value;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* Clone () const {return new TEDDataInteger (*this);}

		/*--------------------------------------------------------------------------
			Set the value
		--------------------------------------------------------------------------*/
		void Set (ED_EXLONG _value) {value = _value;}

		/*--------------------------------------------------------------------------
			Return information on the class
		--------------------------------------------------------------------------*/
		virtual const TEDClassBase* GetClass () const {return itsClass;}

		/*--------------------------------------------------------------------------
			Returns the value
		--------------------------------------------------------------------------*/
		ED_EXLONG GetValue () const {return value;}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, unsigned indent) const;
#endif
	protected:
		// Internal value
		ED_EXLONG value;

		// Its related class
		const TEDClassInteger* itsClass;
};

/*==============================================================================
	Base class for Enumerated integers
==============================================================================*/
class TEDDataEnumerated: public TEDDataInteger {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataEnumerated (const TEDClassEnumerated* _itsClass, ED_EXLONG _value): TEDDataInteger (_itsClass, _value) {assert (itsClass);}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataEnumerated (const TEDDataEnumerated& b): TEDDataInteger (b) {}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDDataEnumerated& operator= (const TEDDataEnumerated& b) {
			TEDDataInteger::operator= (b);
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* Clone () const {return new TEDDataEnumerated (*this);}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, unsigned indent) const;
#endif
};

/*==============================================================================
	Base class for binary values
==============================================================================*/
class TEDDataBinary: public TEDDataBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataBinary (const TEDClassBinary* _itsClass, const ED_BYTE* _data, unsigned _usedBits):
			itsClass (_itsClass), data (NULL), usedBits (0U), allocatedBytes (0U) 
			{assert (itsClass); Set (_data, _usedBits);}

		/*--------------------------------------------------------------------------
			DEFAULT CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataBinary (const TEDClassBinary* _itsClass);

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataBinary (const TEDDataBinary& b) {operator= (b);}

		/*--------------------------------------------------------------------------
			DESTRUCTOR
		--------------------------------------------------------------------------*/
		virtual ~TEDDataBinary () {if (data) delete [] data;}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDDataBinary& operator= (const TEDDataBinary& b) {
			TEDDataBase::operator= (b);
			itsClass = b.itsClass;
			PrepareData (b.usedBits);
			Set (b.data, b.usedBits);
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* Clone () const {return new TEDDataBinary (*this);}

		/*--------------------------------------------------------------------------
			Set the data
		--------------------------------------------------------------------------*/
		void Set (const ED_BYTE* newData, unsigned newUsedBits);

		/*--------------------------------------------------------------------------
			Return information on the class
		--------------------------------------------------------------------------*/
		virtual const TEDClassBase* GetClass () const {return itsClass;}

		/*--------------------------------------------------------------------------
			Returns the internal data
		--------------------------------------------------------------------------*/
		const ED_BYTE* GetValue () const {return data;}
		unsigned GetUsedBits () const {return usedBits;}


#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, unsigned indent) const;
#endif

	protected:
		// Prepare the data
		void PrepareData (unsigned sizeInBits) {
			if (data) delete [] data;
			allocatedBytes = ((sizeInBits+7)>>3);
			data = new ED_BYTE [allocatedBytes];
			ED_RESET_MEM (data, allocatedBytes);
			usedBits = 0;
		}

		// Its related class
		const TEDClassBinary* itsClass;

		// Internal value
		ED_BYTE* data;
		unsigned usedBits;
		unsigned allocatedBytes;

};

/*==============================================================================
	Base class for binary values
==============================================================================*/
class TEDDataSequence: public TEDDataBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataSequence (const TEDClassSequence* _itsClass);

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDDataSequence (const TEDDataSequence& b) {operator= (b);}

		/*--------------------------------------------------------------------------
			operator =
		--------------------------------------------------------------------------*/
		TEDDataSequence& operator= (const TEDDataSequence& b) {
			TEDDataBase::operator= (b);
			itsClass = b.itsClass;
			elements = b.elements;
			return *this;
		}

		/*--------------------------------------------------------------------------
			Returns a copy of this object
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* Clone () const {return new TEDDataSequence (*this);}

		/*--------------------------------------------------------------------------
			Add an element
		--------------------------------------------------------------------------*/
		void AddElement (TEDDataBase* newElement) {
			elements.Add (newElement);
		}

		/*--------------------------------------------------------------------------
			Insert an element before the given one
		--------------------------------------------------------------------------*/
		void InsertElement (TEDDataBase* newElement, unsigned position) {
			if (position < Count ()) elements.Insert (newElement, position);
			else AddElement (newElement);
		}

		/*--------------------------------------------------------------------------
			Replaces the given element
		--------------------------------------------------------------------------*/
		void ReplaceElement (TEDDataBase* newElement, unsigned position) {
			DelElement (position);
			InsertElement (newElement, position);
		}

		/*--------------------------------------------------------------------------
			Delete an element
		--------------------------------------------------------------------------*/
		void DelElement (unsigned position) {
			elements.Delete (position);
		}

		/*--------------------------------------------------------------------------
			Return information on the class
		--------------------------------------------------------------------------*/
		virtual const TEDClassBase* GetClass () const {return itsClass;}

		/*--------------------------------------------------------------------------
			Returns the currently set element
		--------------------------------------------------------------------------*/
		TEDDataBase* GetElement (unsigned i) {assert (i < elements.Count ()); return &elements [i];}
		const TEDDataBase* GetElement (unsigned i) const {assert (i < elements.Count ()); return &elements [i];}
		unsigned Count () const {return elements.Count ();}

#ifndef ED_NO_ACCESS_DEBUG
		/*--------------------------------------------------------------------------
			Print the data on the given ostream, for debugging purposes
		--------------------------------------------------------------------------*/
		virtual void Print (ostream& out, unsigned indent) const;
#endif
	protected:
		const TEDClassSequence* itsClass;
		// Type descriptor of the class here contained
		TEDArray <TEDDataBase> elements;
};

#endif

