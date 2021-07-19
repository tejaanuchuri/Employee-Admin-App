
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
#include "CUpdate.h"
#include "CSearch.h"
#include "CDelete.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdminAppDlg dialog



CAdminAppDlg::CAdminAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINAPP_DIALOG, pParent)
	, v_insert(1)
	, v_update(2)
	, v_search(3)
	, v_delete(4)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdminAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMP, emp_list);
	DDX_Control(pDX, IDC_RADIO_INSERT, c_insert);
	DDX_Radio(pDX, IDC_RADIO_INSERT, v_insert);
	DDX_Control(pDX, IDC_RADIO_UPDATE, c_update);
	DDX_Radio(pDX, IDC_RADIO_UPDATE, v_update);
	DDX_Control(pDX, IDC_RADIO_SEARCH, c_search);
	DDX_Radio(pDX, IDC_RADIO_SEARCH, v_update);
	DDX_Control(pDX, IDC_RADIO_DELETE, c_delete);
	DDX_Radio(pDX, IDC_RADIO_DELETE, v_delete);
}

BEGIN_MESSAGE_MAP(CAdminAppDlg, CDialogEx)
	//ON_WM_PAINT()
	//ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_INSERT, &CAdminAppDlg::OnBnClickedRadioInsert)
	ON_BN_CLICKED(IDC_RADIO_UPDATE, &CAdminAppDlg::OnBnClickedRadioUpdate)
	ON_BN_CLICKED(IDC_RADIO_SEARCH, &CAdminAppDlg::OnBnClickedRadioSearch)
	ON_BN_CLICKED(IDC_RADIO_DELETE, &CAdminAppDlg::OnBnClickedRadioDelete)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CAdminAppDlg::OnBnClickedButtonSubmit)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CAdminAppDlg::OnBnClickedButtonInsert)
END_MESSAGE_MAP()


// CAdminAppDlg message handlers

BOOL CAdminAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	emp_data_load();

	c_insert.SetCheck(0);
	c_delete.SetCheck(0);
	c_update.SetCheck(0);
	c_search.SetCheck(0);
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
	ListView_SetExtendedListViewStyle(emp_list, LVS_EX_GRIDLINES);
	emp_list.InsertColumn(
		0,              // Rank/order of item
		L"EmpID",          // Caption for this header
		LVCFMT_LEFT,    // Relative position of items under header
		70);           // Width of items under header

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
void CAdminAppDlg::OnBnClickedRadioInsert()
{
	c_insert.SetCheck(1);
	c_update.SetCheck(0);
	c_search.SetCheck(0);
	c_delete.SetCheck(0);
}


void CAdminAppDlg::OnBnClickedRadioUpdate()
{
	c_insert.SetCheck(0);
	c_update.SetCheck(2);
	c_search.SetCheck(0);
	c_delete.SetCheck(0);
}


void CAdminAppDlg::OnBnClickedRadioSearch()
{
	c_insert.SetCheck(0);
	c_update.SetCheck(0);
	c_search.SetCheck(3);
	c_delete.SetCheck(0);
}


void CAdminAppDlg::OnBnClickedRadioDelete()
{
	c_insert.SetCheck(0);
	c_update.SetCheck(0);
	c_search.SetCheck(0);
	c_delete.SetCheck(4);
}


void CAdminAppDlg::OnBnClickedButtonSubmit()
{
	if (c_insert.GetCheck()) {
		CInsert dlg;
		if (dlg.DoModal() == IDOK) {
			emp_data_load();
			UpdateWindow();
		}
	}
	else if (c_update.GetCheck()) {
		CUpdate dlg;
		if (dlg.DoModal() == IDOK) {
			emp_data_load();
			UpdateWindow();
		}
	}
	else if (c_search.GetCheck()) {
		CSearch dlg;
		dlg.DoModal();
	}
	else if (c_delete.GetCheck()) {
		CDelete dlg;
		if (dlg.DoModal() == IDOK) {
			emp_data_load();
			UpdateWindow();
		}
	}
	else {
		AfxMessageBox(L"Select Apporiate Radio Button...!");
	}
}


void CAdminAppDlg::OnBnClickedButtonInsert()
{

}
