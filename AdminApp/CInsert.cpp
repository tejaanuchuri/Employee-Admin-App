// CInsert.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "CInsert.h"
#include "afxdialogex.h"


#include "odbcinst.h"
#include "afxdb.h"
#include "AdminAppDlg.h"

IMPLEMENT_DYNAMIC(CInsert, CDialogEx)

CInsert::CInsert(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INSERTDLG, pParent)
	, emp_title(_T(""))
	, emp_age(_T(""))
	, emp_firstname(_T(""))
	, emp_lastname(_T(""))
	, emp_gender(_T(""))
	, emp_email(_T(""))
	, emp_phonenumber(_T(""))
	, emp_address(_T(""))
	, emp_jobtitle(_T(""))
	, emp_salary(_T(""))
	, emp_datebirth(COleDateTime::GetCurrentTime())
	, employee_hiredate(COleDateTime::GetCurrentTime())
	, e_yrsofexp(_T(""))
{

}

CInsert::~CInsert()
{
}

void CInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_TITLE, emp_title);
	DDX_Text(pDX, IDC_EDIT_AGE, emp_age);
	DDX_Text(pDX, IDC_EDIT_FIRSTNAME, emp_firstname);
	DDX_Text(pDX, IDC_EDIT_LASTNAME, emp_lastname);
	DDX_CBString(pDX, IDC_COMBO_GENDER, emp_gender);
	DDX_Text(pDX, IDC_EDIT_EMAIL, emp_email);
	DDX_Text(pDX, IDC_EDIT_PHONE_NUMBER, emp_phonenumber);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, emp_address);
	DDX_CBString(pDX, IDC_COMBO_JOBTITLE, emp_jobtitle);
	DDX_Text(pDX, IDC_EDIT_SALARY, emp_salary);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR_DATEOFBIRTH, emp_datebirth);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR_HIREDATE, employee_hiredate);
	DDX_Control(pDX, IDC_COMBO_TITLE, cemp_title);
	DDX_Control(pDX, IDC_EDIT_AGE, CAge);
	DDX_Control(pDX, IDC_EDIT_FIRSTNAME, CFirstName);
	DDX_Control(pDX, IDC_EDIT_LASTNAME, CLastName);
	DDX_Control(pDX, IDC_COMBO_GENDER, CGender);
	DDX_Control(pDX, IDC_EDIT_EMAIL, CEmail);
	DDX_Control(pDX, IDC_EDIT_PHONE_NUMBER, CPhoneNumber);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, CAddress);
	DDX_Control(pDX, IDC_COMBO_JOBTITLE, CJobTitle);
	DDX_Control(pDX, IDC_EDIT_SALARY, CSalary);
	DDX_Text(pDX, IDC_EDIT_YEARSOFEXP, e_yrsofexp);
	DDX_Control(pDX, IDC_EDIT_YEARSOFEXP, CYrsOfExp);
}


BEGIN_MESSAGE_MAP(CInsert, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CInsert::OnBnClickedButtonInsert)
END_MESSAGE_MAP()


// CInsert message handlers


void CInsert::OnBnClickedButtonInsert()
{
	UpdateData(TRUE); // flow direction database <- ui


	CDatabase database;
	CString sDsn;
	CString SqlString;
	COleDateTime date;
	date = COleDateTime::GetCurrentTime();
	CString cur_date = date.Format(_T("%d/%m/%Y"));
	CString hiredate = employee_hiredate.Format(_T("%d/%m/%Y"));
	COleDateTimeSpan diff = (cur_date - hiredate);
	int yrs = diff.GetTotalDays() / 365.0;
	CString yrsofexps = _T("%d", yrs);
	if (emp_title.IsEmpty()) {
		AfxMessageBox(L"Title Must Be Required ...!");
	}
	else if (emp_age.IsEmpty()) {
		AfxMessageBox(L"Age Must Be Required ...!");
	}
	else if (emp_firstname.IsEmpty()) {
		AfxMessageBox(L"First Name Must Be Required ...!");
	}
	else if (emp_lastname.IsEmpty()) {
		AfxMessageBox(L"Last Name Must Be Required ...!");
	}
	else if (emp_gender.IsEmpty()) {
		AfxMessageBox(L"Gender Must Be Required ...!");
	}
	else if (emp_email.IsEmpty()) {
		AfxMessageBox(L" Email Must Be Required ...!");
	}
	else if (emp_phonenumber.IsEmpty()) {
		AfxMessageBox(L"Phone Number Must Be Required ...!");
	}
	else if (emp_address.IsEmpty()) {
		AfxMessageBox(L"Address Must Be Required ...!");
	}
	else if (emp_jobtitle.IsEmpty()) {
		AfxMessageBox(L"Job Title Must Be Required ...!");
	}
	else if (emp_salary.IsEmpty()) {
		AfxMessageBox(L"Salary Must Be Required ...!");
	}
	else if (e_yrsofexp.IsEmpty()) {
		AfxMessageBox(L"Years Of Experience Must Be Required ...!");
	}
	else {
		// Build ODBC connection string
		sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
		TRY{
			// Open the database
			database.Open(NULL,false,false,sDsn);
		//MessageBoxW(L"Are You Sure ?", L"Insert a Record",MB_YESNO);

		CString out = L" ,";
		CString quo = L"'";
		SqlString.Append(_T("INSERT INTO EmployeeTable(Title,Age,FirstName,LastName,Gender,MobilePhone,EMail,BirthDate,Address,JobTitle,Salary,Hiredate,YearsOfExp) VALUES ("));
		SqlString.Append(quo);
		SqlString.Append(emp_title);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_age);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_firstname);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_lastname);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_gender);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_phonenumber);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_email);
		SqlString.Append(quo);
		SqlString.Append(out);

		COleDateTime dt(emp_datebirth);
		SqlString.Append(quo);
		SqlString.Append(dt.Format(_T("%Y-%m-%d")));
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_address);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_jobtitle);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_salary);
		SqlString.Append(quo);
		SqlString.Append(out);

		COleDateTime DT(employee_hiredate);
		SqlString.Append(quo);
		SqlString.Append(DT.Format(_T("%Y-%m-%d")));
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(yrsofexps);
		SqlString.Append(quo);

		SqlString.Append(_T(" )"));

		//AfxMessageBox(SqlString);
		database.ExecuteSQL(SqlString);
		MessageBox(L"Insert Record sucessfully...!");
		// Close the database
		database.Close();
		}CATCH(CDBException, e) {
			// If a database exception occured, show error msg
			AfxMessageBox(L"Database error: " + e->m_strError);
		}
		END_CATCH;

		cemp_title.SetWindowText(_T(""));
		CAge.SetWindowText(_T(""));
		CFirstName.SetWindowText(_T(""));
		CLastName.SetWindowText(_T(""));
		CPhoneNumber.SetWindowText(_T(""));
		CEmail.SetWindowText(_T(""));
		CAddress.SetWindowText(_T(""));
		CJobTitle.SetWindowText(_T(""));
		CSalary.SetWindowText(_T(""));
		CGender.SetWindowText(_T(""));

		UpdateData(FALSE);
		CInsert::OnOK();
	}
}


BOOL CInsert::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	cemp_title.SetWindowText(_T(""));
	CAge.SetWindowText(_T(""));
	CFirstName.SetWindowText(_T(""));
	CLastName.SetWindowText(_T(""));
	CPhoneNumber.SetWindowText(_T(""));
	CEmail.SetWindowText(_T(""));
	CAddress.SetWindowText(_T(""));
	CJobTitle.SetWindowText(_T(""));
	CSalary.SetWindowText(_T(""));
	CGender.SetWindowText(_T(""));
	CYrsOfExp.SetWindowText(_T(""));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
