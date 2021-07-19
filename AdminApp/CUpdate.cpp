// CUpdate.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "CUpdate.h"
#include "afxdialogex.h"


#include "odbcinst.h"
#include "afxdb.h"
#include "AdminAppDlg.h"
// CUpdate dialog

IMPLEMENT_DYNAMIC(CUpdate, CDialogEx)

CUpdate::CUpdate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGUPDATEDLG, pParent)
	, u_empid(_T(""))
	, u_choosefield(_T(""))
	, u_updatevalue(_T(""))
	, u_date_value(COleDateTime::GetCurrentTime())
{

}

CUpdate::~CUpdate()
{
}

void CUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, u_empid);
	DDX_CBString(pDX, IDC_COMBO_CHOOSE_FILED, u_choosefield);
	DDX_Text(pDX, IDC_EDIT_UPDATE_VALUE, u_updatevalue);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR_UPDATE_DATE, u_date_value);
	DDX_Control(pDX, IDC_EDIT_ID, CSEnterEmpNumber);
	DDX_Control(pDX, IDC_COMBO_CHOOSE_FILED, CChooseField);
	DDX_Control(pDX, IDC_EDIT_UPDATE_VALUE, CUpdateField);
}


BEGIN_MESSAGE_MAP(CUpdate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CUpdate::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CUpdate::OnBnClickedButtonCheck)
END_MESSAGE_MAP()


// CUpdate message handlers


BOOL CUpdate::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_EDIT_UPDATE_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_MONTHCALENDAR_UPDATE_DATE)->ShowWindow(SW_HIDE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CUpdate::OnBnClickedButtonUpdate()
{

	UpdateData(TRUE); // flow direction database <- ui

	CString EmpID = u_empid;
	CString ChooseField = u_choosefield;
	CString EnterValue = u_updatevalue;
	COleDateTime DT(u_date_value);
	CString date_value;
	date_value.Append(DT.Format(_T("%Y-%m-%d")));

	CDatabase database;
	CString sDsn;
	CString SqlString;
	// Build ODBC connection string
	sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		database.Open(NULL,false,false,sDsn);
	SqlString = L"UPDATE EmployeeTable SET ";
	SqlString.Append(ChooseField);
	SqlString.Append(_T(" = "));
	if (ChooseField == L"Hiredate" || ChooseField == L"BirthDate") {
		SqlString.Append(_T("'" + date_value + "'"));
	}
	else {

		SqlString.Append(_T("'" + EnterValue + "'"));
	}
	SqlString.Append(_T(" WHERE EmpId =" + EmpID));

	//AfxMessageBox(SqlString);
	database.ExecuteSQL(SqlString);

	MessageBox(L"Record Update sucessfully...!");
	// Close the database
	database.Close();
	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;
	CChooseField.SetWindowText(_T(""));
	CUpdateField.SetWindowText(_T(""));
	CSEnterEmpNumber.SetWindowText(_T(""));

CUpdate:OnOK();

}


void CUpdate::OnBnClickedButtonCheck()
{
	UpdateData(TRUE);
	if (u_choosefield == "BirthDate" || u_choosefield == "Hiredate") {
		GetDlgItem(IDC_EDIT_UPDATE_VALUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MONTHCALENDAR_UPDATE_DATE)->ShowWindow(SW_SHOW);
	}
	else if (u_choosefield == "Address" || u_choosefield == "Title" || u_choosefield == "Age" || u_choosefield == "FirstName" || u_choosefield == "LastName" || u_choosefield == "Gender" || u_choosefield == "MobilePhone" || u_choosefield == "EMail" || u_choosefield == "JobTitle" || u_choosefield == "Salary") {
		GetDlgItem(IDC_EDIT_UPDATE_VALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MONTHCALENDAR_UPDATE_DATE)->ShowWindow(SW_HIDE);
	}
	else {

		AfxMessageBox(L"Choose Valid Option...!");
	}
	UpdateWindow();
}
