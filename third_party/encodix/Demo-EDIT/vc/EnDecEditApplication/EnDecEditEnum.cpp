// EnDecEditEnum.cpp : implementation file
//

#include "stdafx.h"
#include "endeceditapplication.h"
#include "EnDecEditEnum.h"
//// ADDED BY Dafocus - START
#include "ed_access.h"
//// ADDED BY Dafocus - END

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditEnum dialog


CEnDecEditEnum::CEnDecEditEnum(
//// ADDED BY Dafocus - START
		TEDDataEnumerated* _accessData,
//// ADDED BY Dafocus - END
	CWnd* pParent /*=NULL*/)
	: CDialog(CEnDecEditEnum::IDD, pParent)

//// ADDED BY Dafocus - START
		, accessData (_accessData)
//// ADDED BY Dafocus - END

{
	//{{AFX_DATA_INIT(CEnDecEditEnum)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEnDecEditEnum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnDecEditEnum)
	DDX_Control(pDX, IDC_ENUMLIST, m_SelectedEnum);
	//}}AFX_DATA_MAP

//// ADDED BY Dafocus - START
	if (!pDX->m_bSaveAndValidate) {
		const TEDClassEnumerated& cls = *(EDAccessCast<const TEDClassEnumerated*>(accessData->GetClass ()));

		unsigned i;
		for (i=0; i<cls.Count (); i++) {
			CString text;
			text.Format ("%s (%d)", cls.GetLabel (i), cls.GetValue (i));
			int pos = m_SelectedEnum.AddString (text);
			m_SelectedEnum.SetItemData (pos, cls.GetValue (i));
			if (cls.GetValue (i) == accessData->GetValue ()) m_SelectedEnum.SetCurSel (pos);
		}
	} else {
		INT selected = m_SelectedEnum.GetCurSel ();
		accessData->Set (m_SelectedEnum.GetItemData (selected));
	}
//// ADDED BY Dafocus - END
}


BEGIN_MESSAGE_MAP(CEnDecEditEnum, CDialog)
	//{{AFX_MSG_MAP(CEnDecEditEnum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditEnum message handlers

