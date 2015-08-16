/*******************************************************************************
  ed_access_util.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __ED_ACCESS_UTIL_H
#define __ED_ACCESS_UTIL_H
#ifndef __cplusplus
#error "You need a C++ compiler for the 'EnDec access' library!"
#endif
#include <stdlib.h>
#include <assert.h>
#include "ed_data.h"
#include "ed_lib.h"


/*------------------------------------------------------------------------------
	Some C++ programs are compiled with the old "iostream.h"; some other with
	"iostream". Set ED_USE_IOSTREAM_H according to the needs.
------------------------------------------------------------------------------*/
#ifndef ED_NO_ACCESS_DEBUG
#if defined (ED_USE_IOSTREAM_H) && !(_MSC_VER > 1200)
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#endif

#ifdef ED_USE_RTTI
#define EDAccessCast dynamic_cast
#else
template<class C> inline C EDAccessCast (const void* p) {return (C)p;}
template<class C> inline C EDAccessCast (void* p) {return (C)p;}
#endif

/*==============================================================================
	String class. This is used wherever a dynamic string is needed.
==============================================================================*/
class TEDString {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDString (const char* newText=NULL): text (NULL) {Set (newText);}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDString (const TEDString& b): text (NULL) {operator= (b);}

		/*--------------------------------------------------------------------------
			DESTRUCTOR
		--------------------------------------------------------------------------*/
		~TEDString () {Set (NULL);}

		/*--------------------------------------------------------------------------
			Operator=
		--------------------------------------------------------------------------*/
		TEDString& operator= (const TEDString& b) {Set (b.text); return *this;}

		/*--------------------------------------------------------------------------
			Set the string value
		--------------------------------------------------------------------------*/
		void Set (const char* newText);
		const char* operator= (const char* newText) {Set (newText); return newText;}

		/*--------------------------------------------------------------------------
			Get the string value
		--------------------------------------------------------------------------*/
		const char* Get () const {return text;}
		operator const char* () const {return text;}

	private:
		char* text;
};

#ifndef ED_NO_ACCESS_DEBUG
inline ostream& operator<< (ostream& o, const TEDString& b) {
	o << b.Get ();
	return o;
}
#endif
/*==============================================================================
	Dynamic array template class.
==============================================================================*/
template <class TYPE> class TEDArray {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDArray (): data (NULL), allocated (0), used (0) {}

		/*--------------------------------------------------------------------------
			COPY CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TEDArray (const TEDArray& b): data (NULL), allocated (0), used (0)
			{operator= (b);}

		/*--------------------------------------------------------------------------
			DESTRUCTOR
		--------------------------------------------------------------------------*/
		~TEDArray () {DeleteAll ();}

		/*--------------------------------------------------------------------------
			Operator=
		--------------------------------------------------------------------------*/
		TEDArray& operator= (const TEDArray& b);

		/*--------------------------------------------------------------------------
			Delete all the elements
		--------------------------------------------------------------------------*/
		void DeleteAll ();

		/*--------------------------------------------------------------------------
			Returns the number of elements here stored
		--------------------------------------------------------------------------*/
		unsigned Count () const {return used;}

		/*--------------------------------------------------------------------------
			Get the element at the given position
		--------------------------------------------------------------------------*/
		const TYPE& operator[] (unsigned i) const {
			assert (data); 
			assert (i<used);
			assert (data[i]);
			return *(data [i]);
		}
		TYPE& operator[] (unsigned i) {
			assert (data); 
			assert (i<used); 
			assert (data[i]);
			return *(data [i]);
		}

		/*--------------------------------------------------------------------------
			Append an element to the end
		--------------------------------------------------------------------------*/
		void Add (TYPE* newElement);

		/*--------------------------------------------------------------------------
			Insert an item before "next"
		--------------------------------------------------------------------------*/
		void Insert (TYPE* newElement, unsigned next);

		/*--------------------------------------------------------------------------
			Delete the item at "position"
		--------------------------------------------------------------------------*/
		void Delete (unsigned position);

	private:
		// Array of pointers
		TYPE** data;

		// Number of items allocated
		unsigned allocated;

		// Number of items really used
		unsigned used;

		// Checks the array and makes sure we can fit n more items
		void CheckAndGrow (unsigned n);
};

/*--------------------------------------------------------------------------
	Delete all the elements
--------------------------------------------------------------------------*/
template <class TYPE> 
void TEDArray<TYPE>::DeleteAll () 
{
	unsigned i;
	if (data != NULL) {
		// Delete all the owned sub-elements
		for (i=0; i<used; i++) {
			delete data [i];
		}
		// Delete the array itself
		delete [] data;
		data = NULL;
	}
	allocated = 0;
	used = 0;
}

/*--------------------------------------------------------------------------
	TEDArray operator= implementation
--------------------------------------------------------------------------*/
template <class TYPE> 
TEDArray<TYPE>& TEDArray<TYPE>::operator= (const TEDArray<TYPE>& b)
{
	unsigned i;
	
	DeleteAll ();
	for (i=0; i<b.Count (); i++) {
		Add (b [i].Clone ());
	}
	return *this;
}

/*--------------------------------------------------------------------------
	Checks the array and makes sure we can fit n more items
--------------------------------------------------------------------------*/
template <class TYPE>
void TEDArray<TYPE>::CheckAndGrow (unsigned n)
{
	if (allocated < (used+n)) {
		TYPE** old = data;
		unsigned grow = ((n+8) & ~7);
		data = new TYPE* [allocated+grow];
		ED_RESET_MEM (data, sizeof (TYPE*)*(allocated+grow));
		if (old) {
			memcpy (data, old, sizeof (TYPE*)*allocated);
			delete [] old;
		}
		allocated += grow;
	}
}

/*--------------------------------------------------------------------------
	Append an element to the end
--------------------------------------------------------------------------*/
template <class TYPE>
void TEDArray<TYPE>::Add (TYPE* newElement)
{
	CheckAndGrow (1);
	data [used] = newElement;
	used++;
}

/*--------------------------------------------------------------------------
	Insert an item before "next"
--------------------------------------------------------------------------*/
template <class TYPE>
void TEDArray<TYPE>::Insert (TYPE* newElement, unsigned next)
{
	assert (next <= used);
	CheckAndGrow (1);
	unsigned i;
	for (i=used; i>next; i--) {
		data [i] = data [i-1];
	}
	data [next] = newElement;
	used++;
}

/*--------------------------------------------------------------------------
	Delete the item at "position"
--------------------------------------------------------------------------*/
template <class TYPE>
void TEDArray<TYPE>::Delete (unsigned position)
{
	assert (position < used);
	unsigned i;
	delete data [position];
	for (i=position; i<(used-1); i++) {
		data [i] = data [i+1];
	}
	used--;
}
#endif

