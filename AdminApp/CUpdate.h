#pragma once


// CUpdate dialog

class CUpdate : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdate)

public:
	CUpdate(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUpdate();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGUPDATEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString u_empid;
	CString u_choosefield;
	CString u_updatevalue;
	COleDateTime u_date_value;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonUpdate();
	CEdit CSEnterEmpNumber;
	CComboBox CChooseField;
	CEdit CUpdateField;
	afx_msg void OnBnClickedButtonCheck();
};
