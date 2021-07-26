// MyStatic.cpp : implementation file
//

#include "afxwin.h"
#include "MyStatic.h"
#include ".\mystatic.h"


// CMyStatic

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)
CMyStatic::CMyStatic()
{
	stColor = RGB(0, 0, 0);
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyStatic message handlers


void CMyStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
	RECT rc;
	GetClientRect(&rc);
	dc.FillSolidRect(&rc, stColor);
}
