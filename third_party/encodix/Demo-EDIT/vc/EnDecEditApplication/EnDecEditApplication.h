// EnDecEditApplication.h : main header file for the ENDECAPPLICATION application
//

#if !defined(AFX_ENDECAPPLICATION_H__E953A79E_3401_408D_9E29_F8D0AF094951__INCLUDED_)
#define AFX_ENDECAPPLICATION_H__E953A79E_3401_408D_9E29_F8D0AF094951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditApplicationApp:
// See EnDecEditApplication.cpp for the implementation of this class
//

class CEnDecEditApplicationApp : public CWinApp
{
public:
	CEnDecEditApplicationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnDecEditApplicationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEnDecEditApplicationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDECAPPLICATION_H__E953A79E_3401_408D_9E29_F8D0AF094951__INCLUDED_)
