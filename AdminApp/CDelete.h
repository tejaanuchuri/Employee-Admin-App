#pragma once


// CDelete dialog

class CDelete : public CDialogEx
{
	DECLARE_DYNAMIC(CDelete)

public:
	CDelete(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDelete();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString DEmployeeNumber;
	afx_msg void OnBnClickedButtonDelete();
	CEdit CEmpNumber;
};
