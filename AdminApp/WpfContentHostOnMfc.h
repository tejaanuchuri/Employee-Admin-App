#pragma once

#include <vcclr.h>
#include <string.h>

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Documents;
using namespace System::Threading;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Windows::Media::Animation;
using namespace System::Runtime;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Interop;

//RECT rect;
HWND GetHwnd(HWND parent, int x, int y, int width, int height);


// WpfContentHostOnMfc dialog

class WpfContentHostOnMfc : public CDialogEx
{
	DECLARE_DYNAMIC(WpfContentHostOnMfc)

public:
	WpfContentHostOnMfc(CWnd* pParent = nullptr);   // standard constructor
	virtual ~WpfContentHostOnMfc();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATAGRIDCONTOLONMFC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};
