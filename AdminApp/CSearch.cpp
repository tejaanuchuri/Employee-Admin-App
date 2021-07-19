// CSearch.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "CSearch.h"
#include "afxdialogex.h"

#include "odbcinst.h"
#include "afxdb.h"
// CSearch dialog

IMPLEMENT_DYNAMIC(CSearch, CDialogEx)

CSearch::CSearch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEARCH, pParent)
	, s_choose_field(_T(""))
	, s_entervalue(_T(""))
{

}

CSearch::~CSearch()
{
}

void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_SEARCH_FIELD, s_choose_field);
	DDX_Text(pDX, IDC_EDIT_SEARCH_VALUE, s_entervalue);
	DDX_Control(pDX, IDC_LIST_SEARCH_LIST, m_Search_list);
}


BEGIN_MESSAGE_MAP(CSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CSearch::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CSearch message handlers



void CSearch::OnBnClickedButtonSearch()
{
	UpdateData(TRUE); // flow direction database <- ui
	//if (dlg.DoModal() == IDD_DIALOG_INSERT) {
	CString ChooseField = s_choose_field;
	CString EnterValue = s_entervalue;

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
	//sDsn.Format(_T("Driver={ODBC Driver 17 for SQL Server};Server=FYYP1N2;Dbq=C:\\Program Files\\Microsoft SQL Server\\MSSQL15.MSSQLSERVER\\MSSQL\\DATA\\AdminApp.mdf;Trusted_Connection=yes"));

	sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,sDsn);
	SqlString = L"SELECT * FROM EmployeeTable WHERE ";
	SqlString.Append(ChooseField);
	SqlString.Append(_T(" = "));
	if (ChooseField == L"EmpID") {
		SqlString.Append(EnterValue);
	}
	else {
		SqlString.Append(_T("'" + EnterValue + "'"));
	}
	//AfxMessageBox(SqlString);
	//database.ExecuteSQL(SqlString);

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	ResetListControl();
	ListView_SetExtendedListViewStyle(m_Search_list, LVS_EX_GRIDLINES);
	m_Search_list.InsertColumn(
		0,              // Rank/order of item
		L"EmpID",          // Caption for this header
		LVCFMT_LEFT,    // Relative position of items under header
		100);           // Width of items under header

	m_Search_list.InsertColumn(1, L"Title", LVCFMT_CENTER, 80);
	m_Search_list.InsertColumn(2, L"Age", LVCFMT_LEFT, 100);
	m_Search_list.InsertColumn(3, L"FirstName", LVCFMT_CENTER, 80);
	m_Search_list.InsertColumn(4, L"LastName", LVCFMT_LEFT, 100);
	m_Search_list.InsertColumn(5, L"Gender", LVCFMT_CENTER, 80);
	m_Search_list.InsertColumn(6, L"MobilePhone", LVCFMT_LEFT, 100);
	m_Search_list.InsertColumn(7, L"EMail", LVCFMT_CENTER, 80);
	m_Search_list.InsertColumn(8, L"BirthDate", LVCFMT_LEFT, 100);
	m_Search_list.InsertColumn(9, L"Address", LVCFMT_CENTER, 80);
	m_Search_list.InsertColumn(10, L"JobTitle", LVCFMT_LEFT, 100);
	m_Search_list.InsertColumn(11, L"Salary", LVCFMT_CENTER, 80);
	m_Search_list.InsertColumn(12, L"HireDate", LVCFMT_LEFT, 100);
	int count = 0;
	while (!recset.IsEOF()) {
		count++;
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
		iRec = m_Search_list.InsertItem(0, e_id, 0);
		m_Search_list.SetItemText(0, 1, e_title);
		m_Search_list.SetItemText(0, 2, e_age);
		m_Search_list.SetItemText(0, 3, e_firstname);
		m_Search_list.SetItemText(0, 4, e_lastname);
		m_Search_list.SetItemText(0, 5, e_gender);
		m_Search_list.SetItemText(0, 6, e_phonenumber);
		m_Search_list.SetItemText(0, 7, e_email);
		m_Search_list.SetItemText(0, 8, e_birthdate);
		m_Search_list.SetItemText(0, 9, e_address);
		m_Search_list.SetItemText(0, 10, e_jobtitle);
		m_Search_list.SetItemText(0, 11, e_salary);
		m_Search_list.SetItemText(0, 12, e_hiredate);

		// goto next record
		recset.MoveNext();
	}
	if (count == 0) {
		AfxMessageBox(L"Record Not Found...!");
	}
	// Close the database
	database.Close();
	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;
	//s_choose_field.SetWindowText(_T(""));
	//s_entervalue.SetWindowText(_T(""));
	UpdateWindow();
}
void CSearch::ResetListControl() {
	m_Search_list.DeleteAllItems();
	int iNbrOfColumns = 0, i;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_Search_list.GetDlgItem(0);
	if (pHeader) {
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (i = iNbrOfColumns; i >= 0; i--) {
		m_Search_list.DeleteColumn(i);
	}
}