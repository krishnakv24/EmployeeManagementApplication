#include "stdafx.h"
#include "EDataDisplay.h"
#include "uiProgressBarDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CuiProgressBarDlg, CDialogEx)

CuiProgressBarDlg::CuiProgressBarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EDATA_PROGRESS_BAR, pParent)
{	
}

CuiProgressBarDlg::~CuiProgressBarDlg()
{
}

void CuiProgressBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PROGRESS, m_stProgressBar);
}


BEGIN_MESSAGE_MAP(CuiProgressBarDlg, CDialogEx)
	
END_MESSAGE_MAP()

BOOL CuiProgressBarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBackgroundColor(RGB(1, 11, 21));
	LONG ExtendedStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, ExtendedStyle | WS_EX_LAYERED);
	::SetLayeredWindowAttributes(GetSafeHwnd(), RGB(1, 11, 21), 0, LWA_COLORKEY);

	m_stProgressBar.SetInfiniteProgressInterval(50);
	m_stProgressBar.SetInfiniteProgressArcOffsetIncrement(10);
	m_stProgressBar.SetInfiniteProgress(true);

	m_stProgressBar.SetCircleThickness(12);
	m_stProgressBar.SetProgCircleColor(RGB(107, 125, 189));

	m_stProgressBar.SetFontSize(16);
	m_stProgressBar.SetFontColor(RGB(0, 0, 139));
	m_stProgressBar.SetDisplayText(L"Starting up.Please wait.");

	m_stProgressBar.StartInfiniteProgress();
	return TRUE;
}

void CuiProgressBarDlg::OnOK()
{
}


void CuiProgressBarDlg::OnCancel()
{
}

void CuiProgressBarDlg::StopInfiniteProgress()
{
	m_stProgressBar.StopInfiniteProgress();
}

