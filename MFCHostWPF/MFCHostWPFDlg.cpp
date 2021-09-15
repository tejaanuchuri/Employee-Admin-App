// MFCHostWPFDlg.cpp : implementation file
//



#include "stdafx.h"
#include "MFCHostWPF.h"
#include "MFCHostWPFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////
//////////////////////WPF Implementation//////////////////////

ref class Globals
{
public:
	static System::Windows::Interop::HwndSource^ gHwndSource;
	static WPFControls::AnimClock^ gwcClock;
	static WpfControlLibrary::UserControl1^ gwcDataGrid;
};

HWND hwndWPF; //The hwnd associated with the hosted WPF page

HWND GetHwnd(HWND parent, int x, int y, int width, int height)
{
	System::Windows::Interop::HwndSourceParameters^ sourceParams = gcnew System::Windows::Interop::HwndSourceParameters("MFCWPFApp");
	sourceParams->PositionX = x;
	sourceParams->PositionY = y;
	sourceParams->Height = height;
	sourceParams->Width = width;
	sourceParams->ParentWindow = IntPtr(parent);
	sourceParams->WindowStyle = WS_VISIBLE | WS_CHILD;
	Globals::gHwndSource = gcnew System::Windows::Interop::HwndSource(*sourceParams);

	Globals::gwcDataGrid = gcnew WpfControlLibrary::UserControl1();

	//Globals::gwcClock = gcnew WPFControls::AnimClock();
	Globals::gwcDataGrid->LoadEmployeeRecordsOnGrid();
	FrameworkElement^ myPage = Globals::gwcDataGrid;

	Globals::gHwndSource->RootVisual = myPage;
	return (HWND)Globals::gHwndSource->Handle.ToPointer();
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMFCHostWPFDlg dialog




CMFCHostWPFDlg::CMFCHostWPFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCHostWPFDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCHostWPFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCHostWPFDlg, CDialog)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCHostWPFDlg message handlers

int CMFCHostWPFDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	hwndWPF = GetHwnd(this->GetSafeHwnd(), 10, 10, 1200, 1200);

	return 0;
}

BOOL CMFCHostWPFDlg::OnInitDialog()
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

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// TODO: Add extra initialization here
	//ShowWindow(SW_SHOWMAXIMIZED);
	//UpdateWindow();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCHostWPFDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCHostWPFDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

HCURSOR CMFCHostWPFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

