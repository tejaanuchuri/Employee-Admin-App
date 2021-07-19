
// AdminAppDlg.h : header file
//

#pragma once


// CAdminAppDlg dialog
class CAdminAppDlg : public CDialogEx
{
	// Construction
public:
	CAdminAppDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
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
	CButton c_insert;
	int v_insert;
	CButton c_update;
	int v_update;
	CButton c_search;
	int v_search;
	CButton c_delete;
	int v_delete;
	afx_msg void OnBnClickedRadioInsert();
	afx_msg void OnBnClickedRadioUpdate();
	afx_msg void OnBnClickedRadioSearch();
	afx_msg void OnBnClickedRadioDelete();
	afx_msg void OnBnClickedButtonSubmit();
	afx_msg void OnBnClickedButtonInsert();
};
