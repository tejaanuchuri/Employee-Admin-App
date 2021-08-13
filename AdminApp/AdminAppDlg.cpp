
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
#include "CSelectedFiles.h"
#include <set>
#include "CXml.h"
#include "Employee.h"

// CAdminAppDlg dialog;



CAdminAppDlg::CAdminAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINAPP_DIALOG, pParent)
	, row(-1)
	, m_iYScale(0)
	, S_choose_filed(_T(""))
	, S_choose_filed_value(_T(""))
	, pBottomAxis()
	, pLeftAxis()
	, pSeries()
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
	DDX_Control(pDX, IDC_COMBO_CHHOSEFIELDOPTIONS, CChooseType);
	DDX_Control(pDX, IDC_EDIT_CHOOSEVALUE, CChoosetypevalue);
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
	ON_COMMAND(ID_OPERATIONS_EXPORT, &CAdminAppDlg::OnOperationsExport)
	ON_COMMAND(ID_OPERATIONS_IMPORT, &CAdminAppDlg::OnOperationsImport)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_FILE, &CAdminAppDlg::OnBnClickedButtonImportFile)
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
	display_all_employee_records_in_the_listview_representation();
	display_all_employee_records_in_the_bargraph_representation();
	delete_all_employee_records_in_the_linegraph();
	display_all_employee_records_in_the_linegraph();

	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_HIDE);
	m_line_graph_control.SetState(true);
	m_line_graph_control.SetCheck(1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CAdminAppDlg::display_all_employee_records_in_the_listview_representation() {
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
		int row = emp_list.GetItemCount();
		iRec = emp_list.InsertItem(row, e_id, 0);
		emp_list.SetItemText(row, 1, e_hiredate);
		emp_list.SetItemText(row, 2, e_yrsofexp);
		emp_list.SetItemText(row, 3, e_title);
		emp_list.SetItemText(row, 4, e_age);
		emp_list.SetItemText(row, 5, e_firstname);
		emp_list.SetItemText(row, 6, e_lastname);
		emp_list.SetItemText(row, 7, e_gender);
		emp_list.SetItemText(row, 8, e_phonenumber);
		emp_list.SetItemText(row, 9, e_email);
		emp_list.SetItemText(row, 10, e_birthdate);
		emp_list.SetItemText(row, 11, e_address);
		emp_list.SetItemText(row, 12, e_jobtitle);
		emp_list.SetItemText(row, 13, e_salary);
		Employee Record;
		Record.Id = e_id;
		Record.HireDate = e_hiredate;
		Record.YearsOfExperience = e_yrsofexp;
		Record.Title = e_title;
		Record.Age = e_age;
		Record.FirstName = e_firstname;
		Record.LastName = e_lastname;
		Record.Gender = e_gender;
		Record.MobileNumber = e_phonenumber;
		Record.Email = e_email;
		Record.DateOfBirth = e_birthdate;
		Record.Address = e_address;
		Record.JobTitle = e_jobtitle;
		Record.Salary = e_salary;
		EmployeeRecords.push_back(Record);
		recset.MoveNext();
	}
	database.Close();
	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;
}

void CAdminAppDlg::display_all_employee_records_in_the_bargraph_representation()
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
void CAdminAppDlg::delete_all_employee_records_in_the_bargraph()
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

void CAdminAppDlg::display_all_employee_records_in_the_linegraph()
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



	//pSeries[n]; = m_ChartCtrl.CreateLineSerie();

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

		m_ChartCtrl.EnableRefresh(true);
	}


	return;
}
void CAdminAppDlg::delete_all_employee_records_in_the_linegraph()
{
	m_ChartCtrl.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);
}

void CAdminAppDlg::displayallrecords()
{
	UpdateData(FALSE);
	ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
	removeallrecords();
	int iRec = 0;
	for (unsigned int i = 0; i < EmployeeRecords.size(); i++) {
		Employee Record = EmployeeRecords[i];
		int row = emp_list.GetItemCount();
		iRec = emp_list.InsertItem(row, Record.Id, 0);
		emp_list.SetItemText(row, 1, Record.HireDate);
		emp_list.SetItemText(row, 2, Record.YearsOfExperience);
		emp_list.SetItemText(row, 3, Record.Title);
		emp_list.SetItemText(row, 4, Record.Age);
		emp_list.SetItemText(row, 5, Record.FirstName);
		emp_list.SetItemText(row, 6, Record.LastName);
		emp_list.SetItemText(row, 7, Record.Gender);
		emp_list.SetItemText(row, 8, Record.MobileNumber);
		emp_list.SetItemText(row, 9, Record.Email);
		emp_list.SetItemText(row, 10, Record.DateOfBirth);
		emp_list.SetItemText(row, 11, Record.Address);
		emp_list.SetItemText(row, 12, Record.JobTitle);
		emp_list.SetItemText(row, 13, Record.Salary);
	}
	emp_list.UpdateWindow();
	UpdateWindow();
	UpdateData(FALSE);
}

void CAdminAppDlg::removeallrecords()
{
	while (emp_list.GetItemCount() != 0) {
		emp_list.DeleteItem(0);
	}
}

CString CAdminAppDlg::Add_elem(CString s, CString v)
{
	return Start_Tag(s) + v + End_Tag(s);
}

CString CAdminAppDlg::Start_Tag(CString s)
{
	return open_tag_symbol + s + close_tag_symbol;
}

CString CAdminAppDlg::End_Tag(CString s)
{
	return open_end_tag_symbol + s + close_tag_symbol_with_nextline;
}

CString CAdminAppDlg::root_start_tag(CString s)
{
	return open_tag_symbol + s + close_tag_symbol_with_nextline;
}

CString CAdminAppDlg::root_end_tag(CString s)
{
	return open_end_tag_symbol + s + close_tag_symbol_with_nextline;
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
		//display_all_employee_records_in_the_listview_representation();

		UpdateData(FALSE); // flow direction database -> ui
		CString e_age = dlg.emp_age;
		CString e_title = dlg.emp_title;
		CString e_firstname = dlg.emp_firstname;
		CString e_lastname = dlg.emp_lastname;
		CString e_gender = dlg.emp_gender;
		CString e_phonenumber = dlg.emp_phonenumber;
		CString e_email = dlg.emp_email;
		CString e_birthdate = dlg.emp_datebirth.Format(_T("%d-%m-%Y"));
		CString e_address = dlg.emp_address;
		CString e_jobtitle = dlg.emp_jobtitle;
		CString e_salary = dlg.emp_salary;
		CString e_hiredate = dlg.employee_hiredate.Format(_T("%d-%m-%Y"));
		CString e_id = dlg.i_empid;
		CString yrsofexps;

		COleDateTime date;
		date = COleDateTime::GetCurrentTime();
		int cur_year = _wtoi(date.Format(_T("%Y")));
		int hireyear = _wtoi(dlg.employee_hiredate.Format(_T("%Y")));
		int cur_month = _wtoi(date.Format(_T("%m")));
		int hire_month = _wtoi(dlg.employee_hiredate.Format(_T("%m")));
		int cur_date = _wtoi(date.Format(_T("%d")));
		int hire_date = _wtoi(dlg.employee_hiredate.Format(_T("%d")));
		int b_date = _wtoi(dlg.emp_datebirth.Format(_T("%d")));
		int b_month = _wtoi(dlg.emp_datebirth.Format(_T("%m")));
		int b_year = _wtoi(dlg.emp_datebirth.Format(_T("%Y")));
		E_DATE dt1 = { hire_date, hire_month, hireyear };
		E_DATE dt2 = { cur_date, cur_month, cur_year };
		E_DATE dt3 = { b_date, b_month, b_year };

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

		e_age.Format(_T("%d"), ((getDiff(dt3, dt2) - remove_leap_year) / 365));
		//AfxMessageBox(age_);
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
		yrsofexps.Format(_T("%d"), ((getDiff(dt1, dt2) - remove_leap_year) / 365));


		ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
		int row = emp_list.GetItemCount();

		int iRec = 0;
		iRec = emp_list.InsertItem(row, e_id, 0);
		emp_list.SetItemText(row, 3, e_title);
		emp_list.SetItemText(row, 4, e_age);
		emp_list.SetItemText(row, 5, e_firstname);
		emp_list.SetItemText(row, 6, e_lastname);
		emp_list.SetItemText(row, 7, e_gender);
		emp_list.SetItemText(row, 8, e_phonenumber);
		emp_list.SetItemText(row, 9, e_email);
		emp_list.SetItemText(row, 11, e_address);
		emp_list.SetItemText(row, 12, e_jobtitle);
		emp_list.SetItemText(row, 13, e_salary);
		emp_list.SetItemText(row, 10, e_birthdate);
		emp_list.SetItemText(row, 1, e_hiredate);
		emp_list.SetItemText(row, 2, yrsofexps);

		emp_list.UpdateWindow();

		char tmp[20];
		int k = _wtoi(e_id);
		sprintf_s(tmp, "%d", k);
		k = _wtoi(yrsofexps);
		m_Graph.AddBar(k, RGB(rand() % 256, rand() % 256, rand() % 256), tmp);
		m_Graph.DrawGraph();

		pSeries = m_ChartCtrl.CreateLineSerie();
		pSeries->SetWidth(5); //line width
		pSeries->SetColor(RGB(rand() % 256, rand() % 256, rand() % 256)); //color of line
		double XVal[2] = { 0 };
		double YVal[2] = { 0 };

		int year = _wtoi(dlg.employee_hiredate.Format(_T("%Y")));
		int j = 0;
		k = _wtoi(yrsofexps);
		XVal[j] = year;
		YVal[j] = _wtoi(e_id);
		j++;
		YVal[j] = _wtoi(e_id);
		XVal[j] = XVal[j - 1] + k;
		j++;
		unsigned int l = j;
		pSeries->SetPoints(XVal, YVal, l);
		m_ChartCtrl.EnableRefresh(true);
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
			COleDateTime date;
			date = COleDateTime::GetCurrentTime();
			int cur_year = _wtoi(date.Format(_T("%Y")));
			int hireyear = _wtoi(u.u_hiredate.Format(_T("%Y")));
			int cur_month = _wtoi(date.Format(_T("%m")));
			int hire_month = _wtoi(u.u_hiredate.Format(_T("%m")));
			int cur_date = _wtoi(date.Format(_T("%d")));
			int hire_date = _wtoi(u.u_hiredate.Format(_T("%d")));
			int b_date = _wtoi(u.u_dateofbirthdate.Format(_T("%d")));
			int b_month = _wtoi(u.u_dateofbirthdate.Format(_T("%m")));
			int b_year = _wtoi(u.u_dateofbirthdate.Format(_T("%Y")));
			E_DATE dt1 = { hire_date, hire_month, hireyear };
			E_DATE dt2 = { cur_date, cur_month, cur_year };
			E_DATE dt3 = { b_date, b_month, b_year };

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

			emp_age.Format(_T("%d"), ((getDiff(dt3, dt2) - remove_leap_year) / 365));

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
			emp_yrsofexp.Format(_T("%d"), ((getDiff(dt1, dt2) - remove_leap_year) / 365));

			ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
			emp_list.SetItemText(row, 0, u.u_id);
			emp_list.SetItemText(row, 3, u.u_title);
			emp_list.SetItemText(row, 4, emp_age);
			emp_list.SetItemText(row, 5, u.u_firstname);
			emp_list.SetItemText(row, 6, u.u_lastname);
			emp_list.SetItemText(row, 7, u.u_gender);
			emp_list.SetItemText(row, 8, u.u_phonenumber);
			emp_list.SetItemText(row, 9, u.u_email);
			emp_list.SetItemText(row, 11, u.u_address);
			emp_list.SetItemText(row, 12, u.u_jobtitle);
			emp_list.SetItemText(row, 13, u.u_salary);
			emp_list.SetItemText(row, 10, u.u_dateofbirthdate.Format(_T("%d-%m-%Y")));
			emp_list.SetItemText(row, 1, u.u_hiredate.Format(_T("%d-%m-%Y")));
			emp_list.SetItemText(row, 2, emp_yrsofexp);

			emp_list.UpdateWindow();
			MessageBox(L"Update Record Sucessfully...!");


			m_Graph.SetBarValue(m_Graph.GetNumberOfBars() - row - 1, _wtoi(emp_yrsofexp), TRUE);
			m_Graph.DrawGraph();


			delete_all_employee_records_in_the_linegraph();
			display_all_employee_records_in_the_linegraph();

		}
		UpdateWindow();
	}

}


void CAdminAppDlg::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);

	CString ChooseField = S_choose_filed;
	CString EnterValue = S_choose_filed_value;
	map<CString, int> m;
	m.insert(make_pair(L"EmpID", 0));
	m.insert(make_pair(L"Hiredate", 1));
	m.insert(make_pair(L"YearsOfExp", 2));
	m.insert(make_pair(L"Title", 3));
	m.insert(make_pair(L"Age", 4));
	m.insert(make_pair(L"FirstName", 5));
	m.insert(make_pair(L"LastName", 6));
	m.insert(make_pair(L"Gender", 7));
	m.insert(make_pair(L"MobilePhone", 8));
	m.insert(make_pair(L"EMail", 9));
	m.insert(make_pair(L"BirthDate", 10));
	m.insert(make_pair(L"Address", 11));
	m.insert(make_pair(L"JobTitle", 12));
	m.insert(make_pair(L"Salary", 13));

	displayallrecords();
	if (EnterValue.IsEmpty()) {
		CChooseType.SetWindowText(_T(""));
		CChoosetypevalue.SetWindowText(_T(""));
	}
	else {
		UpdateData(FALSE);
		vector<int> record_index;
		record_index.clear();
		int cnt = EmployeeRecords.size();
		CString q;
		q.Format(_T("%d"), cnt);
		//MessageBox(q);
		for (int i = 0; i < cnt; i++) {
			CString temp = emp_list.GetItemText(i, m[ChooseField]);
			if (m[ChooseField] == 0 || m[ChooseField] == 1 || m[ChooseField] == 2 || m[ChooseField] == 4 || m[ChooseField] == 10 || m[ChooseField] == 13 || m[ChooseField] == 8) {
				//MessageBox(temp);
				//MessageBox(S_choose_filed_value);
				if (compare_twostrings(temp, S_choose_filed_value)) {
					record_index.push_back(i);
					//MessageBox(L"In");
				}
			}
			else {
				if (temp.Find(S_choose_filed_value) != -1) {
					//MessageBox(temp);
					record_index.push_back(i);
				}
			}
		}
		removeallrecords();
		//m_ResetListControl();
		UpdateData(FALSE);
		ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
		int iRec = 0;
		for (unsigned int i = 0; i < record_index.size(); i++) {
			Employee Record = EmployeeRecords[record_index[i]];
			int row = emp_list.GetItemCount();
			iRec = emp_list.InsertItem(row, Record.Id, 0);
			emp_list.SetItemText(row, 1, Record.HireDate);
			emp_list.SetItemText(row, 2, Record.YearsOfExperience);
			emp_list.SetItemText(row, 3, Record.Title);
			emp_list.SetItemText(row, 4, Record.Age);
			emp_list.SetItemText(row, 5, Record.FirstName);
			emp_list.SetItemText(row, 6, Record.LastName);
			emp_list.SetItemText(row, 7, Record.Gender);
			emp_list.SetItemText(row, 8, Record.MobileNumber);
			emp_list.SetItemText(row, 9, Record.Email);
			emp_list.SetItemText(row, 10, Record.DateOfBirth);
			emp_list.SetItemText(row, 11, Record.Address);
			emp_list.SetItemText(row, 12, Record.JobTitle);
			emp_list.SetItemText(row, 13, Record.Salary);
		}
		emp_list.UpdateWindow();
	}
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

void CAdminAppDlg::s_ResetListControl()
{
	CSelectedFiles d;
	d.m_select_list.DeleteAllItems();
	int iNbrOfColumns = 0, i;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)d.m_select_list.GetDlgItem(0);
	if (pHeader) {
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (i = iNbrOfColumns; i >= 0; i--) {
		d.m_select_list.DeleteColumn(i);
	}
}

void CAdminAppDlg::OnBnClickedButtonDelete()
{
	UpdateData(TRUE);

	row = emp_list.GetSelectionMark();
	if (row < 0) {
		AfxMessageBox(L"No row Selected");
	}
	else {
		vector<Employee>::iterator it = EmployeeRecords.begin();
		EmployeeRecords.erase(it + row);
		CString id = emp_list.GetItemText(row, 0);
		emp_list.DeleteItem(row);
		UpdateWindow();
		m_Graph.DeleteBar(row);
		m_Graph.DrawGraph();

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


		delete_all_employee_records_in_the_linegraph();
		display_all_employee_records_in_the_linegraph();
		m_ChartCtrl.EnableRefresh(true);
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
	delete_all_employee_records_in_the_bargraph();
	m_Graph.DrawGraph();
	delete_all_employee_records_in_the_linegraph();
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
		delete_all_employee_records_in_the_bargraph();
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
	delete_all_employee_records_in_the_bargraph();
	display_all_employee_records_in_the_bargraph_representation();
	m_Graph.DrawGraph();
	delete_all_employee_records_in_the_linegraph();
	display_all_employee_records_in_the_linegraph();
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


void CAdminAppDlg::OnOperationsExport()
{

	POSITION Pos = emp_list.GetFirstSelectedItemPosition();
	if (Pos == NULL) {
		AfxMessageBox(L"No row Selected");
	}
	else {
		Employee EmployeeRecord;
		vector<Employee> EmployeeRecords;
		POSITION Pos = emp_list.GetFirstSelectedItemPosition();

		if (Pos != NULL) {
			while (Pos)
			{
				int Row = emp_list.GetNextSelectedItem(Pos);
				EmployeeRecords.push_back(GetRecord(Row));
			}
		}
		CXml xml;
		xml.Export(EmployeeRecords);
		MessageBox(L"Xml Files Generate Sucessfully...!");
	}

	return;
}


void CAdminAppDlg::OnOperationsImport()
{
	CString sFilter = _T("Xml Files (*.xml)|*.xml");

	CFileDialog dlg(TRUE, _T("*.xml"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, sFilter, this);

	vector<Employee> IEmployeeRecords;
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos(dlg.GetStartPosition());
		while (pos)
		{
			CString FilePath = dlg.GetNextPathName(pos);
			CXml xml;
			IEmployeeRecords = xml.Import(FilePath);

			CSelectedFiles dlg;
			dlg.EmployeeRecords = IEmployeeRecords;
			if (dlg.DoModal() == IDOK) {
				UpdateData(FALSE);
				int iRec = 0;
				ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
				for (unsigned int i = 0; i < dlg.SelectedEmployeesIndex.size(); i++) {
					Employee Record = IEmployeeRecords[dlg.SelectedEmployeesIndex[i]];
					int row = emp_list.GetItemCount();
					iRec = emp_list.InsertItem(row, Record.Id, 0);
					emp_list.SetItemText(row, 1, Record.HireDate);
					emp_list.SetItemText(row, 2, Record.YearsOfExperience);
					emp_list.SetItemText(row, 3, Record.Title);
					emp_list.SetItemText(row, 4, Record.Age);
					emp_list.SetItemText(row, 5, Record.FirstName);
					emp_list.SetItemText(row, 6, Record.LastName);
					emp_list.SetItemText(row, 7, Record.Gender);
					emp_list.SetItemText(row, 8, Record.MobileNumber);
					emp_list.SetItemText(row, 9, Record.Email);
					emp_list.SetItemText(row, 10, Record.DateOfBirth);
					emp_list.SetItemText(row, 11, Record.Address);
					emp_list.SetItemText(row, 12, Record.JobTitle);
					emp_list.SetItemText(row, 13, Record.Salary);
					EmployeeRecords.push_back(Record);

					char tmp[20];
					int k = _wtoi(Record.Id);
					sprintf_s(tmp, "%d", k);
					k = _wtoi(Record.YearsOfExperience);
					m_Graph.AddBar(k, RGB(rand() % 256, rand() % 256, rand() % 256), tmp);
					m_Graph.DrawGraph();

					pSeries = m_ChartCtrl.CreateLineSerie();
					pSeries->SetWidth(5);
					pSeries->SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
					double XVal[2] = { 0 };
					double YVal[2] = { 0 };

					COleDateTime date;
					date.ParseDateTime(Record.HireDate);
					int year = date.GetYear();
					int j = 0;
					k = _wtoi(Record.YearsOfExperience);
					XVal[j] = year;
					YVal[j] = _wtoi(Record.Id);
					j++;
					YVal[j] = _wtoi(Record.Id);
					XVal[j] = XVal[j - 1] + k;
					j++;
					unsigned int l = j;
					pSeries->SetPoints(XVal, YVal, l);
					m_ChartCtrl.EnableRefresh(true);
				}

				emp_list.UpdateWindow();

				UpdateWindow();

				CDatabase database;
				CString sDsn;
				CString SqlString;
				CString out = L" ,";
				CString quo = L"'";

				sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
				TRY{
					database.Open(NULL,false,false,sDsn);

				for (unsigned int i = 0; i < dlg.SelectedEmployeesIndex.size(); i++) {
					Employee Record = IEmployeeRecords[dlg.SelectedEmployeesIndex[i]];
					SqlString.Empty();
					SqlString.Append(_T("INSERT INTO EmployeeTable(EmpID,Hiredate,YearsOfExp,Title,Age,FirstName,LastName,Gender,MobilePhone,EMail,BirthDate,Address,JobTitle,Salary) VALUES ("));
					SqlString.Append(quo);
					SqlString.Append(Record.Id);
					SqlString.Append(quo);
					SqlString.Append(out);

					//COleDateTime DT(employee_hiredate);
					SqlString.Append(quo);
					SqlString.Append(Record.HireDate);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.YearsOfExperience);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.Title);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.Age);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.FirstName);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.LastName);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.Gender);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.MobileNumber);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.Email);
					SqlString.Append(quo);
					SqlString.Append(out);



					//COleDateTime dt(emp_datebirth);
					SqlString.Append(quo);
					SqlString.Append(Record.DateOfBirth);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.Address);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.JobTitle);
					SqlString.Append(quo);
					SqlString.Append(out);

					SqlString.Append(quo);
					SqlString.Append(Record.Salary);
					SqlString.Append(quo);

					SqlString.Append(_T(" )"));

					EmployeeRecords.push_back(Record);
					database.ExecuteSQL(SqlString);
				}
				database.Close();
				}CATCH(CDBException, e) {

					AfxMessageBox(L"Database error: " + e->m_strError);
				}
				END_CATCH;
			}
			UpdateWindow();
			MessageBox(L"Successfully Insert Xml File...!");
		}
	}

}

int CAdminAppDlg::cntLeapYears(E_DATE d) {
	int years = d.y;

	if (d.m <= 2)
		years--;

	return years / 4
		- years / 100
		+ years / 400;
	return 0;
}
/*
CString CAdminAppDlg::remove_spaces(CString s)
{
	s.TrimRight();
	s.TrimLeft();
	return s;

}
bool CAdminAppDlg::isvalidxml(vector<CString>& v)
{
	stack<CString> s;
	for (unsigned int i = 0; i < v.size(); i++) {
		if (isstarttag(v[i])) {
			s.push(stagname(v[i]));
			//MessageBox(stagname(v[i]));
		}
		else if (isendtag(v[i])) {
			CString temp = s.top();
			if ((ismatchingtagname(temp, etagname(v[i])))) {
				s.pop();
			}
			//MessageBox(etagname(v[i]));
		}
	}
	return s.empty();
}
bool CAdminAppDlg::isstarttag(CString s)
{
	int n = s.GetLength();
	for (int i = 0; i < s.GetLength(); i++) {
		if (s[0] != '<') {
			return false;
		}
		if (s[1] == '/') {
			return false;
		}
		if (s[n - 1] != '>') {
			return false;
		}
	}
	return true;

}
bool CAdminAppDlg::isendtag(CString s)
{
	int l = s.GetLength();
	if (l <= 2)
		return false;
	if (s[0] != '<')
		return false;
	if (s[1] != '/')
		return false;
	if (s[l - 1] != '>')
		return false;
	return true;
}
CString CAdminAppDlg::stagname(CString s)
{
	CString temp;
	temp.Empty();
	for (int i = 1; i < s.GetLength() - 1; i++) {
		temp.AppendChar(s[i]);
	}
	return temp;
}
CString CAdminAppDlg::etagname(CString s)
{
	CString temp;
	temp.Empty();
	for (int i = 2; i < s.GetLength() - 1; i++) {
		temp.AppendChar(s[i]);
	}
	return temp;
}
bool CAdminAppDlg::ismatchingtagname(CString s, CString d)
{
	if (s.GetLength() >= d.GetLength()) {
		for (int i = 0; i < d.GetLength(); i++) {
			if (s[i] != d[i]) {
				return false;
			}
		}
	}
	else {
		return false;
	}
	return true;
}
vector<CString> CAdminAppDlg::split_entire_file_string_to_vector_of_small_elements(CString s)
{
	CString temp;
	CString hold;
	temp.Empty();
	hold.Empty();
	hold = s;
	vector<CString> v;
	for (int i = 0; i < hold.GetLength(); i++) {
		if (hold[i] == '<') {
			if (temp.IsEmpty()) {
				temp.AppendChar(hold[i]);
			}
			else {
				v.push_back(temp);
				temp.Empty();
				temp.AppendChar(hold[i]);
			}
		}
		else if (hold[i] != '>') {
			temp.AppendChar(hold[i]);
		}
		else if ((hold[i] == '>') && (temp[0] == '<')) {
			temp.AppendChar(hold[i]);
			v.push_back(temp);
			temp.Empty();
		}
		else if ((hold[i] == '>') && (temp[0] != '<')) {
			v.push_back(temp);
			temp.Empty();
		}
	}
	hold.Empty();

	return v;
}*/
bool CAdminAppDlg::compare_twostrings(CString p, CString q)
{
	if (p.GetLength() != q.GetLength())
		return false;
	for (int i = 0; i < p.GetLength(); i++) {
		if (p[i] != q[i]) {
			return false;
		}
	}
	return true;
}

Employee CAdminAppDlg::GetRecord(int Row)
{
	Employee Record;
	Record.Id = emp_list.GetItemText(Row, 0);
	Record.HireDate = emp_list.GetItemText(Row, 1);
	Record.YearsOfExperience = emp_list.GetItemText(Row, 2);
	Record.Title = emp_list.GetItemText(Row, 3);
	Record.Age = emp_list.GetItemText(Row, 4);
	Record.FirstName = emp_list.GetItemText(Row, 5);
	Record.LastName = emp_list.GetItemText(Row, 6);
	Record.Gender = emp_list.GetItemText(Row, 7);
	Record.MobileNumber = emp_list.GetItemText(Row, 8);
	Record.Email = emp_list.GetItemText(Row, 9);
	Record.DateOfBirth = emp_list.GetItemText(Row, 10);
	Record.Address = emp_list.GetItemText(Row, 11);
	Record.JobTitle = emp_list.GetItemText(Row, 12);
	Record.Salary = emp_list.GetItemText(Row, 13);
	return Record;
}

int CAdminAppDlg::getDiff(E_DATE dt1, E_DATE dt2) {
	long int n1 = dt1.y * 365 + dt1.d;

	for (int i = 0; i < dt1.m - 1; i++)
		n1 += mdays[i];

	n1 += cntLeapYears(dt1);

	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += mdays[i];
	n2 += cntLeapYears(dt2);

	return (n2 - n1);
	return 0;
}

void CAdminAppDlg::OnBnClickedButtonImportFile()
{

}
