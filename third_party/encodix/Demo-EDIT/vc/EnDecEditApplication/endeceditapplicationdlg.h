// EnDecEditApplicationDlg.h : header file
//

#if !defined(AFX_ENDECAPPLICATIONDLG_H__9E3386BF_CA72_4E26_BFFA_AAE1A1B6E3BC__INCLUDED_)
#define AFX_ENDECAPPLICATIONDLG_H__9E3386BF_CA72_4E26_BFFA_AAE1A1B6E3BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//// ADDED BY Dafocus - START
class TAMTreeItemBase;
//// ADDED BY Dafocus - END

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditApplicationDlg dialog

class CEnDecEditApplicationDlg : public CDialog
{
// Construction
public:
	CEnDecEditApplicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEnDecEditApplicationDlg)
	enum { IDD = IDD_ENDECAPPLICATION_DIALOG };
	CTreeCtrl	m_MessageView;
	CString	m_SourceMessage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnDecEditApplicationDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEnDecEditApplicationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDecode();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEncodeTree();
	afx_msg void OnNewMessage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//// ADDED BY Dafocus - START
	// Item currently working on its popup menu
	TAMTreeItemBase* currentItem;
	//// ADDED BY Dafocus - END
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDECAPPLICATIONDLG_H__9E3386BF_CA72_4E26_BFFA_AAE1A1B6E3BC__INCLUDED_)
