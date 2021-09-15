// MFCHostWPFDlg.h : header file
//

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
// CMFCHostWPFDlg dialog
class CMFCHostWPFDlg : public CDialog
{
	// Construction
public:
	CMFCHostWPFDlg(CWnd* pParent = NULL);	// standard constructor
	// Dialog Data
	enum { IDD = IDD_MFCHOSTWPF_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
