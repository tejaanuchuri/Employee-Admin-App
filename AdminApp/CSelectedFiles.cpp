// CSelectedFiles.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "CSelectedFiles.h"
#include "afxdialogex.h"
#include "AdminAppDlg.h"


// CSelectedFiles dialog

IMPLEMENT_DYNAMIC(CSelectedFiles, CDialogEx)

CSelectedFiles::CSelectedFiles(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SELECT_FILES, pParent)
{

}

CSelectedFiles::~CSelectedFiles()
{
}

void CSelectedFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SELECT_FILES, m_select_list);
}


BEGIN_MESSAGE_MAP(CSelectedFiles, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_FILE, &CSelectedFiles::OnBnClickedButtonImportFile)
END_MESSAGE_MAP()


BOOL CSelectedFiles::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(FALSE); // flow direction database -> ui

	int iRec = 0, j = 0;
	//m_ResetListControl();
	ListView_SetExtendedListViewStyle(m_select_list, LVS_EX_FULLROWSELECT);

	m_select_list.InsertColumn(j++, L"FirstName", LVCFMT_CENTER, 260);
	m_select_list.InsertColumn(j++, L"LastName", LVCFMT_CENTER, 260);

	for (unsigned int i = 0; i < EmployeeRecords.size(); i++) {
		Employee Record = EmployeeRecords[i];

		iRec = m_select_list.InsertItem(0, Record.FirstName, 0);
		m_select_list.SetItemText(0, 1, Record.LastName);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSelectedFiles::OnBnClickedButtonImportFile()
{
	POSITION pos = m_select_list.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		AfxMessageBox(L"No row Selected");
	}
	else {

		POSITION pos = m_select_list.GetFirstSelectedItemPosition();
		u.clear();
		if (pos != NULL) {
			while (pos)
			{
				int Row = m_select_list.GetNextSelectedItem(pos);
				SelectedEmployeesIndex.push_back(m_select_list.GetItemCount() - Row - 1);
			}
		}
		UpdateData(FALSE);
	}
	CSelectedFiles::OnOK();
}
