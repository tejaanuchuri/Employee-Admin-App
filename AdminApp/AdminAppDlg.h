
// AdminAppDlg.h : header file
//
struct E_DATE {
	int d, m, y;
};

const int mdays[12]
= { 31, 28, 31, 30, 31, 30,
   31, 31, 30, 31, 30, 31 };

#pragma once
#include "external/GraphCtrl.h"

#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartLabel.h"

#include <fstream>
#include <vector>
#include <stdlib.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <stack>
using namespace std;

#define open_tag_symbol _T("<")
#define close_tag_symbol _T(">")
#define close_tag_symbol_with_nextline _T(">\n")
#define open_end_tag_symbol _T("</")
// CAdminAppDlg dialog
class CAdminAppDlg : public CDialogEx
{
	// Construction
public:
	CAdminAppDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
	CGraphCtrl m_Graph;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINAPP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:

	void m_ResetListControl();
	void ResetListControl();
	void s_ResetListControl();
	void display_all_employee_records_in_the_listview_representation();
	void display_all_employee_records_in_the_bargraph_representation();
	void delete_all_employee_records_in_the_bargraph();
	void display_all_employee_records_in_the_linegraph();
	void delete_all_employee_records_in_the_linegraph();
	void displayallrecords();
	CString Add_elem(CString s, CString v);
	CString Start_Tag(CString s);
	CString End_Tag(CString s);
	CString root_start_tag(CString s);
	CString root_end_tag(CString s);
	int getDiff(E_DATE dt1, E_DATE dt2);
	int cntLeapYears(E_DATE dt1);
	CString remove_spaces(CString s);
	bool isvalidxml(vector<CString>& v);
	bool isstarttag(CString s);
	bool isendtag(CString s);
	CString stagname(CString s);
	CString etagname(CString s);
	bool ismatchingtagname(CString s, CString d);
	vector<CString> split_entire_file_string_to_vector_of_small_elements(CString s);

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl emp_list;
	int row;
	int m_iYScale;
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnFileClose();
	afx_msg void OnAboutAdminapp();

	afx_msg void OnBnClickedButtonDeleteAllBars();
	afx_msg void OnBnClickedButtonSelectgraph();
	afx_msg void OnBnClickedButtonLoadbragraph();
	CChartCtrl m_ChartCtrl;
	CChartStandardAxis* pBottomAxis;
	CChartStandardAxis* pLeftAxis;
	CChartLineSerie* pSeries;


	afx_msg void OnBnClickedRadioBargraph();
	afx_msg void OnBnClickedRadioLineGraphRepresentation();
	CButton m_bar_graph_control;
	CButton m_line_graph_control;
	CString S_choose_filed;
	CString S_choose_filed_value;
	CComboBox CChooseType;
	CEdit CChoosetypevalue;
	vector< vector<pair<CString, CString>>> employee_records;
	vector<vector<CString>> employeerecords;

	afx_msg void OnOperationsExport();
	afx_msg void OnOperationsImport();
	afx_msg void OnBnClickedButtonImportFile();
};