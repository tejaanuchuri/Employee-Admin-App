#pragma once


// CSelectedFiles dialog

#include <fstream>
#include <vector>
#include <stdlib.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <stack>
using namespace std;
class CSelectedFiles : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectedFiles)

public:
	CSelectedFiles(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSelectedFiles();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELECT_FILES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_select_list;
	vector<vector<pair<CString, CString>>> emps;
	vector<CString> v;
	vector<vector<CString>> u;
	vector<int> emp_index;
	afx_msg void OnBnClickedButtonImportFile();
};
