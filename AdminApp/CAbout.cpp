// CAbout.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "CAbout.h"
#include "afxdialogex.h"


// CAbout dialog

IMPLEMENT_DYNAMIC(CAbout, CDialogEx)

CAbout::CAbout(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ABOUT_ADMINAPP, pParent)
{

}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAbout, CDialogEx)
END_MESSAGE_MAP()


// CAbout message handlers
