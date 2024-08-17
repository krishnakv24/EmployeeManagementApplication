#include "stdafx.h"
#include "uiDialogEx.h"

CuiDialogEx::CuiDialogEx()
{
}

CuiDialogEx::CuiDialogEx(UINT nIDTemplate, CWnd* pParent): CDialogEx(nIDTemplate, pParent) 
{
	
}
CuiDialogEx::~CuiDialogEx()
{
}

BEGIN_MESSAGE_MAP(CuiDialogEx, CDialogEx)
	ON_WM_PAINT()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDOK, &CuiDialogEx::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CuiDialogEx::OnBnClickedCancel)

END_MESSAGE_MAP()

void CuiDialogEx::OnPaint()
{
	CPaintDC dc(this);
	CRect rct;
	GetClientRect(&rct);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rct.Width(), rct.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	CBrush brsh(RGB(245, 245, 255));
	memDC.FillRect(rct, &brsh);

	dc.BitBlt(0, 0, rct.Width(), rct.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
}

void CuiDialogEx::OnBnClickedOk()
{
}

void CuiDialogEx::OnBnClickedCancel()
{
}

