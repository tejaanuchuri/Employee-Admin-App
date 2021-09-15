// GraphCtrl.cpp : implementation file
//

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>
#include "GraphCtrl.h"
#include ".\graphctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl

CGraphCtrl::CGraphCtrl()
{
	offsetx = 50;
	offsety = 40;
	strcpy_s(sUnit, "cm");
	scale = 5;
	iStart = 0;
	iEnd = 80;
	BGC = RGB(224, 231, 240);
	AxisC = RGB(0, 0, 0);
	TextC = RGB(0, 0, 0);
}

CGraphCtrl::~CGraphCtrl()
{

}

BEGIN_MESSAGE_MAP(CGraphCtrl, CStatic)
	//{{AFX_MSG_MAP(CGraphCtrl)
	ON_WM_DRAWITEM()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	//ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl message handlers

BOOL CGraphCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class

	return CStatic::OnNotify(wParam, lParam, pResult);
}

BOOL CGraphCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

LRESULT CGraphCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

	return CStatic::WindowProc(message, wParam, lParam);
}

void CGraphCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CStatic::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CGraphCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	DrawGraph();

	// Do not call CStatic::OnPaint() for painting messages
}

void CGraphCtrl::OnTimer(UINT nIDEvent)
{

	CStatic::OnTimer(nIDEvent);
}

int CGraphCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here

	return 0;
}

void CGraphCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW lpcd = (LPNMCUSTOMDRAW)pNMHDR;
	CDC* pDC = CDC::FromHandle(lpcd->hdc);
	switch (lpcd->dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
		//return;
	case CDDS_ITEMPREPAINT:
		if (lpcd->dwItemSpec == TBCD_THUMB)
		{
			*pResult = CDRF_DODEFAULT;
			break;
		}
		break;
	}
}

int CGraphCtrl::AddBar(int iVal, COLORREF bClr, const char* sLabel)
{
	BAR_DATA cBar;
	cBar.iVal = iVal;
	cBar.barClr = bClr;
	strncpy_s(cBar.sLabel, sLabel, 15);

	POSITION pos = listBars.AddTail(cBar);

	return listBars.GetCount();
}

int CGraphCtrl::InsertBar(int index, int iVal, COLORREF bClr, const char* sLabel)
{
	if (index < 0 || index >= listBars.GetCount())
		return -1;

	BAR_DATA cBar;
	cBar.iVal = iVal;
	cBar.barClr = bClr;
	strncpy_s(cBar.sLabel, sLabel, 15);

	listBars.InsertAfter(listBars.FindIndex(index), cBar);

	return listBars.GetCount();
}

int CGraphCtrl::DeleteBar(int index)
{
	if (index < 0 || index >= listBars.GetCount())
		return -1;
	listBars.RemoveAt(listBars.FindIndex(index));

	return listBars.GetCount();
}

int CGraphCtrl::GetNumberOfBars()
{
	return listBars.GetCount();
}

void CGraphCtrl::SetBarValue(int index, int val, BOOL bDraw)
{
	if (index < 0 || index >= listBars.GetCount())
		return;

	BAR_DATA cBar = listBars.GetAt(listBars.FindIndex(index));
	cBar.iVal = val;
	listBars.SetAt(listBars.FindIndex(index), cBar);

	if (bDraw)
		DrawGraph();
}

void CGraphCtrl::SetBarColor(int index, COLORREF Clr, BOOL bDraw)
{
	if (index < 0 || index >= listBars.GetCount())
		return;

	BAR_DATA cBar = listBars.GetAt(listBars.FindIndex(index));
	cBar.barClr = Clr;
	listBars.SetAt(listBars.FindIndex(index), cBar);

	if (bDraw)
		DrawGraph();
}

int CGraphCtrl::GetBarValue(int index)
{
	if (index < 0 || index >= listBars.GetCount())
		return -1;

	BAR_DATA cBar = listBars.GetAt(listBars.FindIndex(index));

	return cBar.iVal;
}

COLORREF CGraphCtrl::GetBarColor(int index)
{
	if (index < 0 || index >= listBars.GetCount())
		return -1;

	BAR_DATA cBar = listBars.GetAt(listBars.FindIndex(index));

	return cBar.barClr;
}

void CGraphCtrl::SetUnit(CString pUnit)
{
	strcpy_s(sUnit, (LPCSTR)(CStringA)pUnit);

	DrawGraph();
}

void CGraphCtrl::SetScale(int iScl)
{
	if (iScl <= 0)
		return;

	scale = iScl;

	DrawGraph();
}

int CGraphCtrl::GetScale()
{
	return scale;
}

COLORREF CGraphCtrl::GetBGColor()
{
	return BGC;
}

void CGraphCtrl::SetBGColor(COLORREF pBG)
{
	BGC = pBG;

	DrawGraph();
}

void CGraphCtrl::SetAxisColor(COLORREF pAxC)
{
	AxisC = pAxC;
	DrawGraph();
}

COLORREF CGraphCtrl::GetAxisColor()
{
	return AxisC;
}

void CGraphCtrl::SetTextColor(COLORREF pTxC)
{
	TextC = pTxC;
	DrawGraph();
}

COLORREF CGraphCtrl::GetTextColor()
{
	return TextC;
}

BOOL CGraphCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class

	return CStatic::PreCreateWindow(cs);
}

int CGraphCtrl::DrawGraph(void)
{
	CDC MemDC;
	CBitmap MemBitmap;
	LOGFONT lf;
	CString str;
	CFont newFont, newFont1;

	CRect rc;
	GetClientRect(rc);
	int Width = rc.Width();
	int Height = rc.Height();

	CDC* pDC = GetDC();
	MemDC.CreateCompatibleDC(pDC);
	MemBitmap.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	CBitmap* pOldBitmap = MemDC.SelectObject(&MemBitmap);

	CFont* pFont = MemDC.GetCurrentFont();
	pFont->GetLogFont(&lf);
	lf.lfHeight = (-1) * MulDiv(9, MemDC.GetDeviceCaps(LOGPIXELSY), 72);

	memset(&lf, 0, sizeof(lf));
	lstrcpy(lf.lfFaceName, L"Arial");
	lf.lfHeight = (-1) * MulDiv(9, MemDC.GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfWeight = 700;
	newFont.CreateFontIndirect(&lf);
	lf.lfEscapement = 900;
	newFont1.CreateFontIndirect(&lf);

	MemDC.SelectObject(&newFont1);

	int bx = 0, by = 0;
	MemDC.FillSolidRect(0, 0, Width, Height, BGC);

	MemDC.FillSolidRect(offsetx - 2, 0, 2, Height - (offsety - 2), AxisC);
	MemDC.FillSolidRect(offsetx, Height - offsety, Width - offsetx, 2, AxisC);

	MemDC.SetBkMode(TRANSPARENT);
	MemDC.SetTextColor(TextC);

	int iActHt = (Height - offsety);
	int iDiv = (iActHt - 5) / ((iEnd - iStart) / scale);

	str = _T("Years Of Experience =>");
	MemDC.ExtTextOut(0, iActHt - 20, 0, NULL, str, NULL);

	MemDC.SelectObject(&newFont);

	int iIdx = 0;
	for (int i = offsety; i <= iActHt + offsety + 5; i += (iDiv / 2))
	{
		if (iIdx % 2)
		{
			MemDC.FillSolidRect(offsetx - 6, Height - i, 4, 1, AxisC);
		}
		else
		{
			MemDC.FillSolidRect(offsetx - 10, Height - i, 8, 1, AxisC);
			//str.Empty();
			//str.Append(_T("%d", (iStart + ((iIdx / 2) * scale))));
			str.Format(L"%d", iStart + (iIdx / 2) * scale);
			MemDC.ExtTextOut(17, Height - i - 8, 0, NULL, str, NULL);
		}
		iIdx++;
	}

	int NumOfBars = listBars.GetCount();
	int i;
	for (i = 0; i < NumOfBars; i++)
	{
		BAR_DATA cBar = listBars.GetAt(listBars.FindIndex(i));
		float val_p = ((float)(cBar.iVal - iStart) / (float)scale) * (float)iDiv;
		int pixVal = (int)val_p;
		bx = ((Width - offsetx) / NumOfBars) * i + offsetx;
		if (pixVal > 0)
		{
			MemDC.FillSolidRect(bx, iActHt - pixVal, (Width - offsety) / NumOfBars, pixVal, cBar.barClr);
			MemDC.Draw3dRect(bx, iActHt - pixVal, (Width - offsety) / NumOfBars, pixVal, RGB(255, 255, 255), cBar.barClr);
		}

		str = cBar.sLabel;
		MemDC.ExtTextOut(bx, iActHt + 2, 0, NULL, str, NULL);
	}

	//Draw
	pDC->BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);

	return 0;
}

int CGraphCtrl::SetDisplayRange(int iRangeStart, int iRangeEnd)
{
	if (iRangeStart >= 0 && iRangeEnd >= 0)
	{
		iStart = iRangeStart;
		iEnd = iRangeEnd;
	}

	DrawGraph();
	return 1;
}

void CGraphCtrl::GetDisplayRange(int& iRangeStart, int& iRangeEnd)
{
	iRangeStart = iStart;
	iRangeEnd = iEnd;
}
