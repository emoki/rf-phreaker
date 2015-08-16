#if !defined(AFX_ENDECEDITVALUE_H__D832B584_665C_48FC_A80A_5FB8366DC110__INCLUDED_)
#define AFX_ENDECEDITVALUE_H__D832B584_665C_48FC_A80A_5FB8366DC110__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnDecEditValue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditValue dialog

class CEnDecEditValue : public CDialog
{
// Construction
public:
	CEnDecEditValue(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnDecEditValue)
	enum { IDD = IDD_EDVALUE };
	UINT	m_Value;
	//}}AFX_DATA

//// ADDED BY Dafocus - START
	UINT maxValue;
//// ADDED BY Dafocus - END

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnDecEditValue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnDecEditValue)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDECEDITVALUE_H__D832B584_665C_48FC_A80A_5FB8366DC110__INCLUDED_)
