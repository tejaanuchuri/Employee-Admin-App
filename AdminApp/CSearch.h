#pragma once


// CSearch dialog

class CSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CSearch)

public:
	CSearch(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSearch();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH };
#endif

protected:
	void ResetListControl();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString s_choose_field;
	CString s_entervalue;
	afx_msg void OnBnClickedButtonSearch();
	CListCtrl m_Search_list;
};
