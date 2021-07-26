#if !defined(AFX_GRAPHCTRL_H__8D088C76_20F1_4F89_8527_C3B30E6F763D__INCLUDED_)
#define AFX_GRAPHCTRL_H__8D088C76_20F1_4F89_8527_C3B30E6F763D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphCtrl.h : header file
//

#include <Afxtempl.h>

struct BAR_DATA
{
	int iVal;
	COLORREF barClr;
	char sLabel[16];
};

/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl window

class CGraphCtrl : public CStatic
{
// Construction
public:
	CGraphCtrl();

// Attributes
public:
	CList<BAR_DATA, BAR_DATA> listBars;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphCtrl)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetUnit(CString pUnit);
	void SetScale(int);
	int GetScale();
	char sUnit[16];
	int scale;
	int offsetx;
	int offsety;

	int iStart, iEnd;

	int AddBar(int iVal, COLORREF bClr, const char* sLabel);
	int InsertBar(int index,int iVal, COLORREF bClr, const char* sLabel);
	int DeleteBar(int index);

	void SetBarValue(int, int, BOOL bDraw=TRUE);
	void SetBarColor(int, COLORREF, BOOL bDraw=TRUE);

	int GetBarValue(int);
	COLORREF GetBarColor(int);

	COLORREF BGC;
	void SetBGColor(COLORREF);
	COLORREF GetBGColor();

	COLORREF AxisC;
	void SetAxisColor(COLORREF);
	COLORREF GetAxisColor();

	COLORREF TextC;
	void SetTextColor(COLORREF);
	COLORREF GetTextColor();

	int GetNumberOfBars();
	virtual ~CGraphCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphCtrl)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	int DrawGraph(void);
	int SetDisplayRange(int iRangeStart, int iRangeEnd);
	void GetDisplayRange(int& iRangeStart, int& iRangeEnd);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHCTRL_H__8D088C76_20F1_4F89_8527_C3B30E6F763D__INCLUDED_)
