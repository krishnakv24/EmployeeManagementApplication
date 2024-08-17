#include "stdafx.h"
#include "uiHeaderCtrl.h"

CuiHeaderCtrl::CuiHeaderCtrl()
	: m_headerBgColor(RGB(200, 200, 200)),
	m_headerTextColor(RGB(0, 0, 0))
{
}

CuiHeaderCtrl::~CuiHeaderCtrl()
{
}

void CuiHeaderCtrl::SetHeaderColors(COLORREF bgColor, COLORREF textColor)
{
	m_headerBgColor = bgColor;
	m_headerTextColor = textColor;
	Invalidate();
}

BEGIN_MESSAGE_MAP(CuiHeaderCtrl, CHeaderCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CuiHeaderCtrl::OnCustomDraw)
END_MESSAGE_MAP()

void CuiHeaderCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (pNMCD->dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (pNMCD->dwDrawStage == CDDS_ITEMPREPAINT)
	{
		CDC* pDC = CDC::FromHandle(pNMCD->hdc);

		HDITEM hdi;
		TCHAR szText[256];
		hdi.mask = HDI_TEXT | HDI_FORMAT;
		hdi.pszText = szText;
		hdi.cchTextMax = sizeof(szText) / sizeof(TCHAR);
		GetItem((int)pNMCD->dwItemSpec, &hdi);

		CRect rect(pNMCD->rc);

		pDC->FillSolidRect(&rect, m_headerBgColor);

		pDC->SetTextColor(m_headerTextColor);
		pDC->SetBkMode(TRANSPARENT);

		CFont font;
		font.CreateFont(
			18,
			0,
			0,
			0,
			FW_BOLD,
			FALSE,
			FALSE,
			0,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			_T("Arial"));

		CFont* pOldFont = pDC->SelectObject(&font);

		UINT format = DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX;

		if (hdi.fmt & HDF_CENTER)
			format |= DT_CENTER;
		else if (hdi.fmt & HDF_RIGHT)
			format |= DT_RIGHT;
		else
			format |= DT_LEFT;

		pDC->DrawText(szText, &rect, format);

		pDC->SelectObject(pOldFont);
		font.DeleteObject();

		*pResult = CDRF_SKIPDEFAULT;
	}
	else
	{
		*pResult = CDRF_DODEFAULT;
	}
}
