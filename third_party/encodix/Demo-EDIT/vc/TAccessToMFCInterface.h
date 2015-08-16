/*******************************************************************************
  TAccessToMFCInterface.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __TACCESSTOMFCINTERFNACE_H
#define __TACCESSTOMFCINTERFNACE_H

#include "ed_access.h"

/*==============================================================================
	Item info
==============================================================================*/
struct TAMTreeItemInfo {
	TAMTreeItemInfo (CTreeCtrl& _containerTree, HTREEITEM _parentItem, const char* _fieldName):
			containerTree (_containerTree), parentItem (_parentItem), fieldName (_fieldName) {}

	CTreeCtrl& containerTree;
	HTREEITEM parentItem;
	CString fieldName;
};

/*==============================================================================
	Base class for the tree visualization.
	Each item of these is related to a entry (HTREEITEM) in the overall
	tree.
==============================================================================*/
class TAMTreeItemBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TAMTreeItemBase (const TAMTreeItemInfo& _info):	info (_info),thisItem (NULL) {}

		/*--------------------------------------------------------------------------
			VIRTUAL DESTRUCTOR
		--------------------------------------------------------------------------*/
		virtual ~TAMTreeItemBase () {}

		/*--------------------------------------------------------------------------
			Initialize the item
		--------------------------------------------------------------------------*/
		virtual void Initialize (HTREEITEM previousOne);

		/*--------------------------------------------------------------------------
			Returns the item text
		--------------------------------------------------------------------------*/
		virtual CString GetItemText () const {return info.fieldName;}

		/*--------------------------------------------------------------------------
			Reacts to the right-mouse click
		--------------------------------------------------------------------------*/
		virtual void RightButtonClick (CWnd* pWnd, CPoint point);

		/*--------------------------------------------------------------------------
			Manages the command coming back from the menu
		--------------------------------------------------------------------------*/
		virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam);

		/*--------------------------------------------------------------------------
			Manages the command coming back from the menu
		--------------------------------------------------------------------------*/
		virtual BOOL InternalOnCommand (WPARAM wParam, LPARAM lParam);

		/*--------------------------------------------------------------------------
			Returns associated data
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* GetData () const = 0;

		/*--------------------------------------------------------------------------
			Deletes a branch completely
		--------------------------------------------------------------------------*/
		void DeleteBranch (HTREEITEM toBeDeleted) {DeleteBranch (toBeDeleted, info.containerTree);}

		/*--------------------------------------------------------------------------
			Deletes a branch completely
		--------------------------------------------------------------------------*/
		static void DeleteBranch (HTREEITEM toBeDeleted, CTreeCtrl& containerTree);

		/*--------------------------------------------------------------------------
			Refresh item text
		--------------------------------------------------------------------------*/
		void RefreshItemText () const;

		TAMTreeItemInfo info;

		/*--------------------------------------------------------------------------
			Select this item in the tree
		--------------------------------------------------------------------------*/
		void Select () {info.containerTree.SelectItem (thisItem);}

	protected:
		/*--------------------------------------------------------------------------
			Returns the parent object
		--------------------------------------------------------------------------*/
		TAMTreeItemBase* GetParent () const;

		/*--------------------------------------------------------------------------
			Populates the children menu. This is used to add to the children the
			menus required by their parents (like, for example, "delete item").
		--------------------------------------------------------------------------*/
		virtual void PopulateChildrenMenu (TAMTreeItemBase* child, CMenu& popupMenu) {}

		/*--------------------------------------------------------------------------
			Populate the popup menu with our settings
		--------------------------------------------------------------------------*/
		virtual void PopulateMyMenu (CMenu& popupMenu) {}

		/*--------------------------------------------------------------------------
			Finds a children managing the given data. Returns NULL if not found.
		--------------------------------------------------------------------------*/
		HTREEITEM FindChild (TEDDataBase* data) const;

		HTREEITEM thisItem;
};

/*==============================================================================
	Object representing a structure
==============================================================================*/
class TAMTreeItemStruct: public TAMTreeItemBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TAMTreeItemStruct (const TAMTreeItemInfo& _info, TEDDataStruct* _data):
			TAMTreeItemBase (_info), data (_data) {}

		/*--------------------------------------------------------------------------
			Initialize the item
		--------------------------------------------------------------------------*/
		virtual void Initialize (HTREEITEM previousOne);

		/*--------------------------------------------------------------------------
			Populate the popup menu with our settings
		--------------------------------------------------------------------------*/
		virtual void PopulateMyMenu (CMenu& popupMenu);

		/*--------------------------------------------------------------------------
			Populates the children menu. This is used to add to the children the
			menus required by their parents (like, for example, "delete item").
		--------------------------------------------------------------------------*/
		virtual void PopulateChildrenMenu (TAMTreeItemBase* child, CMenu& popupMenu);

		/*--------------------------------------------------------------------------
			Manages the command coming back from the menu
		--------------------------------------------------------------------------*/
		virtual BOOL InternalOnCommand (WPARAM wParam, LPARAM lParam);

	protected:
		/*--------------------------------------------------------------------------
			Returns associated data
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* GetData () const {return data;}

		/*--------------------------------------------------------------------------
			Returns the name for field i
		--------------------------------------------------------------------------*/
		CString GetFieldName (unsigned i) const;

		TEDDataStruct* data;
};

/*==============================================================================
	Object representing an union
==============================================================================*/
class TAMTreeItemUnion: public TAMTreeItemBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TAMTreeItemUnion (const TAMTreeItemInfo& _info, TEDDataUnion* _data):
			TAMTreeItemBase (_info), data (_data) {}

		/*--------------------------------------------------------------------------
			Initialize the item
		--------------------------------------------------------------------------*/
		virtual void Initialize (HTREEITEM previousOne);

		/*--------------------------------------------------------------------------
			Returns associated data
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* GetData () const {return data;}

		/*--------------------------------------------------------------------------
			Populate the popup menu with our settings
		--------------------------------------------------------------------------*/
		virtual void PopulateMyMenu (CMenu& popupMenu);

		/*--------------------------------------------------------------------------
			Manages the command coming back from the menu
		--------------------------------------------------------------------------*/
		virtual BOOL InternalOnCommand (WPARAM wParam, LPARAM lParam);

	protected:
		TEDDataUnion* data;
};

/*==============================================================================
	Object representing a sequence
==============================================================================*/
class TAMTreeItemSequence: public TAMTreeItemBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TAMTreeItemSequence (const TAMTreeItemInfo& _info, TEDDataSequence* _data):
			TAMTreeItemBase (_info), data (_data) {}

		/*--------------------------------------------------------------------------
			Initialize the item
		--------------------------------------------------------------------------*/
		virtual void Initialize (HTREEITEM previousOne);

		/*--------------------------------------------------------------------------
			Returns associated data
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* GetData () const {return data;}

		/*--------------------------------------------------------------------------
			Populate the popup menu with our settings
		--------------------------------------------------------------------------*/
		virtual void PopulateMyMenu (CMenu& popupMenu);

		/*--------------------------------------------------------------------------
			Populates the children menu. This is used to add to the children the
			menus required by their parents (like, for example, "delete item").
		--------------------------------------------------------------------------*/
		virtual void PopulateChildrenMenu (TAMTreeItemBase* child, CMenu& popupMenu);

		/*--------------------------------------------------------------------------
			Manages the command coming back from the menu
		--------------------------------------------------------------------------*/
		virtual BOOL InternalOnCommand (WPARAM wParam, LPARAM lParam);

	protected:
		TEDDataSequence* data;

		/*--------------------------------------------------------------------------
			Finds the position of the given entry or (unsiged)(-1) if not found.
		--------------------------------------------------------------------------*/
		unsigned Find (TAMTreeItemBase* child) const;

		/*--------------------------------------------------------------------------
			Renumber children
		--------------------------------------------------------------------------*/
		void RenumberChildren () const;
};

/*==============================================================================
	Object representing a integer
==============================================================================*/
class TAMTreeItemInteger: public TAMTreeItemBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TAMTreeItemInteger (const TAMTreeItemInfo& _info, TEDDataInteger* _data):
			TAMTreeItemBase (_info), data (_data) {}

		/*--------------------------------------------------------------------------
			Returns the item text
		--------------------------------------------------------------------------*/
		virtual CString GetItemText () const;

		/*--------------------------------------------------------------------------
			Populate the popup menu with our settings
		--------------------------------------------------------------------------*/
		virtual void PopulateMyMenu (CMenu& popupMenu);

		/*--------------------------------------------------------------------------
			Manages the command coming back from the menu
		--------------------------------------------------------------------------*/
		virtual BOOL InternalOnCommand (WPARAM wParam, LPARAM lParam);

		/*--------------------------------------------------------------------------
			Returns associated data
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* GetData () const {return data;}

	protected:
		TEDDataInteger* data;
};

/*==============================================================================
	Object representing a integer
==============================================================================*/
class TAMTreeItemEnumerated: public TAMTreeItemInteger {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TAMTreeItemEnumerated (const TAMTreeItemInfo& _info, TEDDataEnumerated* _data):
			TAMTreeItemInteger (_info, _data) {}

		/*--------------------------------------------------------------------------
			Returns the item text
		--------------------------------------------------------------------------*/
		virtual CString GetItemText () const;

		/*--------------------------------------------------------------------------
			Manages the command coming back from the menu
		--------------------------------------------------------------------------*/
		virtual BOOL InternalOnCommand (WPARAM wParam, LPARAM lParam);
};

/*==============================================================================
	Object representing a binary
==============================================================================*/
class TAMTreeItemBinary: public TAMTreeItemBase {
	public:
		/*--------------------------------------------------------------------------
			CONSTRUCTOR
		--------------------------------------------------------------------------*/
		TAMTreeItemBinary (const TAMTreeItemInfo& _info, TEDDataBinary* _data):
			TAMTreeItemBase (_info), data (_data) {}

		/*--------------------------------------------------------------------------
			Returns the item text
		--------------------------------------------------------------------------*/
		virtual CString GetItemText () const;

		/*--------------------------------------------------------------------------
			Returns associated data
		--------------------------------------------------------------------------*/
		virtual TEDDataBase* GetData () const {return data;}

	protected:
		TEDDataBinary* data;
};

/*==============================================================================
	TreeItem factory object
==============================================================================*/
TAMTreeItemBase* CreateNewTreeItemBase (const TAMTreeItemInfo& info, TEDDataBase* data, HTREEITEM previousOne=TVI_LAST);

int AccessDecode (const char* text, CTreeCtrl& messageView, CWnd* window);
int AccessEncode (CString& destination, CTreeCtrl& messageView, CWnd* window);
int AccessNew (CTreeCtrl& messageView, CWnd* window);

#endif //__TCURRTREEPOS_H