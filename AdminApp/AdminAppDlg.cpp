
// AdminAppDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "AdminApp.h"
#include "AdminAppDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "CInsert.h"
#include "CSearch.h"
#include "CDelete.h"
#include"CUpdateDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CAbout.h"
#include <vector>
#include <stdlib.h>


// CAdminAppDlg dialog



CAdminAppDlg::CAdminAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINAPP_DIALOG, pParent)
	, row(-1)
	, m_iYScale(0)
{
	m_iYScale = 1;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdminAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMP, emp_list);
	DDX_Control(pDX, IDC_STATIC_GRAPH_CHART, m_Graph);
}

BEGIN_MESSAGE_MAP(CAdminAppDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CAdminAppDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CAdminAppDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CAdminAppDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CAdminAppDlg::OnBnClickedButtonDelete)
	ON_COMMAND(ID_FILE_CLOSE32771, &CAdminAppDlg::OnFileClose)
	ON_COMMAND(ID_ABOUT_ADMINAPP, &CAdminAppDlg::OnAboutAdminapp)
END_MESSAGE_MAP()


// CAdminAppDlg message handlers

BOOL CAdminAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CMenu m_Menu;
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);
	emp_data_load();

	UpdateData(FALSE); // flow direction database -> ui

	CString e_id;
	CString e_age;

	CDatabase database;
	CString sDsn;
	CString SqlString;
	int n = 0;
	CString s_id[100];
	CString s_Age[100];
	// Build ODBC connection string

	sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,sDsn);
	SqlString = L"SELECT EmpID,Age FROM EmployeeTable";

	//AfxMessageBox(SqlString);

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	while (!recset.IsEOF()) {

		// Copy each column into a variable
		recset.GetFieldValue(L"EmpID", e_id);
		recset.GetFieldValue(L"Age", e_age);
		s_id[n].Insert(n, e_id);
		s_Age[n].Insert(n, e_age);
			n++;
			recset.MoveNext();
	}
	database.Close();
	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;


	m_Graph.SetUnit(L"Age");
	m_Graph.SetScale(3);
	int x = 1, y = 50;
	m_Graph.GetDisplayRange(x, y);
	m_iYScale = 3;

	for (int i = 0; i < n; i++)
	{
		char tmp[20];
		int k = _wtoi(s_id[i]);
		sprintf_s(tmp, "EmpID - %d", k);
		k = _wtoi(s_Age[i]);
		m_Graph.AddBar(k, RGB(rand() % 256, rand() % 256, rand() % 256), tmp);

		//sprintf(tmp, "%d", i);
		//m_BarCombo.AddString(tmp);
	}
	m_Graph.SetBGColor(RGB(255, 229, 204));
	m_Graph.SetAxisColor(RGB(102, 0, 0));
	m_Graph.SetTextColor(RGB(102, 102, 255));

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CAdminAppDlg::emp_data_load() {
	UpdateData(FALSE); // flow direction database -> ui

	CString e_id;
	CString e_age;
	CString e_title;
	CString e_firstname;
	CString e_lastname;
	CString e_gender;
	CString e_phonenumber;
	CString e_email;
	CString e_birthdate;
	CString e_address;
	CString e_jobtitle;
	CString e_salary;
	CString e_hiredate;

	CDatabase database;
	CString sDsn;
	CString SqlString;
	int iRec = 0;
	// Build ODBC connection string

	sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,sDsn);
	SqlString = L"SELECT * FROM EmployeeTable";

	//AfxMessageBox(SqlString);

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	m_ResetListControl();
	ListView_SetExtendedListViewStyle(emp_list,LVS_EX_FULLROWSELECT);
	emp_list.InsertColumn(
		0,
		L"EmpID",
		LVCFMT_LEFT,
		70);

	emp_list.InsertColumn(1, L"Title", LVCFMT_CENTER, 90);
	emp_list.InsertColumn(2, L"Age", LVCFMT_LEFT, 70);
	emp_list.InsertColumn(3, L"FirstName", LVCFMT_CENTER, 130);
	emp_list.InsertColumn(4, L"LastName", LVCFMT_LEFT, 130);
	emp_list.InsertColumn(5, L"Gender", LVCFMT_CENTER, 120);
	emp_list.InsertColumn(6, L"MobilePhone", LVCFMT_LEFT, 160);
	emp_list.InsertColumn(7, L"EMail", LVCFMT_CENTER, 230);
	emp_list.InsertColumn(8, L"BirthDate", LVCFMT_LEFT, 100);
	emp_list.InsertColumn(9, L"Address", LVCFMT_CENTER, 180);
	emp_list.InsertColumn(10, L"JobTitle", LVCFMT_LEFT, 100);
	emp_list.InsertColumn(11, L"Salary", LVCFMT_CENTER, 100);
	emp_list.InsertColumn(12, L"HireDate", LVCFMT_LEFT, 100);

	while (!recset.IsEOF()) {
		// Copy each column into a variable
		recset.GetFieldValue(L"EmpID", e_id);
		recset.GetFieldValue(L"Title",e_title);
		recset.GetFieldValue(L"Age", e_age);
		recset.GetFieldValue(L"FirstName", e_firstname);
		recset.GetFieldValue(L"LastName", e_lastname);
		recset.GetFieldValue(L"Gender", e_gender);
		recset.GetFieldValue(L"MobilePhone", e_phonenumber);
		recset.GetFieldValue(L"EMail", e_email);
		recset.GetFieldValue(L"BirthDate", e_birthdate);
		recset.GetFieldValue(L"Address", e_address);
		recset.GetFieldValue(L"JobTitle", e_jobtitle);
		recset.GetFieldValue(L"Salary", e_salary);
		recset.GetFieldValue(L"Hiredate", e_hiredate);

		// Insert values into the list control
		iRec = emp_list.InsertItem(0, e_id, 0);
		emp_list.SetItemText(0, 1, e_title);
		emp_list.SetItemText(0, 2, e_age);
		emp_list.SetItemText(0, 3, e_firstname);
		emp_list.SetItemText(0, 4, e_lastname);
		emp_list.SetItemText(0, 5, e_gender);
		emp_list.SetItemText(0, 6, e_phonenumber);
		emp_list.SetItemText(0, 7, e_email);
		emp_list.SetItemText(0, 8, e_birthdate);
		emp_list.SetItemText(0, 9, e_address);
		emp_list.SetItemText(0, 10, e_jobtitle);
		emp_list.SetItemText(0, 11, e_salary);
		emp_list.SetItemText(0, 12, e_hiredate);

		// goto next record
		recset.MoveNext();
	}
	database.Close();
	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;
}

void CAdminAppDlg::m_ResetListControl() {
	emp_list.DeleteAllItems();
	int iNbrOfColumns = 0, i;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)emp_list.GetDlgItem(0);
	if (pHeader) {
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (i = iNbrOfColumns; i >= 0; i--) {
		emp_list.DeleteColumn(i);
	}
}

void CAdminAppDlg::OnBnClickedButtonInsert()
{
	CInsert dlg;
	if (dlg.DoModal() == IDOK) {
		emp_data_load();
		UpdateWindow();
	}
}


void CAdminAppDlg::OnBnClickedButtonUpdate()
{
	UpdateData(TRUE); // flow direction database <- ui

	row = emp_list.GetSelectionMark();
	if (row < 0) {
		AfxMessageBox(L"No row Selected");
	}
	else {

		CString id = emp_list.GetItemText(row, 0);
		CString emp_title = emp_list.GetItemText(row, 1);
		CString emp_age = emp_list.GetItemText(row, 2);
		CString emp_firstname = emp_list.GetItemText(row, 3);
		CString emp_lastname = emp_list.GetItemText(row, 4);
		CString emp_gender = emp_list.GetItemText(row, 5);
		CString emp_phonenumber = emp_list.GetItemText(row, 6);
		CString emp_email = emp_list.GetItemText(row, 7);
		CString emp_address = emp_list.GetItemText(row, 9);
		CString emp_jobtitle = emp_list.GetItemText(row, 10);
		CString emp_salary = emp_list.GetItemText(row, 11);
		COleDateTime emp_datebirth;
		emp_datebirth.ParseDateTime(emp_list.GetItemText(row, 8));
		COleDateTime employee_hiredate;
		employee_hiredate.ParseDateTime(emp_list.GetItemText(row, 12));

		CUpdateDlg u;
		u.u_id = id;
		u.u_empid = id;
		u.u_title = emp_title;
		u.u_age = emp_age;
		u.u_firstname = emp_firstname;
		u.u_lastname = emp_lastname;
		u.u_gender = emp_gender;
		u.u_phonenumber = emp_phonenumber;
		u.u_email = emp_email;
		u.u_address = emp_address;
		u.u_jobtitle = emp_jobtitle;
		u.u_salary = emp_salary;
		u.u_dateofbirthdate = emp_datebirth;
		u.u_hiredate = employee_hiredate;
		if (u.DoModal() == IDOK) {
			MessageBox(L"Update Record Sucessfully...!");
		}
		emp_data_load();
		UpdateWindow();
	}

}


void CAdminAppDlg::OnBnClickedButtonSearch()
{
	CSearch dlg;
	dlg.DoModal();
}


void CAdminAppDlg::OnBnClickedButtonDelete()
{
	UpdateData(TRUE); // flow direction database <- ui

	row = emp_list.GetSelectionMark();
	if (row < 0) {
		AfxMessageBox(L"No row Selected");
	}
	else {

		CString id = emp_list.GetItemText(row, 0);

		CDatabase database;
		CString sDsn;
		CString SqlString;

		// Build ODBC connection string
		sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
		TRY{
			// Open the database
			database.Open(NULL,false,false,sDsn);
			SqlString = L"DELETE FROM EmployeeTable WHERE EmpID = ";
			SqlString.Append(id);
			//AfxMessageBox(SqlString);
			database.ExecuteSQL(SqlString);


			MessageBox(L"Record Delete sucessfully...!");
			// Close the database
			database.Close();
		}CATCH(CDBException, e) {
			// If a database exception occured, show error msg
			AfxMessageBox(L"Database error: " + e->m_strError);
		}
		END_CATCH;

		emp_data_load();
		UpdateWindow();
	}

}

void CAdminAppDlg::OnFileClose()
{
	if (AfxMessageBox(_T("Are you sure you want to close ?"),
		MB_YESNO) == IDNO)
	{
		return;
	}


	CDialog::OnCancel();
}


void CAdminAppDlg::OnAboutAdminapp()
{
	CAbout about;
	if (about.DoModal() == IDOK) {

	}
}


