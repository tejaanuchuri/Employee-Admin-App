
// AdminAppDlg.h : header file
//

#pragma once
#include "external/GraphCtrl.h"

#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartLabel.h"

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
	void emp_data_load();
	void bargraph_loaded();
	void bargraph_update();
	void bargraph_empty();
	void linegraph_loaded();
	void linegraph_update();
	void linegraph_empty();

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
};
