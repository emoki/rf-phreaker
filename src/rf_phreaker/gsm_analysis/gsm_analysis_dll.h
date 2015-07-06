// GSM Analysis DLL.h : main header file for the GSM ANALYSIS DLL DLL
//

#if !defined(AFX_GSMANALYSISDLL_H__C1928716_0976_436D_ADBC_F4CDFF2DB212__INCLUDED_)
#define AFX_GSMANALYSISDLL_H__C1928716_0976_436D_ADBC_F4CDFF2DB212__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CGSMAnalysisDLLApp
// See GSM Analysis DLL.cpp for the implementation of this class
//

class CGSMAnalysisDLLApp : public CWinApp
{
public:
	CGSMAnalysisDLLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGSMAnalysisDLLApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGSMAnalysisDLLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL InitInstance();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GSMANALYSISDLL_H__C1928716_0976_436D_ADBC_F4CDFF2DB212__INCLUDED_)
