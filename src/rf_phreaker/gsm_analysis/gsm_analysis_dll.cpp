/*************************************************************************
// Created 27 Nov 2007 by Dhaval Dave'
// Ported to MSVS2005 for Wider Data Recorder as built by Diarcy.
// GSM Analysis DLL.cpp : Defines the initialization routines for the DLL.
//
*************************************************************************/

#include "stdafx.h"
#include "GSM Analysis DLL.h"
#include "GSM Analysis Data.h"
#include "resource.h"
#include <WiderCustomResourceManager.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// Global data that will be exported from this DLL
// These might need to be declared as simple "extern" in netstart.h
__declspec(dllexport) SuGSMDebugSettings GsmDebugSettings;

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CGSMAnalysisDLLApp

BEGIN_MESSAGE_MAP(CGSMAnalysisDLLApp, CWinApp)
	//{{AFX_MSG_MAP(CGSMAnalysisDLLApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CGSMAnalysisDLLApp::CGSMAnalysisDLLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	GsmDebugSettings.bBSIC = false;
	GsmDebugSettings.bCGI = false;
	GsmDebugSettings.bProcTime = false;
	GsmDebugSettings.bXCorr = false;
}

BOOL CGSMAnalysisDLLApp::InitInstance()
{
	return CWinApp::InitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CGSMAnalysisDLLApp object

CGSMAnalysisDLLApp theApp;

