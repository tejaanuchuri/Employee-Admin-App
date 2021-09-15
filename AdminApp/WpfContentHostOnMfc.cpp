// WpfContentHostOnMfc.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "WpfContentHostOnMfc.h"
#include "afxdialogex.h"
ref class Globals
{
public:
	static System::Windows::Interop::HwndSource^ gHwndSource;

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

	Globals::gwcDataGrid->LoadEmployeeRecordsOnGrid();
	FrameworkElement^ myPage = Globals::gwcDataGrid;

	Globals::gHwndSource->RootVisual = myPage;
	return (HWND)Globals::gHwndSource->Handle.ToPointer();
}
// WpfContentHostOnMfc dialog

IMPLEMENT_DYNAMIC(WpfContentHostOnMfc, CDialogEx)

WpfContentHostOnMfc::WpfContentHostOnMfc(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DATAGRIDCONTOLONMFC, pParent)
{

}

WpfContentHostOnMfc::~WpfContentHostOnMfc()
{
}

void WpfContentHostOnMfc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WpfContentHostOnMfc, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// WpfContentHostOnMfc message handlers



int WpfContentHostOnMfc::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	hwndWPF = GetHwnd(this->GetSafeHwnd(), 0, 0, 900, 900);

	return 0;
}