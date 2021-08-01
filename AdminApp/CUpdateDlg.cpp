// CUpdateDlg.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "CUpdateDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"

// CUpdateDlg dialog

IMPLEMENT_DYNAMIC(CUpdateDlg, CDialogEx)

CUpdateDlg::CUpdateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATE_DIALOGUE, pParent)
	, u_id(_T(""))
	, u_title(_T(""))
	, u_age(_T(""))
	, u_firstname(_T(""))
	, u_lastname(_T(""))
	, u_gender(_T(""))
	, u_email(_T(""))
	, u_phonenumber(_T(""))
	, u_address(_T(""))
	, u_jobtitle(_T(""))
	, u_salary(_T(""))
	, u_dateofbirthdate(COleDateTime::GetCurrentTime())
	, u_hiredate(COleDateTime::GetCurrentTime())
	, u_empid(_T(""))
	, u_yrsofexp(_T(""))
{

}

CUpdateDlg::~CUpdateDlg()
{
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_UTITLE, u_title);
	DDX_Text(pDX, IDC_EDIT_UAGE, u_age);
	DDX_Text(pDX, IDC_EDIT_UFIRSTNAME, u_firstname);
	DDX_Text(pDX, IDC_EDIT_ULASTNAME, u_lastname);
	DDX_CBString(pDX, IDC_COMBO_UGENDER, u_gender);
	DDX_Text(pDX, IDC_EDIT_UEMAIL, u_email);
	DDX_Text(pDX, IDC_EDIT_UPHONE_NUMBER, u_phonenumber);
	DDX_Text(pDX, IDC_EDIT_UADDRESS, u_address);
	DDX_CBString(pDX, IDC_COMBO_UJOBTITLE, u_jobtitle);
	DDX_Text(pDX, IDC_EDIT_USALARY, u_salary);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR_UDATEOFBIRTH, u_dateofbirthdate);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR_UHIREDATE, u_hiredate);
	DDX_Text(pDX, IDC_EDIT_EMP_ID_VALUE, u_empid);
	DDX_Text(pDX, IDC_EDIT_UYEARSOFEXPERIENCE, u_yrsofexp);
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_BUTTON, &CUpdateDlg::OnBnClickedButtonUpdateButton)
END_MESSAGE_MAP()


// CUpdateDlg message handlers


void CUpdateDlg::OnBnClickedButtonUpdateButton()
{
	UpdateData(TRUE); // flow direction database <- ui
	//if (dlg.DoModal() == IDD_DIALOG_INSERT) {

	CDatabase database;
	CString sDsn;
	CString SqlString;


	COleDateTime date;
	date = COleDateTime::GetCurrentTime();
	int cur_year = _wtoi(date.Format(_T("%Y")));
	int hireyear = _wtoi(u_hiredate.Format(_T("%Y")));
	int cur_month = _wtoi(date.Format(_T("%m")));
	int hire_month = _wtoi(u_hiredate.Format(_T("%m")));
	int cur_date = _wtoi(u_hiredate.Format(_T("%d")));
	int hire_date = _wtoi(u_hiredate.Format(_T("%d")));
	int b_date = _wtoi(u_dateofbirthdate.Format(_T("%d")));
	int b_month = _wtoi(u_dateofbirthdate.Format(_T("%m")));
	int b_year = _wtoi(u_dateofbirthdate.Format(_T("%Y")));
	Date dt1 = { hire_date, hire_month, hireyear };
	Date dt2 = { cur_date, cur_month, cur_year };
	Date dt3 = { b_date, b_month, b_year };

	//AfxMessageBox(cur_year);
	//AfxMessageBox(hireyear);
	//COleDateTimeSpan diff = (date.Format(_T("%Y-%m-%d")) - u_hiredate.Format(_T("%Y-%m-%d")));
	//double d = diff.GetDays();
	//int y = d / 365;
	//int yrs = cur_year - hireyear;
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


	if (u_title.IsEmpty()) {
		AfxMessageBox(L"Title Must Be Required ...!");
	}
	else if (u_age.IsEmpty()) {
		AfxMessageBox(L"Age Must Be Required ...!");
	}
	else if (u_firstname.IsEmpty()) {
		AfxMessageBox(L"First Name Must Be Required ...!");
	}
	else if (u_lastname.IsEmpty()) {
		AfxMessageBox(L"Last Name Must Be Required ...!");
	}
	else if (u_gender.IsEmpty()) {
		AfxMessageBox(L"Gender Must Be Required ...!");
	}
	else if (u_email.IsEmpty()) {
		AfxMessageBox(L" Email Must Be Required ...!");
	}
	else if (u_phonenumber.IsEmpty()) {
		AfxMessageBox(L"Phone Number Must Be Required ...!");
	}
	else if (u_address.IsEmpty()) {
		AfxMessageBox(L"Address Must Be Required ...!");
	}
	else if (u_jobtitle.IsEmpty()) {
		AfxMessageBox(L"Job Title Must Be Required ...!");
	}
	else if (u_salary.IsEmpty()) {
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
		SqlString.Append(_T("UPDATE EmployeeTable SET "));

		SqlString.Append(L"Title = ");
		SqlString.Append(quo);
		SqlString.Append(u_title);
		SqlString.Append(quo);
		SqlString.Append(out);

	SqlString.Append(L"Age = ");
	SqlString.Append(quo);
	SqlString.Append(age_);
	SqlString.Append(quo);
	SqlString.Append(out);

	SqlString.Append(L"FirstName = ");
	SqlString.Append(quo);
	SqlString.Append(u_firstname);
	SqlString.Append(quo);
	SqlString.Append(out);

	SqlString.Append(L"LastName = ");
	SqlString.Append(quo);
	SqlString.Append(u_lastname);
	SqlString.Append(quo);
	SqlString.Append(out);


	SqlString.Append(L"Gender = ");
	SqlString.Append(quo);
	SqlString.Append(u_gender);
	SqlString.Append(quo);
	SqlString.Append(out);


	SqlString.Append(L"MobilePhone = ");
	SqlString.Append(quo);
	SqlString.Append(u_phonenumber);
	SqlString.Append(quo);
	SqlString.Append(out);

	SqlString.Append(L"EMail = ");
	SqlString.Append(quo);
	SqlString.Append(u_email);
	SqlString.Append(quo);
	SqlString.Append(out);


	SqlString.Append(L"BirthDate = ");
	COleDateTime dt(u_dateofbirthdate);
	SqlString.Append(quo);
	SqlString.Append(dt.Format(_T("%Y-%m-%d")));
	SqlString.Append(quo);
	SqlString.Append(out);

	SqlString.Append(L"Address = ");
	SqlString.Append(quo);
	SqlString.Append(u_address);
	SqlString.Append(quo);
	SqlString.Append(out);

	SqlString.Append(L"JobTitle = ");
	SqlString.Append(quo);
	SqlString.Append(u_jobtitle);
	SqlString.Append(quo);
	SqlString.Append(out);

	SqlString.Append(L"Salary = ");
	SqlString.Append(quo);
	SqlString.Append(u_salary);
	SqlString.Append(quo);
	SqlString.Append(out);


	SqlString.Append(L"Hiredate = ");
	COleDateTime DT(u_hiredate);
	SqlString.Append(quo);
	SqlString.Append(DT.Format(_T("%Y-%m-%d")));
	SqlString.Append(quo);
	SqlString.Append(out);

	SqlString.Append(L"YearsOfExp = ");
	SqlString.Append(quo);
	SqlString.Append(yrsofexps);
	SqlString.Append(quo);

	SqlString.Append(_T(" WHERE EmpID = " + u_id));

	//MessageBox(SqlString);
	database.ExecuteSQL(SqlString);
	// Close the database
	database.Close();
		}CATCH(CDBException, e) {
			// If a database exception occured, show error msg
			AfxMessageBox(L"Database error: " + e->m_strError);
		}
		END_CATCH;
	}
	CUpdateDlg::OnOK();
}

int CUpdateDlg::countLeapYears(Date d)
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

int CUpdateDlg::getDifference(Date dt1, Date dt2)
{
	long int n1 = dt1.y * 365 + dt1.d;

	// Add days for months in given date
	for (int i = 0; i < dt1.m - 1; i++)
		n1 += monthDays[i];

	// Since every leap year is of 366 days,
	// Add a day for every leap year
	n1 += countLeapYears(dt1);

	// SIMILARLY, COUNT TOTAL NUMBER OF
	// DAYS BEFORE 'dt2'

	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);

	// return difference between two counts
	return (n2 - n1);
	return 0;
}