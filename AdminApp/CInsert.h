#pragma once


// CInsert dialog

class CInsert : public CDialogEx
{
	DECLARE_DYNAMIC(CInsert)

public:
	CInsert(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CInsert();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSERTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	CString emp_title;
	CString emp_age;
	CString emp_firstname;
	CString emp_lastname;
	CString emp_gender;
	CString emp_email;
	CString emp_phonenumber;
	CString emp_address;
	CString emp_jobtitle;
	CString emp_salary;
	COleDateTime emp_datebirth;
	COleDateTime employee_hiredate;
	afx_msg void OnBnClickedButtonInsert();
	CComboBox cemp_title;
	CEdit CAge;
	CEdit CFirstName;
	CEdit CLastName;
	CComboBox CGender;
	CEdit CEmail;
	CEdit CPhoneNumber;
	CEdit CAddress;
	CComboBox CJobTitle;
	CEdit CSalary;
	virtual BOOL OnInitDialog();
};
