
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
#include "xml_library/Markup.h"
#include "CSelectedFiles.h"

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
	emp_data_load();
	bargraph_loaded();
	linegraph_empty();
	linegraph_loaded();

	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_HIDE);
	m_line_graph_control.SetState(true);
	m_line_graph_control.SetCheck(1);

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
	/*UpdateData(FALSE); // flow direction database -> ui

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

	UpdateData(FALSE);*/
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
		//pSeries->SetShadowColor(RGB(50, 50, 50));
		//pSeries->SetShadowDepth(5);
		//pSeries->EnableShadow(true);
		m_ChartCtrl.EnableRefresh(true);
	}


	return;
}

void CAdminAppDlg::linegraph_update()
{

}

void CAdminAppDlg::linegraph_empty()
{
	m_ChartCtrl.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);
}

CString CAdminAppDlg::Add_elem(CString s, CString v)
{
	return Start_Tag(s) + v + End_Tag(s);
}

CString CAdminAppDlg::Start_Tag(CString s)
{
	return sls + s + srs;
}

CString CAdminAppDlg::End_Tag(CString s)
{
	return els + s + srsn;
}

CString CAdminAppDlg::root_start_tag(CString s)
{
	return sls + s + srsn;
}

CString CAdminAppDlg::root_end_tag(CString s)
{
	return els + s + srsn;
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
		CString e_age = dlg.emp_age;
		CString e_title = dlg.emp_title;
		CString e_firstname = dlg.emp_firstname;
		CString e_lastname = dlg.emp_lastname;
		CString e_gender = dlg.emp_gender;
		CString e_phonenumber = dlg.emp_phonenumber;
		CString e_email = dlg.emp_email;
		CString e_birthdate = dlg.emp_datebirth.Format(_T("%Y-%m-%d"));
		CString e_address = dlg.emp_address;
		CString e_jobtitle = dlg.emp_jobtitle;
		CString e_salary = dlg.emp_salary;
		CString e_hiredate = dlg.employee_hiredate.Format(_T("%Y-%m-%d"));
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


		/*CDatabase database;
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
		END_CATCH;*/
		ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
		int row = emp_list.GetItemCount();
		row = row + 1;

		emp_list.SetItemText(row, 0, e_id);
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


		date.ParseDateTime(e_hiredate);
		int year = date.GetYear();
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


		/*linegraph_empty();
		linegraph_loaded();*/
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
			emp_list.SetItemText(row, 10, u.u_dateofbirthdate.Format(_T("%Y-%m-%d")));
			emp_list.SetItemText(row, 1, u.u_hiredate.Format(_T("%Y-%m-%d")));
			emp_list.SetItemText(row, 2, emp_yrsofexp);

			emp_list.UpdateWindow();
			MessageBox(L"Update Record Sucessfully...!");


			m_Graph.SetBarValue(m_Graph.GetNumberOfBars() - row - 1, _wtoi(emp_yrsofexp), TRUE);
			m_Graph.DrawGraph();


			linegraph_empty();
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
			//SqlString = L"SELECT * FROM EmployeeTable";
			emp_data_load();

			CChooseType.SetWindowText(_T(""));
			CChoosetypevalue.SetWindowText(_T(""));
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


			recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
			ResetListControl();
			ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
			emp_list.InsertColumn(0,L"EmpID",LVCFMT_LEFT,42);
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

				recset.GetFieldValue(L"EmpID", e_id);
				recset.GetFieldValue(L"Title", e_title);
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

				recset.MoveNext();
			}
		}
		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;
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

		CString id = emp_list.GetItemText(row, 0);
		emp_list.DeleteItem(row);
		UpdateWindow();
		m_Graph.DeleteBar(m_Graph.GetNumberOfBars() - row - 1);
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


		linegraph_empty();
		linegraph_loaded();
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


void CAdminAppDlg::OnOperationsExport()
{

	POSITION pos = emp_list.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		AfxMessageBox(L"No row Selected");
	}
	else {

		POSITION pos = emp_list.GetFirstSelectedItemPosition();

		CStdioFile file;
		file.Open(L"Emp.xml", CStdioFile::modeCreate | CStdioFile::modeWrite);

		file.WriteString(root_start_tag(L"AdminApp"));
		if (pos != NULL) {
			while (pos)
			{
				int row = emp_list.GetNextSelectedItem(pos);
				CString id = emp_list.GetItemText(row, 0);
				int e_id = _wtoi(id);
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
				CString emp_date_birth = emp_datebirth.Format(_T("%d-%m-%Y"));

				COleDateTime employee_hiredate;
				employee_hiredate.ParseDateTime(emp_list.GetItemText(row, 1));
				CString Hiredate = employee_hiredate.Format(_T("%d-%m-%Y"));
				CString emp_yrsofexp = emp_list.GetItemText(row, 2);

				file.WriteString(root_start_tag(L"Employee"));
				file.WriteString(Add_elem(_T("id"), id));
				file.WriteString(Add_elem(_T("HireDate"), Hiredate));
				file.WriteString(Add_elem(_T("YearsofExperience"), emp_yrsofexp));
				file.WriteString(Add_elem(_T("Title"), emp_title));
				file.WriteString(Add_elem(_T("Age"), emp_age));
				file.WriteString(Add_elem(_T("FirstName"), emp_firstname));
				file.WriteString(Add_elem(_T("LastName"), emp_lastname));
				file.WriteString(Add_elem(_T("Gender"), emp_gender));
				file.WriteString(Add_elem(_T("PhoneNumber"), emp_phonenumber));
				file.WriteString(Add_elem(_T("Email"), emp_email));
				file.WriteString(Add_elem(_T("Address"), emp_address));
				file.WriteString(Add_elem(_T("JobTitle"), emp_jobtitle));
				file.WriteString(Add_elem(_T("Salary"), emp_salary));
				file.WriteString(Add_elem(_T("DateofBirth"), emp_date_birth));
				file.WriteString(root_end_tag(L"Employee"));

			}
		}
		file.WriteString(root_end_tag(L"AdminApp"));
		file.Close();
		MessageBox(L"Xml Files Generate Sucessfully...!");
	}

	return;
}


void CAdminAppDlg::OnOperationsImport()
{
	CString sFilter = _T("Xml Files (*.xml)|*.xml");

	CFileDialog dlg(TRUE, _T("*.xml"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, sFilter, this);

	vector<vector< vector<pair<CString, CString>>>> employeesfiles;
	employeesfiles.clear();
	int check = 0;
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos(dlg.GetStartPosition());
		while (pos)
		{
			CString fullPathName = dlg.GetNextPathName(pos);
			CStdioFile file;

			file.Open(fullPathName, CStdioFile::modeRead | CStdioFile::typeText);

			CString sl;
			CString chReadString;
			vector<CString> v;
			vector<CString> out;
			v.clear();
			sl.Empty();
			out.clear();
			chReadString.Empty();
			int flag = 1;
			while (file.ReadString(sl))
			{
				sl.TrimLeft();
				sl.TrimRight();
				chReadString += sl;
			}

			file.Close();
			CString temp;
			CString hold;
			temp.Empty();
			hold.Empty();
			hold = chReadString;
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
			flag = 0;
			for (vector<CString>::iterator i = v.begin(); i != v.end(); i++) {
				*i = remove_spaces(*i);
				CString t = *i;

				for (int j = 0; j < t.GetLength(); j++) {
					if (t[j] != ' ') {
						flag = 1;
					}
				}
				if (flag == 1) {
					out.push_back(t);
					flag = 0;
				}
				//MessageBox(t);
				//CString x;
				//x.Format(_T(" = %d"), t.GetLength());
				//t = t + x;
				//MessageBox(t);
			}
			v.clear();
			for (vector<CString>::iterator k = out.begin(); k != out.end(); k++) {
				*k = remove_spaces(*k);
				CString t = *k;
				/*for (unsigned int j = 0; j < t.GetLength(); j++) {
					if (t[j] != ' ') {
						flag = 1;
					}
				}
				if (flag == 0) {
					v.erase(k);
				}*/
				//MessageBox(t);
				CString x;

				x.Format(_T(" = %d"), t.GetLength());
				t = t + x;
				//MessageBox(t);
			}
			if (!isvalidxml(out)) {
				MessageBox(L"It Is Not valid xml file");
			}
			else {
				check = 1;
				vector<pair<CString, CString>> res;
				vector< vector<pair<CString, CString>>> emp;
				stack<CString> s;
				CString temp_value;
				temp.Empty();
				temp_value.Empty();
				for (unsigned int i = 0; i < out.size(); i++) {
					if (isstarttag(out[i])) {
						s.push(stagname(out[i]));
					}
					else if (isendtag(out[i])) {
						temp = s.top();
						if ((ismatchingtagname(temp, etagname(out[i]))) && !(temp_value.IsEmpty())) {
							res.push_back(make_pair(etagname(out[i]), temp_value));
							temp.Empty();
							temp_value.Empty();
							s.pop();
						}
						else if (temp == etagname(out[i])) {
							emp.push_back(res);
							res.clear();
						}
					}
					else {
						temp_value.Append(out[i]);
					}
				}
				employee_records = emp;
				employeesfiles.push_back(emp);

				/*UpdateData(FALSE); // flow direction database -> ui

				int iRec = 0;
				//m_ResetListControl();
				ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
				//for (int i = 0; i < emp[0].size(); i++) {
				//	emp_list.InsertColumn(i, emp[0][i].first, LVCFMT_CENTER, 120);
				//}

				for (unsigned int i = 0; i < emp.size(); i++) {
					vector<pair<CString, CString>> record = emp[i];
					for (unsigned int j = 0; j < record.size(); j++) {
						if (j == 0) {
							iRec = emp_list.InsertItem(0, record[j].second, 0);
						}
						else {
							emp_list.SetItemText(0, j, record[j].second);
						}
					}
					record.clear();
				}*/

				/*CDatabase database;
				CString sDsn;
				CString SqlString;

				// Build ODBC connection string
				sDsn.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
				TRY{
					// Open the database
					database.Open(NULL,false,false,sDsn);
				//MessageBoxW(L"Are You Sure ?", L"Insert a Record",MB_YESNO);

				CString out = L" ,";
				CString quo = L"'";
				SqlString.Append(_T("INSERT INTO EmployeeTable(EmpID,Title,Age,FirstName,LastName,Gender,MobilePhone,EMail,BirthDate,Address,JobTitle,Salary,Hiredate,YearsOfExp) VALUES ("));
				SqlString.Append(quo);
				SqlString.Append(id);
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(title);
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(Age);
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(First_Name);
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(Last_Name);
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(Gender);
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(Phonenumber);
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(Email);
				SqlString.Append(quo);
				SqlString.Append(out);

				COleDateTime dt(emp_dob);
				SqlString.Append(quo);
				SqlString.Append(emp_dob.Format(_T("%Y-%m-%d")));
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(Address);
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(Job_title);
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(salary);
				SqlString.Append(quo);
				SqlString.Append(out);

				COleDateTime DT(employee_hiredate);
				SqlString.Append(quo);
				SqlString.Append(employee_hiredate.Format(_T("%Y-%m-%d")));
				SqlString.Append(quo);
				SqlString.Append(out);

				SqlString.Append(quo);
				SqlString.Append(yrsofexp);
				SqlString.Append(quo);

				SqlString.Append(_T(" )"));

				//AfxMessageBox(SqlString);
				database.ExecuteSQL(SqlString);
				//MessageBox(L"Insert Record sucessfully...!");
				// Close the database
				database.Close();
				}CATCH(CDBException, e) {
					// If a database exception occured, show error msg
					AfxMessageBox(L"Database error: " + e->m_strError);
				}
				END_CATCH;*/

				//do something with the filename variable
			}

		}
		if (check == 1) {

			//dlg.m_select_list.UpdateWindow();
			CSelectedFiles dlg;
			dlg.emps = employee_records;
			if (dlg.DoModal() == IDOK) {
				UpdateData(FALSE);
				int iRec = 0;
				ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
				for (unsigned int i = 0; i < dlg.emp_index.size(); i++) {
					vector<pair<CString, CString>> record = employee_records[dlg.emp_index[i]];
					for (unsigned int j = 0; j < record.size(); j++) {
						if (j == 0) {
							iRec = emp_list.InsertItem(0, record[j].second, 0);
						}
						else {
							emp_list.SetItemText(0, j, record[j].second);
						}
					}
					record.clear();
				}
				emp_list.UpdateWindow();
			}
			UpdateWindow();
		}

		//MessageBox(L"Successfully Insert Xml File...!");

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
