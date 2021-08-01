
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
#include "ChartCtrl/ChartAxis.h"
#include "afxdialogex.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartPointsSerie.h"
#include "ChartCtrl\ChartSurfaceSerie.h"
#include "ChartCtrl\ChartGrid.h"
#include "ChartCtrl\ChartBarSerie.h"
#include "ChartCtrl\ChartLabel.h"

#include "ChartCtrl\ChartAxisLabel.h"
#include "ChartCtrl\ChartStandardAxis.h"
#include "ChartCtrl\ChartDateTimeAxis.h"

#include "ChartCtrl\ChartCrossHairCursor.h"
#include "ChartCtrl\ChartDragLineCursor.h"


// CAdminAppDlg dialog



CAdminAppDlg::CAdminAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINAPP_DIALOG, pParent)
	, row(-1)
	, m_iYScale(0)
	, S_choose_filed(_T(""))
	, S_choose_filed_value(_T(""))
{
	m_iYScale = 1;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdminAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMP, emp_list);
	DDX_Control(pDX, IDC_STATIC_GRAPH_CHART, m_Graph);
	DDX_Control(pDX, IDC_CUSTOM_LINE_GRAPH, m_ChartCtrl);
	DDX_Control(pDX, IDC_RADIO_BARGRAPH, m_bar_graph_control);
	DDX_Control(pDX, IDC_RADIO_LINE_GRAPH_REPRESENTATION, m_line_graph_control);
	DDX_CBString(pDX, IDC_COMBO_CHHOSEFIELDOPTIONS, S_choose_filed);
	DDX_Text(pDX, IDC_EDIT_CHOOSEVALUE, S_choose_filed_value);
}

BEGIN_MESSAGE_MAP(CAdminAppDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CAdminAppDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CAdminAppDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CAdminAppDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CAdminAppDlg::OnBnClickedButtonDelete)
	ON_COMMAND(ID_FILE_CLOSE32771, &CAdminAppDlg::OnFileClose)
	ON_COMMAND(ID_ABOUT_ADMINAPP, &CAdminAppDlg::OnAboutAdminapp)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL_BARS, &CAdminAppDlg::OnBnClickedButtonDeleteAllBars)
	ON_BN_CLICKED(IDC_BUTTON_SELECTGRAPH, &CAdminAppDlg::OnBnClickedButtonSelectgraph)
	ON_BN_CLICKED(IDC_BUTTON_LOADBRAGRAPH, &CAdminAppDlg::OnBnClickedButtonLoadbragraph)
	ON_BN_CLICKED(IDC_RADIO_BARGRAPH, &CAdminAppDlg::OnBnClickedRadioBargraph)
	ON_BN_CLICKED(IDC_RADIO_LINE_GRAPH_REPRESENTATION, &CAdminAppDlg::OnBnClickedRadioLineGraphRepresentation)
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
	bargraph_loaded();
	linegraph_loaded();
	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CUSTOM_LINE_GRAPH)->ShowWindow(SW_SHOW);

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
	CString e_yrsofexp;

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
	//SqlString = L"SELECT TOP 1 EmpID FROM Customers ORDER BY EmpID DESC";
	//AfxMessageBox(SqlString);

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	m_ResetListControl();
	ListView_SetExtendedListViewStyle(emp_list,LVS_EX_FULLROWSELECT);
	emp_list.InsertColumn(
		0,
		L"EmpID",
		LVCFMT_LEFT,
		70);
	emp_list.InsertColumn(1, L"HireDate", LVCFMT_LEFT, 100);
	emp_list.InsertColumn(2, L"YearsOfExp", LVCFMT_LEFT, 100);

	emp_list.InsertColumn(3, L"Title", LVCFMT_CENTER, 90);
	emp_list.InsertColumn(4, L"Age", LVCFMT_LEFT, 70);
	emp_list.InsertColumn(5, L"FirstName", LVCFMT_CENTER, 130);
	emp_list.InsertColumn(6, L"LastName", LVCFMT_LEFT, 130);
	emp_list.InsertColumn(7, L"Gender", LVCFMT_CENTER, 120);
	emp_list.InsertColumn(8, L"MobilePhone", LVCFMT_LEFT, 160);
	emp_list.InsertColumn(9, L"EMail", LVCFMT_CENTER, 230);
	emp_list.InsertColumn(10, L"BirthDate", LVCFMT_LEFT, 100);
	emp_list.InsertColumn(11, L"Address", LVCFMT_CENTER, 180);
	emp_list.InsertColumn(12, L"JobTitle", LVCFMT_LEFT, 100);
	emp_list.InsertColumn(13, L"Salary", LVCFMT_CENTER, 100);

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
		recset.GetFieldValue(L"YearsOfExp", e_yrsofexp);

		// Insert values into the list control
		iRec = emp_list.InsertItem(0, e_id, 0);
		emp_list.SetItemText(0, 1, e_hiredate);
		emp_list.SetItemText(0, 2, e_yrsofexp);
		emp_list.SetItemText(0, 3, e_title);
		emp_list.SetItemText(0, 4, e_age);
		emp_list.SetItemText(0, 5, e_firstname);
		emp_list.SetItemText(0, 6, e_lastname);
		emp_list.SetItemText(0, 7, e_gender);
		emp_list.SetItemText(0, 8, e_phonenumber);
		emp_list.SetItemText(0, 9, e_email);
		emp_list.SetItemText(0, 10, e_birthdate);
		emp_list.SetItemText(0, 11, e_address);
		emp_list.SetItemText(0, 12, e_jobtitle);
		emp_list.SetItemText(0, 13, e_salary);


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

void CAdminAppDlg::bargraph_loaded()
{

	UpdateData(FALSE); // flow direction database -> ui

	CString e_id;
	CString e_age;
	CString e_yrsofexp;

	CDatabase database;
	CString sDsn;
	CString SqlString;
	int n = 0;
	CString s_id[100];
	CString s_Age[100];
	CString s_YrsOfExp[100];
	// Build ODBC connection string

	sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,sDsn);
	SqlString = L"SELECT EmpID,Age,YearsOfExp FROM EmployeeTable";

	//AfxMessageBox(SqlString);

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	while (!recset.IsEOF()) {
		// Copy each column into a variable
		recset.GetFieldValue(L"EmpID", e_id);
		recset.GetFieldValue(L"Age", e_age);
		recset.GetFieldValue(L"YearsOfExp", e_yrsofexp);

		s_id[n].Insert(n, e_id);
		s_Age[n].Insert(n, e_age);
		s_YrsOfExp[n].Insert(n, e_yrsofexp);
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
	m_Graph.SetScale(10);
	int x = 1, y = 100;
	m_Graph.GetDisplayRange(x, y);
	m_iYScale = 1;

	for (int i = 0; i < n; i++)
	{
		char tmp[20];
		int k = _wtoi(s_id[i]);
		sprintf_s(tmp, "%d", k);
		k = _wtoi(s_YrsOfExp[i]);
		m_Graph.AddBar(k, RGB(rand() % 256, rand() % 256, rand() % 256), tmp);

		//sprintf(tmp, "%d", i);
		//m_BarCombo.AddString(tmp);
	}
	//m_Graph.DeleteBar(1);
	m_Graph.SetBGColor(RGB(255, 229, 204));
	m_Graph.SetAxisColor(RGB(102, 0, 0));
	m_Graph.SetTextColor(RGB(102, 102, 255));

	UpdateData(FALSE);
}

void CAdminAppDlg::bargraph_update()
{
	UpdateData(FALSE); // flow direction database -> ui

	CString e_id;
	CString e_age;
	CString e_yrsofexp;

	CDatabase database;
	CString sDsn;
	CString SqlString;
	int n = 0;
	CString s_id[100];
	CString s_Age[100];
	CString s_YrsOfExp[100];
	// Build ODBC connection string

	sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,sDsn);
	SqlString = L"SELECT EmpID,Age,YearsOfExp FROM EmployeeTable";

	//AfxMessageBox(SqlString);

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	while (!recset.IsEOF()) {

		// Copy each column into a variable
		recset.GetFieldValue(L"EmpID", e_id);
		recset.GetFieldValue(L"Age", e_age);
		recset.GetFieldValue(L"YearsOfExp", e_yrsofexp);

		s_id[n].Insert(n, e_id);
		s_Age[n].Insert(n, e_age);
		s_YrsOfExp[n].Insert(n, e_yrsofexp);
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
	m_Graph.SetScale(10);
	int x = 1, y = 100;
	m_Graph.GetDisplayRange(x, y);
	m_iYScale = 3;

	for (int i = 0; i < n; i++)
	{
		//char tmp[20];
		//int k = _wtoi(s_id[i]);
		//sprintf_s(tmp, "EmpID - %d", k);
		int k = _wtoi(s_YrsOfExp[i]);
		m_Graph.SetBarValue(i, k, TRUE);
		//m_Graph.AddBar(k, RGB(rand() % 256, rand() % 256, rand() % 256), tmp);

		//sprintf(tmp, "%d", i);
		//m_BarCombo.AddString(tmp);
	}
	m_Graph.SetBGColor(RGB(255, 229, 204));
	m_Graph.SetAxisColor(RGB(102, 0, 0));
	m_Graph.SetTextColor(RGB(102, 102, 255));

	UpdateData(FALSE);
}

void CAdminAppDlg::bargraph_empty()
{
	UpdateData(FALSE);
	while (1) {
		int m = m_Graph.GetNumberOfBars();
		if (m == 0) {
			break;
		}
		//	MessageBox((LPCTSTR)itoa(m));
		for (int i = 0; i < m; i++) {
			m_Graph.DeleteBar(i);
			//m_Graph.DrawGraph();
		}
		UpdateWindow();
	}
	return;
}

void CAdminAppDlg::linegraph_loaded()
{
	CChartCtrl ref;
	ref.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);
	pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAxisColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	pBottomAxis->SetAxisColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//m_ChartCtrl.SetBackColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	pBottomAxis->SetMinMax(2000, 2015);

	pLeftAxis->SetMinMax(1, 20);
	pLeftAxis->GetLabel()->SetText(L"Employee Id");

	pBottomAxis->GetLabel()->SetText(L"Year of Employee hired");
	pBottomAxis->SetTickIncrement(false, 1);
	pLeftAxis->SetTickIncrement(false, 1);
	pBottomAxis->SetDiscrete(false);
	pLeftAxis->SetDiscrete(false);
	pBottomAxis->EnableScrollBar(true);
	pLeftAxis->EnableScrollBar(true);




	UpdateData(FALSE); // flow direction database -> ui

	CString e_id;
	CString e_age;
	CString e_hiredate;
	CString e_yrsofexp;

	CDatabase database;
	CString sDsn;
	CString SqlString;
	unsigned int n = 0;
	CString s_id[100];
	CString s_Age[100];
	CString s_YrsOfExp[100];
	CString s_hiredate[100];
	// Build ODBC connection string

	sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,sDsn);
	SqlString = L"SELECT EmpID,Age,YearsOfExp,Hiredate FROM EmployeeTable";

	//AfxMessageBox(SqlString);

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	while (!recset.IsEOF()) {

		// Copy each column into a variable
		recset.GetFieldValue(L"EmpID", e_id);
		recset.GetFieldValue(L"Age", e_age);
		recset.GetFieldValue(L"YearsOfExp", e_yrsofexp);
		recset.GetFieldValue(L"Hiredate", e_hiredate);


		s_id[n].Insert(n, e_id);
		s_Age[n].Insert(n, e_age);
		s_YrsOfExp[n].Insert(n, e_yrsofexp);
		s_hiredate[n].Insert(n, e_hiredate);
			n++;
			recset.MoveNext();
	}
	database.Close();
	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;





	for (unsigned int i = 0; i < n; i++)
	{
		pSeries = m_ChartCtrl.CreateLineSerie();
		//pSeries->ClearSerie();
		pSeries->SetWidth(5); //line width
		pSeries->SetColor(RGB(rand() % 256, rand() % 256, rand() % 256)); //color of line
		double XVal[2] = { 0 };
		double YVal[2] = { 0 };
		//pSeries->SetName(str("Emp"));


		COleDateTime date;
		date.ParseDateTime(s_hiredate[i]);
		int year = date.GetYear();
		int j = 0;
		int k = _wtoi(s_YrsOfExp[i]);
		XVal[j] = year;
		YVal[j] = _wtoi(s_id[i]);
		j++;
		YVal[j] = _wtoi(s_id[i]);
		XVal[j] = XVal[j - 1] + k;
		j++;
		unsigned int l = j;
		pSeries->SetPoints(XVal, YVal, l);
		//pSeries->SetShadowColor(RGB(50, 50, 50));
		//pSeries->SetShadowDepth(5);
		//pSeries->EnableShadow(true);
		m_ChartCtrl.EnableRefresh(true);
	}


	return;
}

void CAdminAppDlg::linegraph_update()
{
	UpdateData(FALSE); // flow direction database -> ui

	CString e_id;
	CString e_age;
	CString e_yrsofexp;

	CDatabase database;
	CString sDsn;
	CString SqlString;
	int n = 0;
	CString s_id[100];
	CString s_Age[100];
	CString s_YrsOfExp[100];
	// Build ODBC connection string

	sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,sDsn);
	SqlString = L"SELECT EmpID,Age,YearsOfExp FROM EmployeeTable";

	//AfxMessageBox(SqlString);

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	while (!recset.IsEOF()) {

		// Copy each column into a variable
		recset.GetFieldValue(L"EmpID", e_id);
		recset.GetFieldValue(L"Age", e_age);
		recset.GetFieldValue(L"YearsOfExp", e_yrsofexp);

		s_id[n].Insert(n, e_id);
		s_Age[n].Insert(n, e_age);
		s_YrsOfExp[n].Insert(n, e_yrsofexp);
			n++;
			recset.MoveNext();
	}
	database.Close();
	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;

	double XVal[100] = { 0 };
	double YVal[100] = { 0 };


	for (int i = 0; i < n; i++)
	{
		int k = _wtoi(s_id[i]);
		XVal[i] = k;
		k = _wtoi(s_YrsOfExp[i]);
		YVal[i] = k;
	}
	unsigned int l = n;
	pSeries->SetPoints(XVal, YVal, l);

	m_ChartCtrl.EnableRefresh(true);

	UpdateData(FALSE);
}

void CAdminAppDlg::linegraph_empty()
{
	m_ChartCtrl.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);
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

		UpdateData(FALSE); // flow direction database -> ui

		CString e_id;
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
			SqlString = L"SELECT TOP 1 EmpID FROM EmployeeTable ORDER BY EmpID DESC";
			//AfxMessageBox(SqlString);

			recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

			while (!recset.IsEOF()) {
				// Copy each column into a variable
				recset.GetFieldValue(L"EmpID", e_id);
				recset.MoveNext();
			}
			database.Close();
		}CATCH(CDBException, e) {
			// If a database exception occured, show error msg
			AfxMessageBox(L"Database error: " + e->m_strError);
		}
		END_CATCH;

		char tmp[20];
		int k = _wtoi(e_id);
		sprintf_s(tmp, "EID-%d", k);
		k = _wtoi(dlg.e_yrsofexp);
		m_Graph.AddBar(k, RGB(rand() % 256, rand() % 256, rand() % 256), tmp);
		m_Graph.DrawGraph();
		//linegraph_empty();
		//linegraph_loaded();
		UpdateWindow();
	}
}


void CAdminAppDlg::OnBnClickedButtonUpdate()
{
	UpdateData(TRUE); // flow direction database <- ui

	row = emp_list.GetSelectionMark();
	//MessageBox((LPCTSTR)row);
	//AfxMessageBox(row);
	if (row < 0) {
		AfxMessageBox(L"No row Selected");
	}
	else {



		CString id = emp_list.GetItemText(row, 0);
		CString emp_title = emp_list.GetItemText(row, 3);
		CString emp_age = emp_list.GetItemText(row, 4);
		CString emp_firstname = emp_list.GetItemText(row, 5);
		CString emp_lastname = emp_list.GetItemText(row, 6);
		CString emp_gender = emp_list.GetItemText(row, 7);
		CString emp_phonenumber = emp_list.GetItemText(row, 8);
		CString emp_email = emp_list.GetItemText(row, 9);
		CString emp_address = emp_list.GetItemText(row, 11);
		CString emp_jobtitle = emp_list.GetItemText(row, 12);
		CString emp_salary = emp_list.GetItemText(row, 13);
		COleDateTime emp_datebirth;
		emp_datebirth.ParseDateTime(emp_list.GetItemText(row, 10));
		COleDateTime employee_hiredate;
		employee_hiredate.ParseDateTime(emp_list.GetItemText(row, 1));
		CString emp_yrsofexp = emp_list.GetItemText(row, 2);


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
		u.u_yrsofexp = emp_yrsofexp;
		if (u.DoModal() == IDOK) {

			MessageBox(L"Update Record Sucessfully...!");
			emp_data_load();
			bargraph_update();

			m_ChartCtrl.RemoveAllSeries();
			linegraph_loaded();

		}
		UpdateWindow();
	}

}


void CAdminAppDlg::OnBnClickedButtonSearch()
{
	UpdateData(TRUE); // flow direction database <- ui
	//if (dlg.DoModal() == IDD_DIALOG_INSERT) {
	CString ChooseField = S_choose_filed;
	CString EnterValue = S_choose_filed_value;

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
		if (EnterValue.IsEmpty()) {
			SqlString = L"SELECT * FROM EmployeeTable";
		}
		else {

			SqlString = L"SELECT * FROM EmployeeTable WHERE ";
			SqlString.Append(ChooseField);
			SqlString.Append(_T(" LIKE "));
			if (ChooseField == L"EmpID") {
				SqlString.Append(_T("'%" + EnterValue + "%'"));
			}
			else {
				SqlString.Append(_T("'%" + EnterValue + "%'"));
			}
		}
		//AfxMessageBox(SqlString);
		//database.ExecuteSQL(SqlString);

		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
		ResetListControl();
		ListView_SetExtendedListViewStyle(emp_list, LVS_EX_GRIDLINES);
		emp_list.InsertColumn(
			0,              // Rank/order of item
			L"EmpID",          // Caption for this header
			LVCFMT_LEFT,    // Relative position of items under header
			42);           // Width of items under header

		emp_list.InsertColumn(1, L"Title", LVCFMT_CENTER, 80);
		emp_list.InsertColumn(2, L"Age", LVCFMT_LEFT, 100);
		emp_list.InsertColumn(3, L"FirstName", LVCFMT_CENTER, 80);
		emp_list.InsertColumn(4, L"LastName", LVCFMT_LEFT, 100);
		emp_list.InsertColumn(5, L"Gender", LVCFMT_CENTER, 80);
		emp_list.InsertColumn(6, L"MobilePhone", LVCFMT_LEFT, 100);
		emp_list.InsertColumn(7, L"EMail", LVCFMT_CENTER, 80);
		emp_list.InsertColumn(8, L"BirthDate", LVCFMT_LEFT, 100);
		emp_list.InsertColumn(9, L"Address", LVCFMT_CENTER, 80);
		emp_list.InsertColumn(10, L"JobTitle", LVCFMT_LEFT, 100);
		emp_list.InsertColumn(11, L"Salary", LVCFMT_CENTER, 80);
		emp_list.InsertColumn(12, L"HireDate", LVCFMT_LEFT, 100);
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
		/*if (count == 0) {
			AfxMessageBox(L"Record Not Found...!");
		}*/
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

void CAdminAppDlg::ResetListControl() {
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
		bargraph_empty();
		bargraph_loaded();
		//m_Graph.DeleteBar(m_Graph.GetNumberOfBars() - row);
		m_Graph.DrawGraph();
		linegraph_empty();
		//linegraph_loaded();

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




void CAdminAppDlg::OnBnClickedButtonDeleteAllBars()
{
	bargraph_empty();
	m_Graph.DrawGraph();
	linegraph_empty();
	UpdateData(FALSE);
	//AfxMessageBox(m_Graph.GetNumberOfBars());
	UpdateWindow();
}


void CAdminAppDlg::OnBnClickedButtonSelectgraph()
{
	POSITION pos = emp_list.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		AfxMessageBox(L"No row Selected");
	}
	else {
		bargraph_empty();
		m_Graph.DrawGraph();

		m_ChartCtrl.RemoveAllSeries();


		double XVal[100] = { 0 };
		double YVal[100] = { 0 };
		int n = 0;




		CChartCtrl ref;
		ref.RemoveAllSeries();
		m_ChartCtrl.EnableRefresh(true);
		pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
		pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
		pLeftAxis->SetAxisColor(RGB(rand() % 256, rand() % 256, rand() % 256));
		pBottomAxis->SetAxisColor(RGB(rand() % 256, rand() % 256, rand() % 256));
		//m_ChartCtrl.SetBackColor(RGB(rand() % 256, rand() % 256, rand() % 256));
		pBottomAxis->SetMinMax(2000, 2015);

		pLeftAxis->SetMinMax(1, 20);
		pLeftAxis->GetLabel()->SetText(L"Employee Id");

		pBottomAxis->GetLabel()->SetText(L"Year of Employee hired");
		pBottomAxis->SetTickIncrement(false, 1);
		pLeftAxis->SetTickIncrement(false, 1);
		pBottomAxis->SetDiscrete(false);
		pLeftAxis->SetDiscrete(false);
		pBottomAxis->EnableScrollBar(true);
		pLeftAxis->EnableScrollBar(true);


		CString id;
		CString emp_age;
		//id = emp_list.GetItemText(row, 0);
		//emp_age = emp_list.GetItemText(row, 2);
		m_Graph.SetScale(10);
		int x = 1, y = 100;
		m_Graph.GetDisplayRange(x, y);
		m_iYScale = 1;

		POSITION pos = emp_list.GetFirstSelectedItemPosition();

		if (pos != NULL) {
			while (pos)
			{
				int Row = emp_list.GetNextSelectedItem(pos);
				CString id = emp_list.GetItemText(Row, 0);
				CString yrsofexp = emp_list.GetItemText(Row, 2);
				char tmp[20];
				int k = _wtoi(id);
				XVal[n] = k;
				sprintf_s(tmp, "%d", k);
				k = _wtoi(yrsofexp);
				YVal[n] = k;
				n++;
				m_Graph.AddBar(k, RGB(rand() % 256, rand() % 256, rand() % 256), tmp);
				pSeries = m_ChartCtrl.CreateLineSerie();
				//pSeries->ClearSerie();
				pSeries->SetWidth(5); //line width
				pSeries->SetColor(RGB(rand() % 256, rand() % 256, rand() % 256)); //color of line
				double XVal[2] = { 0 };
				double YVal[2] = { 0 };
				//pSeries->SetName(str("Emp"));


				COleDateTime date;
				date.ParseDateTime(emp_list.GetItemText(Row, 1));
				int year = date.GetYear();
				int j = 0;
				k = _wtoi(yrsofexp);
				XVal[j] = year;
				YVal[j] = _wtoi(id);
				j++;
				YVal[j] = _wtoi(id);
				XVal[j] = XVal[j - 1] + k;
				j++;
				unsigned int l = j;
				pSeries->SetPoints(XVal, YVal, l);
				m_ChartCtrl.EnableRefresh(true);
			}
		}
		m_Graph.SetBGColor(RGB(255, 229, 204));
		m_Graph.SetAxisColor(RGB(102, 0, 0));
		m_Graph.SetTextColor(RGB(102, 102, 255));


		UpdateData(FALSE);

	}
}


void CAdminAppDlg::OnBnClickedButtonLoadbragraph()
{
	bargraph_empty();
	bargraph_loaded();
	m_Graph.DrawGraph();
	linegraph_empty();
	linegraph_loaded();
	UpdateWindow();
	return;
}


void CAdminAppDlg::OnBnClickedRadioBargraph()
{
	UpdateData(FALSE);
	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CUSTOM_LINE_GRAPH)->ShowWindow(SW_HIDE);
	UpdateWindow();
}


void CAdminAppDlg::OnBnClickedRadioLineGraphRepresentation()
{
	UpdateData(FALSE);
	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CUSTOM_LINE_GRAPH)->ShowWindow(SW_SHOW);
	UpdateWindow();

}
