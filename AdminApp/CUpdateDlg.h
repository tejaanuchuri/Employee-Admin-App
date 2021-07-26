#pragma once


// CUpdateDlg dialog

class CUpdateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateDlg)

public:
	CUpdateDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUpdateDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_DIALOGUE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString u_id;
	CString u_title;
	CString u_age;
	CString u_firstname;
	CString u_lastname;
	CString u_gender;
	CString u_email;
	CString u_phonenumber;
	CString u_address;
	CString u_jobtitle;
	CString u_salary;
	COleDateTime u_dateofbirthdate;
	COleDateTime u_hiredate;
	afx_msg void OnBnClickedButtonUpdateButton();
	CString u_empid;
};
