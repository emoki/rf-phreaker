// EnDecEditApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EnDecEditApplication.h"
#include "EnDecEditApplicationDlg.h"

//// ADDED BY Dafocus - START
#include "TAccessToMFCInterface.h"
//// ADDED BY Dafocus - END

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditApplicationDlg dialog

CEnDecEditApplicationDlg::CEnDecEditApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEnDecEditApplicationDlg::IDD, pParent)
//// ADDED BY Dafocus - START
	, currentItem (NULL)
//// ADDED BY Dafocus - END
{
	//{{AFX_DATA_INIT(CEnDecEditApplicationDlg)
	m_SourceMessage = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnDecEditApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnDecEditApplicationDlg)
	DDX_Control(pDX, IDC_DECODEDTREE, m_MessageView);
	DDX_Text(pDX, IDC_SOURCEMESSAGE, m_SourceMessage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEnDecEditApplicationDlg, CDialog)
	//{{AFX_MSG_MAP(CEnDecEditApplicationDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_DECODE, OnDecode)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_ENCODETREE, OnEncodeTree)
	ON_BN_CLICKED(IDC_NEWMESSAGE, OnNewMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnDecEditApplicationDlg message handlers

BOOL CEnDecEditApplicationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEnDecEditApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEnDecEditApplicationDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEnDecEditApplicationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEnDecEditApplicationDlg::OnDecode() 
{
	// TODO: Add your control notification handler code here

	//// ADDED BY Dafocus - START
	//// The method has been added with the wizard
	UpdateData ();
	AccessDecode (m_SourceMessage, m_MessageView, this);
	//// ADDED BY Dafocus - END	
}

void CEnDecEditApplicationDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here

	//// ADDED BY Dafocus - START
	//// The method has been added with the wizard
	if (pWnd == &m_MessageView) {
		unsigned int Flags;
		CPoint winPoint = point;
		m_MessageView.ScreenToClient (&winPoint);
		HTREEITEM itemTargeted = m_MessageView.HitTest (winPoint, &Flags);
		if (itemTargeted != NULL) {
			m_MessageView.SelectItem (itemTargeted);
			currentItem = (TAMTreeItemBase*)m_MessageView.GetItemData (itemTargeted);
			if (currentItem) currentItem->RightButtonClick (this, point);
		}
	}
	//// ADDED BY Dafocus - END	
}

BOOL CEnDecEditApplicationDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	//// ADDED BY Dafocus - START
	BOOL ret = false;
	if (currentItem != NULL) {
		ret = currentItem->OnCommand (wParam, lParam);
		currentItem = NULL;
	}
	if (ret) return ret;
	//// ADDED BY Dafocus - END	
	
	return CDialog::OnCommand(wParam, lParam);
}

BOOL CEnDecEditApplicationDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//// ADDED BY Dafocus - START
	HTREEITEM item;
	while ((item = m_MessageView.GetNextItem (NULL, TVGN_CHILD)) != NULL) {
		TAMTreeItemBase* currentItem = (TAMTreeItemBase*)m_MessageView.GetItemData (item);
		delete currentItem->GetData ();
		TAMTreeItemBase::DeleteBranch (item, m_MessageView);
	}
	//// ADDED BY Dafocus - END
	
	return CDialog::DestroyWindow();
}

void CEnDecEditApplicationDlg::OnEncodeTree() 
{
	// TODO: Add your control notification handler code here
	
	//// ADDED BY Dafocus - START
	//// The method has been added with the wizard
	AccessEncode (m_SourceMessage, m_MessageView, this);
	UpdateData (FALSE);
	//// ADDED BY Dafocus - END	
}

void CEnDecEditApplicationDlg::OnNewMessage() 
{
	// TODO: Add your control notification handler code here
	
	//// ADDED BY Dafocus - START
	//// The method has been added with the wizard
	AccessNew (m_MessageView, this);
	//// ADDED BY Dafocus - END	
}
