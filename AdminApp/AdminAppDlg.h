
// AdminAppDlg.h : header file
//

#pragma once
#include "external/GraphCtrl.h"


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
	void emp_data_load();



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

};
