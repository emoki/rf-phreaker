/*******************************************************************************
  TAccessToMFCInterface.cpp  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "stdafx.h"
#include "ed_c_access.h"
#include "TAccessToMFCInterface.h"
#include "ed_c_recog.h"
#include "bitencode.h"
#include "Uplink.h"
#include "EnDecEditApplication/resource.h"
#include "EnDecEditApplication/EnDecEditValue.h"
#include "EnDecEditApplication/EnDecEditEnum.h"

#define AMCMD_CHANGEVALUE   1000
#define AMCMD_REMOVE_BASE   2000
#define AMCMD_REMOVE_MAX    2999
#define AMCMD_ADD_BASE      3000
#define AMCMD_ADD_MAX       3999

#define AMCMD_TOPARENT_FLAG 0x8000
#define AMCMD_TEXT_SIZE 512

/*--------------------------------------------------------------------------
	CONSTRUCTOR
--------------------------------------------------------------------------*/
TUserInterface::TUserInterface (): text (NULL) {
	text = new char [AMCMD_TEXT_SIZE];
	memset (text, 0, AMCMD_TEXT_SIZE);
}

/*--------------------------------------------------------------------------
	DESTRUCTOR
--------------------------------------------------------------------------*/
TUserInterface::~TUserInterface ()
{
	delete [] text;
}

/*--------------------------------------------------------------------------
	Add message
--------------------------------------------------------------------------*/
void TUserInterface::AddMessage (const char* messageText)
{
	int len = strlen (text);
	for (; (*messageText) && len < (AMCMD_TEXT_SIZE-4); messageText++) {
		switch (*messageText) {
			case '\r': break;
			case '\n': strcpy (text+len, "\r\n"); len+=2; break;
			default: {
				text [len] = (*messageText);
				len++;
			}
		}
	}
}


/*==============================================================================
	TreeItem factory object
==============================================================================*/
TAMTreeItemBase* CreateNewTreeItemBase (const TAMTreeItemInfo& info, TEDDataBase* data, HTREEITEM previousOne)
{
	TAMTreeItemBase* ret = NULL;
	if (data->GetClass ()->IsA (TED_ACC_STRUCT))       {ret = new TAMTreeItemStruct   (info, EDAccessCast<TEDDataStruct*>  (data));}
	else if (data->GetClass ()->IsA (TED_ACC_UNION))   {ret = new TAMTreeItemUnion    (info, EDAccessCast<TEDDataUnion*>   (data));}
	else if (data->GetClass ()->IsA (TED_ACC_ENUMERATED)) {ret = new TAMTreeItemEnumerated (info, EDAccessCast<TEDDataEnumerated*> (data));}
	else if (data->GetClass ()->IsA (TED_ACC_INTEGER)) {ret = new TAMTreeItemInteger  (info, EDAccessCast<TEDDataInteger*> (data));}
	else if (data->GetClass ()->IsA (TED_ACC_BINARY))  {ret = new TAMTreeItemBinary   (info, EDAccessCast<TEDDataBinary*>  (data));}
	else if (data->GetClass ()->IsA (TED_ACC_SEQUENCE)){ret = new TAMTreeItemSequence (info, EDAccessCast<TEDDataSequence*>(data));}
	else ret = NULL;

	if (ret != NULL) ret->Initialize (previousOne);

	return ret;
}


/*--------------------------------------------------------------------------
	Initialize the item
--------------------------------------------------------------------------*/
void TAMTreeItemBase::Initialize (HTREEITEM previousOne)
{
	thisItem = info.containerTree.InsertItem (GetItemText (), (info.parentItem == NULL ? TVI_ROOT : info.parentItem), previousOne);
	info.containerTree.SetItemData (thisItem, (DWORD)this);
}

/*--------------------------------------------------------------------------
	Returns the parent object
--------------------------------------------------------------------------*/
TAMTreeItemBase* TAMTreeItemBase::GetParent () const
{
	if (info.parentItem == NULL) return NULL;
	return (TAMTreeItemBase*)(info.containerTree.GetItemData (info.parentItem));
}

/*--------------------------------------------------------------------------
	Deletes a branch completely
--------------------------------------------------------------------------*/
void TAMTreeItemBase::DeleteBranch (HTREEITEM toBeDeleted, CTreeCtrl& containerTree)
{
	HTREEITEM child;
	while ((child = containerTree.GetChildItem (toBeDeleted)) != NULL) {
		DeleteBranch (child, containerTree);
	}
	TAMTreeItemBase* treeItem = (TAMTreeItemBase*)(containerTree.GetItemData (toBeDeleted));
	if (treeItem) delete treeItem;
	containerTree.DeleteItem (toBeDeleted);
}


/*--------------------------------------------------------------------------
	Finds a children managing the given data. Returns NULL if not found.
--------------------------------------------------------------------------*/
HTREEITEM TAMTreeItemBase::FindChild (TEDDataBase* itemSearched) const
{
	// Find among my children the required one.
	HTREEITEM child, ret = NULL;
	for (child = info.containerTree.GetChildItem (thisItem); child != NULL; child = info.containerTree.GetNextSiblingItem (child)) {
		TAMTreeItemBase* treeItem = (TAMTreeItemBase*)(info.containerTree.GetItemData (child));
		if (treeItem->GetData () == itemSearched) {
			ret = child;
			break;
		}						
	}
	return ret;
}

/*--------------------------------------------------------------------------
	Refresh item text
--------------------------------------------------------------------------*/
void TAMTreeItemBase::RefreshItemText () const
{
	info.containerTree.SetItemText (thisItem, GetItemText ());
}

/*--------------------------------------------------------------------------
	Reacts to the right-mouse click
--------------------------------------------------------------------------*/
void TAMTreeItemBase::RightButtonClick (CWnd* pWnd, CPoint point)
{
	CMenu myMenu;
	myMenu.CreatePopupMenu ();
//	myMenu.AppendMenu (MF_BYPOSITION|MF_STRING, 100, "Primo");
	PopulateMyMenu (myMenu);
	if (GetParent ()) GetParent ()->PopulateChildrenMenu (this, myMenu);
	myMenu.TrackPopupMenu (TPM_RIGHTBUTTON, point.x, point.y, pWnd);
}

/*--------------------------------------------------------------------------
	Manages the command coming back from the menu
--------------------------------------------------------------------------*/
BOOL TAMTreeItemBase::OnCommand (WPARAM wParam, LPARAM lParam)
{
	WORD wID = LOWORD(wParam);
	if ((wID & AMCMD_TOPARENT_FLAG) == AMCMD_TOPARENT_FLAG) {
		wID &= ~AMCMD_TOPARENT_FLAG;
		wParam = MAKEWPARAM (wID, HIWORD (wParam));
		return GetParent ()->InternalOnCommand (wParam, lParam);
	}
	return InternalOnCommand (wParam, lParam);
}

/*--------------------------------------------------------------------------
	Manages the command coming back from the menu
--------------------------------------------------------------------------*/
BOOL TAMTreeItemBase::InternalOnCommand (WPARAM wParam, LPARAM lParam)
{
	if (GetParent ()) return GetParent ()->InternalOnCommand (wParam, lParam);
	return FALSE;
}

/*--------------------------------------------------------------------------
	Returns the name for field i
--------------------------------------------------------------------------*/
CString TAMTreeItemStruct::GetFieldName (unsigned i) const
{
	CString ret;
	const TEDClassStruct& cls = *(EDAccessCast<const TEDClassStruct*>(data->GetClass ()));
	if (cls.GetFieldInfo (i).GetIsOptional ()) {
		ret.Format ("%s [OPT]", cls.GetFieldInfo (i).GetFieldName ());
	} else {
		ret.Format ("%s", cls.GetFieldInfo (i).GetFieldName ());
	}
	return ret;
}

/*--------------------------------------------------------------------------
	Initialize the item
--------------------------------------------------------------------------*/
void TAMTreeItemStruct::Initialize (HTREEITEM previousOne)
{
	TAMTreeItemBase::Initialize (previousOne);
	unsigned i;
	const TEDClassStruct& cls = *(EDAccessCast<const TEDClassStruct*>(data->GetClass ()));
	for (i=0; i<cls.Count (); i++) {
		if (data->GetElement (i) != NULL) {
			TAMTreeItemInfo newInfo (info.containerTree, thisItem, GetFieldName (i));
			CreateNewTreeItemBase (newInfo, data->GetElement (i));
		}
	}
}

/*--------------------------------------------------------------------------
	Manages the command coming back from the menu
--------------------------------------------------------------------------*/
BOOL TAMTreeItemStruct::InternalOnCommand (WPARAM wParam, LPARAM lParam)
{
	WORD wID = LOWORD(wParam);
	const TEDClassStruct& cls = *(EDAccessCast<const TEDClassStruct*>(data->GetClass ()));

	if (wID >= AMCMD_REMOVE_BASE && wID <= AMCMD_REMOVE_MAX) {
		// Find the item at 'position'
		unsigned position = wID-(AMCMD_REMOVE_BASE);
		if (data->IsPresent (position)) {
			TEDDataBase* itemSearched = data->GetElement (position);
			// Find among my children the required one.
			HTREEITEM child = FindChild (itemSearched);
			if (child != NULL) {
				// Ok, found. We delete the tree entry
				DeleteBranch (child);
				// We set to NULL the entry in the structure
				data->SetElement (position, NULL);
			}
		}
		return TRUE;
	}
	if (wID >= AMCMD_ADD_BASE && wID <= AMCMD_ADD_MAX) {
		// Find the item at 'position'
		unsigned position = wID-(AMCMD_ADD_BASE);
		if (!data->IsPresent (position)) {
			TEDDataBase* newItem = cls.GetFieldInfo (position).GetFieldClass ().NewInstance ();
			data->SetElement (position, newItem);

			TAMTreeItemInfo newInfo (info.containerTree, thisItem, GetFieldName (position));
			CreateNewTreeItemBase (newInfo, newItem)->Select ();
		}
		return TRUE;
	}
	return TAMTreeItemBase::InternalOnCommand (wParam, lParam);
}

/*--------------------------------------------------------------------------
	Populate the popup menu with our settings
--------------------------------------------------------------------------*/
void TAMTreeItemStruct::PopulateMyMenu (CMenu& popupMenu)
{
	unsigned i;
	const TEDClassStruct& cls = *(EDAccessCast<const TEDClassStruct*>(data->GetClass ()));
	for (i=0; i<cls.Count (); i++) {
		if (cls.GetFieldInfo (i).GetIsOptional ()) {
			if (!data->IsPresent (i)) {
				CString Text;
				Text.Format ("Activate opt. field '%s'", cls.GetFieldInfo (i).GetFieldName ());
				popupMenu.AppendMenu (MF_STRING, AMCMD_ADD_BASE+i, Text);
			} else {
				CString Text;
				Text.Format ("Remove opt. field '%s'", cls.GetFieldInfo (i).GetFieldName ());
				popupMenu.AppendMenu (MF_STRING, AMCMD_REMOVE_BASE+i, Text);
			}
		}
	}
}

/*--------------------------------------------------------------------------
	Populates the children menu. This is used to add to the children the
	menus required by their parents (like, for example, "delete item").
--------------------------------------------------------------------------*/
void TAMTreeItemStruct::PopulateChildrenMenu (TAMTreeItemBase* child, CMenu& popupMenu) 
{
	unsigned i;
	const TEDClassStruct& cls = *(EDAccessCast<const TEDClassStruct*>(data->GetClass ()));
	for (i=0; i<cls.Count (); i++) {
		if (data->GetElement (i) == child->GetData ()) {
			if (cls.GetFieldInfo (i).GetIsOptional ()) {
				popupMenu.AppendMenu (MF_STRING, AMCMD_TOPARENT_FLAG|(AMCMD_REMOVE_BASE+i), "Delete from parent struct");
			}
			break;
		}
	}
}


/*--------------------------------------------------------------------------
	Initialize the item
--------------------------------------------------------------------------*/
void TAMTreeItemSequence::Initialize (HTREEITEM previousOne)
{
	TAMTreeItemBase::Initialize (previousOne);
	const TEDClassSequence& cls = *(EDAccessCast<const TEDClassSequence*>(data->GetClass ()));
	unsigned i;
	for (i=0; i<data->Count (); i++) {
		CString fieldName = "";
		fieldName.Format ("[%02d]", i);
		TAMTreeItemInfo newInfo (info.containerTree, thisItem, fieldName);
		CreateNewTreeItemBase (newInfo, data->GetElement (i));
	}
}

/*--------------------------------------------------------------------------
	Initialize the item
--------------------------------------------------------------------------*/
void TAMTreeItemUnion::Initialize (HTREEITEM previousOne)
{
	TAMTreeItemBase::Initialize (previousOne);
	const TEDClassUnion& cls = *(EDAccessCast<const TEDClassUnion*>(data->GetClass ()));

	unsigned active = data->GetActiveEntry ();
	assert (data->GetElement () != NULL);

	TAMTreeItemInfo newInfo (info.containerTree, thisItem, cls.GetFieldInfo (active).GetFieldName ());
	CreateNewTreeItemBase (newInfo, data->GetElement ());
}

/*--------------------------------------------------------------------------
	Populate the popup menu with our settings
--------------------------------------------------------------------------*/
void TAMTreeItemUnion::PopulateMyMenu (CMenu& popupMenu)
{
	unsigned i;
	const TEDClassUnion& cls = *(EDAccessCast<const TEDClassUnion*>(data->GetClass ()));
	for (i=0; i<cls.Count (); i++) {
		CString Text;
		Text.Format ("Set field '%s'", cls.GetFieldInfo (i).GetFieldName ());
		popupMenu.AppendMenu (MF_STRING|(data->GetActiveEntry ()==i?MF_CHECKED:0), AMCMD_ADD_BASE+i, Text);
	}
}

/*--------------------------------------------------------------------------
	Manages the command coming back from the menu
--------------------------------------------------------------------------*/
BOOL TAMTreeItemUnion::InternalOnCommand (WPARAM wParam, LPARAM lParam)
{
	WORD wID = LOWORD(wParam);
	const TEDClassUnion& cls = *(EDAccessCast<const TEDClassUnion*>(data->GetClass ()));

	if (wID >= AMCMD_ADD_BASE && wID <= AMCMD_ADD_MAX) {
		// Find the item at 'position'
		unsigned position = wID-(AMCMD_ADD_BASE);
		if (data->GetActiveEntry () != position) {
			HTREEITEM item = info.containerTree.GetChildItem (thisItem);
			DeleteBranch (item);
			TEDDataBase* newItem = cls.GetFieldInfo (position).GetFieldClass ().NewInstance ();
			data->SetElement (position, newItem);

			TAMTreeItemInfo newInfo (info.containerTree, thisItem, cls.GetFieldInfo (position).GetFieldName ());
			CreateNewTreeItemBase (newInfo, newItem)->Select ();
		}
		return TRUE;
	}
	return TAMTreeItemBase::InternalOnCommand (wParam, lParam);
}

/*--------------------------------------------------------------------------
	Returns the item text
--------------------------------------------------------------------------*/
CString TAMTreeItemInteger::GetItemText () const
{
	CString val;
	const TEDClassInteger& cls = *(EDAccessCast<const TEDClassInteger*>(data->GetClass ()));
	switch (cls.GetBitSize ()) {
		case 0: val = "PRESENT"; break;
		case 1: val = (data->GetValue ()? "true" : "false"); break;
		default: val.Format ("%d", data->GetValue ());
	}

	CString ret = info.fieldName;
	ret += ": ";
	ret += val;
	return ret;
}

/*--------------------------------------------------------------------------
	Populate the popup menu with our settings
--------------------------------------------------------------------------*/
void TAMTreeItemInteger::PopulateMyMenu (CMenu& popupMenu)
{
	popupMenu.AppendMenu (MF_STRING, AMCMD_CHANGEVALUE, "&Edit");
}

/*--------------------------------------------------------------------------
	Manages the command coming back from the menu
--------------------------------------------------------------------------*/
BOOL TAMTreeItemInteger::InternalOnCommand (WPARAM wParam, LPARAM lParam)
{
	WORD wID = LOWORD(wParam);
	if (wID == AMCMD_CHANGEVALUE) {
		const TEDClassInteger& cls = *(EDAccessCast<const TEDClassInteger*>(data->GetClass ()));
		CEnDecEditValue editValueDlg;
		editValueDlg.m_Value = data->GetValue ();
		if (cls.GetBitSize () == 32) editValueDlg.maxValue = 0xFFFFFFFF;
		else editValueDlg.maxValue = (1 << cls.GetBitSize ())-1;
		if (editValueDlg.DoModal () == IDOK) {
			data->Set (editValueDlg.m_Value);
			RefreshItemText ();
		}
		return TRUE;
	}
	return TAMTreeItemBase::InternalOnCommand (wParam, lParam);
}

/*--------------------------------------------------------------------------
	Returns the item text
--------------------------------------------------------------------------*/
CString TAMTreeItemEnumerated::GetItemText () const
{
	CString val = "unknown";
	const TEDClassEnumerated& cls = *(EDAccessCast<const TEDClassEnumerated*>(data->GetClass ()));

	unsigned i;
	long l = data->GetValue ();
	for (i=0; i<cls.Count (); i++) {
		if (cls.GetValue (i) == l) {
			val.Format ("%s (%d)", cls.GetLabel (i), l);
			break;
		}
	}

	CString ret = info.fieldName;
	ret += ": ";
	ret += val;
	return ret;
}

/*--------------------------------------------------------------------------
	Manages the command coming back from the menu
--------------------------------------------------------------------------*/
BOOL TAMTreeItemEnumerated::InternalOnCommand (WPARAM wParam, LPARAM lParam)
{
	WORD wID = LOWORD(wParam);
	if (wID == AMCMD_CHANGEVALUE) {
		CEnDecEditEnum editValueDlg (EDAccessCast<TEDDataEnumerated*>(data));
		if (editValueDlg.DoModal () == IDOK) {
			RefreshItemText ();
		}
		return TRUE;
	}
	return TAMTreeItemInteger::InternalOnCommand (wParam, lParam);
}


/*--------------------------------------------------------------------------
	Returns the item text
--------------------------------------------------------------------------*/
CString TAMTreeItemBinary::GetItemText () const
{
	CString val;
	const TEDClassBinary& cls = *(EDAccessCast<const TEDClassBinary*>(data->GetClass ()));
	CString ret = info.fieldName;
	ret += ": <binary data>";
	return ret;
}


/*--------------------------------------------------------------------------
	Finds the position of the given entry or (unsiged)(-1) if not found.
--------------------------------------------------------------------------*/
unsigned TAMTreeItemSequence::Find (TAMTreeItemBase* child) const
{
	unsigned i;
	for (i=0; i<data->Count (); i++) {
		if (data->GetElement (i) == child->GetData ()) return i;
	}
	return (unsigned)-1;
}

/*--------------------------------------------------------------------------
	Populate the popup menu with our settings
--------------------------------------------------------------------------*/
void TAMTreeItemSequence::PopulateMyMenu (CMenu& popupMenu)
{
	const TEDClassSequence& cls = *(EDAccessCast<const TEDClassSequence*>(data->GetClass ()));
	if (cls.GetIsFixed ()) return;	

	if (data->Count () < cls.GetMaxItems ()) {
		popupMenu.AppendMenu (MF_STRING, AMCMD_ADD_BASE+data->Count (), "Add");
	} else {
		CString Text;
		Text.Format ("Add (limit of %d items reached)", cls.GetMaxItems ());
		popupMenu.AppendMenu (MF_STRING|MF_GRAYED|MF_DISABLED, 0, Text);
	}
}

/*--------------------------------------------------------------------------
	Populates the children menu. This is used to add to the children the
	menus required by their parents (like, for example, "delete item").
--------------------------------------------------------------------------*/
void TAMTreeItemSequence::PopulateChildrenMenu (TAMTreeItemBase* child, CMenu& popupMenu)
{
	const TEDClassSequence& cls = *(EDAccessCast<const TEDClassSequence*>(data->GetClass ()));
	if (cls.GetIsFixed ()) return;

	unsigned i = Find (child);
	if (i != (unsigned)-1) {
		popupMenu.AppendMenu (MF_STRING, AMCMD_TOPARENT_FLAG|(AMCMD_REMOVE_BASE+i), "Delete from parent struct");
		if (data->Count () < cls.GetMaxItems ()) {
			popupMenu.AppendMenu (MF_STRING, AMCMD_TOPARENT_FLAG|(AMCMD_ADD_BASE+i), "Insert before");
			popupMenu.AppendMenu (MF_STRING, AMCMD_TOPARENT_FLAG|(AMCMD_ADD_BASE+i+1), "Insert after");
		}
	}
}

/*--------------------------------------------------------------------------
	Renumber children
--------------------------------------------------------------------------*/
void TAMTreeItemSequence::RenumberChildren () const
{
	unsigned i;
	HTREEITEM child = info.containerTree.GetChildItem (thisItem);
	for (i=0; i<data->Count (); i++) {
		assert (child);

		//HTREEITEM child = FindChild (data->GetElement (i));
		assert (child != NULL);
		TAMTreeItemBase* treeItem = (TAMTreeItemBase*)(info.containerTree.GetItemData (child));
		treeItem->info.fieldName.Format ("[%02d]", i);
		treeItem->RefreshItemText ();
		child = info.containerTree.GetNextSiblingItem (child);
	}
}


/*--------------------------------------------------------------------------
	Manages the command coming back from the menu
--------------------------------------------------------------------------*/
BOOL TAMTreeItemSequence::InternalOnCommand (WPARAM wParam, LPARAM lParam)
{
	const TEDClassSequence& cls = *(EDAccessCast<const TEDClassSequence*>(data->GetClass ()));
	WORD wID = LOWORD(wParam);
	BOOL ret = FALSE;

	if (wID >= AMCMD_REMOVE_BASE && wID <= AMCMD_REMOVE_MAX) {
		// Find the item at 'position'
		unsigned position = wID-(AMCMD_REMOVE_BASE);
		if (position < data->Count ()) {
			TEDDataBase* itemSearched = data->GetElement (position);
			// Find among my children the required one.
			HTREEITEM child = FindChild (itemSearched);
			if (child != NULL) {
				// Ok, found. We delete the tree entry
				DeleteBranch (child);
				data->DelElement (position);
				RenumberChildren ();
			}						
		}
		ret = TRUE;
	} else if (wID >= AMCMD_ADD_BASE && wID <= AMCMD_ADD_MAX) {
		// Find the item at 'position'
		unsigned position = wID-(AMCMD_ADD_BASE);
		TEDDataBase* newItem = cls.GetSequencedClass ()->NewInstance ();

		HTREEITEM nextChild;
		if (position == 0) nextChild = NULL;
		else if (position >= data->Count ()) nextChild = TVI_LAST;
		else {
			TEDDataBase* itemSearched = data->GetElement (position-1);
			nextChild = FindChild (itemSearched);
		}

		data->InsertElement (newItem, position);
		CString Text;
		Text.Format ("[%02d]", position);
		TAMTreeItemInfo newInfo (info.containerTree, thisItem, Text);
		CreateNewTreeItemBase (newInfo, newItem, nextChild)->Select ();
		RenumberChildren ();
		ret = TRUE;
	}
	else ret = TAMTreeItemBase::InternalOnCommand (wParam, lParam);

	return ret;
}


void AccessDumpBinary (ostream& dumpfile, const char* name, const char* p, int len)
{
	bool newLine = false;
	int i, j;
	dumpfile << "/*---------------------------------------------" << endl;
	dumpfile << "  " << name << " len=" << len << endl;
	dumpfile << "---------------------------------------------*/" << endl;
	for (i=0; len>0; i++) {
		newLine = false;
		char Buf [40];
		sprintf (Buf, "/* 0x%08X: */ '\\x%02X'%c /* (%03d) - ", (unsigned int)i, (unsigned int)((unsigned char)(p[i])), (len>7?',':' '), (unsigned int)((unsigned char)(p[i])));
		dumpfile << Buf;
		for (j=0; j<8; j++) {
			if (len == 0) break;
			if (p[i] & (1 << (7-j))) dumpfile << "1";
			else dumpfile << "0";
			len --;
		}
		dumpfile << "*/" << endl;
	}
	dumpfile << "/*---------------------------------------------*/" << endl;
	dumpfile.flush ();
}


int AccessDecode (const char* Text, CTreeCtrl& MessageView, CWnd* Window)
{
	int len;
	const char* String = BitEncode (Text, &len);
	//MessageView.DeleteAllItems ();
	if (len == BE_ERROR_LEN) {
		Window->MessageBox (String, "Error in source string", MB_OK);
		return -1000;
	}

	TUplink_Data* data = new TUplink_Data;
	TUserInterface userInterface;
	int Ret = SetDecode_Uplink (String, data, len, userInterface);
	if (Ret < 0) {
		CString Message;
		Message += "Decoder reported the following error: ";
		switch (Ret) {
			case ED_MISSING_OPTIONAL                : Message += "MISSING OPTIONAL"; break;
			case ED_SYNTAX_ERROR                    : Message += "SYNTAX ERROR"; break;
			case ED_UNKNOWN_MESSAGE                 : Message += "UNKNOWN MESSAGE"; break;
			case ED_UNKNOWN_IEI                     : Message += "UNKNOWN IEI"; break;
			case ED_MESSAGE_TOO_SHORT               : Message += "MESSAGE TOO SHORT"; break;
			case ED_MISSING_REQUIRED_CONDITIONAL_IE : Message += "MISSING REQUIRED CONDITIONAL IE"; break;
			case ED_FOUND_UNEXPECTED_CONDITIONAL_IE : Message += "FOUND UNEXPECTED CONDITIONAL IE"; break;
			case ED_MANDATORY_IE_SYNTAX_ERROR       : Message += "MANDATORY IE SYNTAX ERROR"; break;
			case ED_CONDITIONAL_IE_SYNTAX_ERROR     : Message += "CONDITIONAL IE SYNTAX ERROR"; break;
			case ED_OPTIONAL_IE_SYNTAX_ERROR        : Message += "OPTIONAL IE SYNTAX ERROR"; break;
			case ED_FIELD_OUT_OF_RANGE              : Message += "FIELD OUT OF RANGE"; break;
			default: Message += "UNKNOWN ERROR #" + Ret;
		}
		Message += "\r\n";
		Message += userInterface.text;
		Window->MessageBox (Message, "Error decoding message", MB_OK);
		delete data;
		return Ret;
	}

	//TAccessToMFCInterface AccessToMFCInterfnace (MessageView);
	TEDDataBase* decodedData = AccessGetSet_Uplink (data);
	//TEDDataBase* decodedData = AccessGet_Uplink (data);
	delete data;
	TAMTreeItemInfo info (MessageView, NULL, "Decoded Uplink Message");
	//TAMTreeItemInfo info (MessageView, NULL, decodedData->GetClass ()->GetClassName ());
	CreateNewTreeItemBase (info, decodedData);

	return Ret;
}


int AccessEncode (CString& destination, CTreeCtrl& messageView, CWnd* window)
{
	// Find the rootmost item
	HTREEITEM item = messageView.GetSelectedItem ();
	if (item == NULL) {
		window->MessageBox ("Can't encode: no messages selected!", "Error encoding", MB_OK);
		return -1;
	}
	
	while (messageView.GetParentItem (item)) item = messageView.GetParentItem (item);
	messageView.SelectItem (item);

	TAMTreeItemBase* treeItem = (TAMTreeItemBase*)(messageView.GetItemData (item));
	TEDDataBase* decodedData = treeItem->GetData ();

	TUplink_Data* data = new TUplink_Data;
	INIT_TUplink_Data (data);
	AccessSet_Uplink (data, decodedData);
	
	#define BUFSIZE 2048
	unsigned char* buffer = new unsigned char [BUFSIZE];
	memset (buffer, 0, BUFSIZE);

	TUserInterface userInterface;
	int len = SetEncode_Uplink ((char*)buffer, 0, data, userInterface);
	delete data;

	if (len < 0) {
		destination.Format (
			"Error encoding the message: function returned %d!\r\n"
			"Probably the selected source message below is not coherent.\r\n"
			"Check that those information elements encoded with CSN.1\r\n"
			"have all the required optional fields active.\r\n", len);
		destination += userInterface.text;
	} else {
		int i, max;
		max = (len+7)/8;
		destination.Empty ();
		for (i=0; i<max; i++) {
			CString s;
			s.Format ("x%02X ", (unsigned)(buffer [i]));
			destination += s;
			if (((i % 4) == 0) && (i>0)) {
				destination += "\r\n";
			}
		}
	}
	delete [] buffer;
	return 0;
}

int AccessNew (CTreeCtrl& messageView, CWnd* window)
{
	//TAccessToMFCInterface AccessToMFCInterfnace (MessageView);
	TEDDataBase* newItem = AccessClass_Set_Uplink->NewInstance ();
	TAMTreeItemInfo info (messageView, NULL, "New Uplink Message");
	CreateNewTreeItemBase (info, newItem)->Select ();
	return 0;
}
