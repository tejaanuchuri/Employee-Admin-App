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
	, i_empid(_T(""))
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
	DDX_Text(pDX, IDC_EDIT_EMP_ID, i_empid);
}


BEGIN_MESSAGE_MAP(CInsert, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CInsert::OnBnClickedButtonInsert)
END_MESSAGE_MAP()


// CInsert message handlers


void CInsert::OnBnClickedButtonInsert()
{
	UpdateData(TRUE); // flow direction database <- ui

	CString id;
	CDatabase database;
	CString sDsn;
	CString SqlString;
	COleDateTime date;
	date = COleDateTime::GetCurrentTime();
	int cur_year = _wtoi(date.Format(_T("%Y")));
	int hireyear = _wtoi(employee_hiredate.Format(_T("%Y")));
	int cur_month = _wtoi(date.Format(_T("%m")));
	int hire_month = _wtoi(employee_hiredate.Format(_T("%m")));
	int cur_date = _wtoi(date.Format(_T("%d")));
	int hire_date = _wtoi(employee_hiredate.Format(_T("%d")));
	int b_date = _wtoi(emp_datebirth.Format(_T("%d")));
	int b_month = _wtoi(emp_datebirth.Format(_T("%m")));
	int b_year = _wtoi(emp_datebirth.Format(_T("%Y")));
	DT dt1 = { hire_date, hire_month, hireyear };
	DT dt2 = { cur_date, cur_month, cur_year };
	DT dt3 = { b_date, b_month, b_year };


	CString age_;

	int remove_leap_year = 0;
	for (int i = b_year; i <= cur_year; i++) {
		if (i % 400 == 0) {
			remove_leap_year++;
		}
		else if (i % 100 != 0) {

		}
		else if (i % 4 == 0) {
			remove_leap_year++;
		}
	}
	age_.Format(_T("%d"), ((getDifference(dt3, dt2) - remove_leap_year) / 365));
	//AfxMessageBox(age_);
	CString yrsofexps;
	remove_leap_year = 0;
	for (int i = hireyear; i <= cur_year; i++) {
		if (i % 400 == 0) {
			remove_leap_year++;
		}
		else if (i % 100 != 0) {

		}
		else if (i % 4 == 0) {
			remove_leap_year++;
		}
	}
	yrsofexps.Format(_T("%d"), ((getDifference(dt1, dt2) - remove_leap_year) / 365));



	/*COleDateTime date;
	date = COleDateTime::GetCurrentTime();
	CString cur_date = date.Format(_T("%d/%m/%Y"));
	CString hiredate = employee_hiredate.Format(_T("%d/%m/%Y"));
	COleDateTimeSpan diff = (cur_date - hiredate);
	float yrs = diff.GetTotalDays() / 365.0;
	CString yrsofexps = _T("%d", (int)yrs);
	*/
	if (emp_title.IsEmpty()) {
		AfxMessageBox(L"Title Must Be Required ...!");
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
	else {
		// Build ODBC connection string
		sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
		TRY{
			// Open the database
			database.Open(NULL,false,false,sDsn);
		//MessageBoxW(L"Are You Sure ?", L"Insert a Record",MB_YESNO);

		CString out = L" ,";
		CString quo = L"'";
		SqlString.Append(_T("INSERT INTO EmployeeTable(EmpID,Hiredate,YearsOfExp,Title,Age,FirstName,LastName,Gender,MobilePhone,EMail,BirthDate,Address,JobTitle,Salary) VALUES ("));
		SqlString.Append(quo);
		SqlString.Append(i_empid);
		SqlString.Append(quo);
		SqlString.Append(out);

		COleDateTime DT(employee_hiredate);
		SqlString.Append(quo);
		SqlString.Append(DT.Format(_T("%d-%m-%Y")));
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(yrsofexps);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(emp_title);
		SqlString.Append(quo);
		SqlString.Append(out);

		SqlString.Append(quo);
		SqlString.Append(age_);
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

		COleDateTime dt(emp_datebirth);
		SqlString.Append(quo);
		SqlString.Append(dt.Format(_T("%d-%m-%Y")));
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

int CInsert::countLeapYears(DT d)
{
	int years = d.y;

	// Check if the current year needs to be
	//  considered for the count of leap years
	// or not
	if (d.m <= 2)
		years--;

	// An year is a leap year if it
	// is a multiple of 4,
	// multiple of 400 and not a
	 // multiple of 100.
	return years / 4
		- years / 100
		+ years / 400;
	return 0;
}

int CInsert::getDifference(DT dt1, DT dt2)
{
	long int n1 = dt1.y * 365 + dt1.d;

	// Add days for months in given date
	for (int i = 0; i < dt1.m - 1; i++)
		n1 += monthdays[i];

	// Since every leap year is of 366 days,
	// Add a day for every leap year
	n1 += countLeapYears(dt1);

	// SIMILARLY, COUNT TOTAL NUMBER OF
	// DAYS BEFORE 'dt2'

	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += monthdays[i];
	n2 += countLeapYears(dt2);

	// return difference between two counts
	return (n2 - n1);
	return 0;
}
