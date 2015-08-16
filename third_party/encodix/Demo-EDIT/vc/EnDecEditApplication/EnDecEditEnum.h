#if !defined(AFX_ENDECEDITENUM_H__FE066688_D2D6_4B7B_A0FB_095147A5D5C9__INCLUDED_)
#define AFX_ENDECEDITENUM_H__FE066688_D2D6_4B7B_A0FB_095147A5D5C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnDecEditEnum.h : header file
//

//// ADDED BY Dafocus - START
class TEDDataEnumerated;
//// ADDED BY Dafocus - END

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditEnum dialog

class CEnDecEditEnum : public CDialog
{
// Construction
public:
	CEnDecEditEnum(
//// ADDED BY Dafocus - START
		TEDDataEnumerated* _accessData,
//// ADDED BY Dafocus - END
		CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnDecEditEnum)
	enum { IDD = IDD_EDENUM };
	CListBox	m_SelectedEnum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnDecEditEnum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnDecEditEnum)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//// ADDED BY Dafocus - START
		TEDDataEnumerated* accessData;
//// ADDED BY Dafocus - END
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDECEDITENUM_H__FE066688_D2D6_4B7B_A0FB_095147A5D5C9__INCLUDED_)
