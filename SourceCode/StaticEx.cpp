#include "StdAfx.h"
#include "StaticEx.h"

CStaticEx::CStaticEx(void)
{
	m_strFontName = DEFAULT_STATIC_FONT;
	m_colFore = DEFAULT_STATIC_TEXTCOLOR;
	m_colBack = DEFAULT_STATIC_BACKCOLOR;
	m_iFontSize = DEFAULT_STATIC_FONTSIZE;
	m_iFontWeight = STATIC_FONT_NORMAL;
	m_bItalic = FALSE;
	m_strText = _T("");
	m_bTransparent = FALSE;

	m_brushBack.CreateSolidBrush(m_colBack);

	CreateDisplayFont(FALSE);

	m_bEnabled = TRUE;
}

CStaticEx::~CStaticEx(void)
{
	m_fontDisplay.DeleteObject();
}

BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	ON_WM_CTLCOLOR_REFLECT()   
END_MESSAGE_MAP()

void CStaticEx::CreateDisplayFont(BOOL bDelete)
{
	if (bDelete)
	{
		m_fontDisplay.DeleteObject();
	}

	if (GetSafeHwnd() != NULL)
	{
		ShowWindow(SW_HIDE);
	}

	m_fontDisplay.CreateFont(
		m_iFontSize,
		0,
		0,
		0,
		static_cast<int>(m_iFontWeight),
		m_bItalic ? TRUE : FALSE, 
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		m_strFontName);


	if (GetSafeHwnd() != NULL)
	{
		ShowWindow(SW_SHOW);
	}
}

void CStaticEx::SetFontName(CString strFontName)
{
	m_strFontName = strFontName;
	CreateDisplayFont(TRUE);
}

void CStaticEx::SetFontSize(INT32 iSize)
{
	m_iFontSize = iSize;
	CreateDisplayFont(TRUE);
}

void CStaticEx::SetFontWeight(INT32 iWeight)
{
	m_iFontWeight = iWeight;
	CreateDisplayFont(TRUE);
}

HBRUSH CStaticEx::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	pDC->SetBkMode(TRANSPARENT);

	if (m_bEnabled)
		pDC->SetTextColor(m_colFore);
	else
		pDC->SetTextColor(DEFAULT_STATIC_DISABLETEXTCOLOR);

	pDC->SetBkColor(m_colBack);

	pDC->SelectObject(&m_fontDisplay);

	if (m_bTransparent)
	{
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	else
	{	
		return m_brushBack;
	}
}

void CStaticEx::EnableWindow(BOOL bEnable)
{
	RECT stRect;

	m_bEnabled = bEnable;

	if (GetSafeHwnd() != NULL)
	{
		GetWindowRect(&stRect);
		GetParent()->ScreenToClient(&stRect);
		GetParent()->InvalidateRect(&stRect);
	}
}

void CStaticEx::RecreateBackBrush()
{
	RECT stRect;
	GetWindowRect(&stRect);
	GetParent()->ScreenToClient(&stRect);
	m_brushBack.DeleteObject();
	m_brushBack.CreateSolidBrush(m_colBack);
	GetParent()->InvalidateRect(&stRect);
}

void CStaticEx::SetText(CString strTxt)
{
    RECT stRect;
    if (GetSafeHwnd() != NULL)
    {
        GetWindowRect(&stRect);
        GetParent()->ModifyStyle(NULL, DT_WORDBREAK, 0);
        GetParent()->ScreenToClient(&stRect);
        __super::SetWindowText(strTxt);
        GetParent()->InvalidateRect(&stRect);
    }
}