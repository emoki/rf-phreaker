// EnDecEditValue.cpp : implementation file
//

#include "stdafx.h"
#include "EnDecEditApplication.h"
#include "EnDecEditValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditValue dialog


CEnDecEditValue::CEnDecEditValue(CWnd* pParent /*=NULL*/)
	: CDialog(CEnDecEditValue::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnDecEditValue)
	m_Value = 0;
	//}}AFX_DATA_INIT
}


void CEnDecEditValue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnDecEditValue)
	DDX_Text(pDX, IDC_VALUE, m_Value);
	//}}AFX_DATA_MAP
//// ADDED BY Dafocus - START
	DDV_MinMaxUInt(pDX, m_Value, 0, maxValue);
//// ADDED BY Dafocus - END
}


BEGIN_MESSAGE_MAP(CEnDecEditValue, CDialog)
	//{{AFX_MSG_MAP(CEnDecEditValue)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditValue message handlers
