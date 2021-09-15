#pragma once


// HOSTWPFONMFC dialog

class HOSTWPFONMFC : public CDialogEx
{
	DECLARE_DYNAMIC(HOSTWPFONMFC)

public:
	HOSTWPFONMFC(CWnd* pParent = nullptr);   // standard constructor
	virtual ~HOSTWPFONMFC();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WPFHOSTONMFC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
