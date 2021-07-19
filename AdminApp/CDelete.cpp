// CDelete.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "CDelete.h"
#include "afxdialogex.h"


#include "odbcinst.h"
#include "afxdb.h"
#include "AdminAppDlg.h"
// CDelete dialog

IMPLEMENT_DYNAMIC(CDelete, CDialogEx)

CDelete::CDelete(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELETEDLG, pParent)
	, DEmployeeNumber(_T(""))
{

}

CDelete::~CDelete()
{
}

void CDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DELETE_EMPID, DEmployeeNumber);
	DDX_Control(pDX, IDC_EDIT_DELETE_EMPID, CEmpNumber);
}


BEGIN_MESSAGE_MAP(CDelete, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDelete::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CDelete message handlers


void CDelete::OnBnClickedButtonDelete()
{
	UpdateData(TRUE); // flow direction database <- ui
	//if (dlg.DoModal() == IDD_DIALOG_INSERT) {
	CString id = DEmployeeNumber;

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
	CEmpNumber.SetWindowText(_T(""));

	CDelete::OnOK();
}
