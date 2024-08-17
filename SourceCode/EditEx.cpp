#include "stdafx.h"
#include "EditEx.h"

BEGIN_MESSAGE_MAP(CEditEx, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


CEditEx::CEditEx()
{
	m_bFocus = FALSE;	
	m_TextColor =  RGB(0,0,0);

	m_NormalBKColor = RGB(255,255,255);	
	m_FocusBKColor  = RGB(223, 239, 255);

	m_NormalBKBrush.CreateSolidBrush(m_NormalBKColor);
	m_FocusBKBrush.CreateSolidBrush(m_FocusBKColor);
}

CEditEx::~CEditEx()
{
	m_TextFont.DeleteObject();

	m_NormalBKBrush.DeleteObject();
	m_FocusBKBrush.DeleteObject();
}

BOOL CEditEx::InitEdit(int fontsize)
{	
	LOGFONT lgfnt;
	CDC *pDC = GetDC();

	lgfnt.lfHeight			   = -MulDiv(fontsize, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);
	lgfnt.lfWidth			     = 0;
	lgfnt.lfEscapement	   = 0;
	lgfnt.lfOrientation	   = 0;
	lgfnt.lfWeight			   = FW_BOLD;
	lgfnt.lfItalic		     = FALSE;
	lgfnt.lfUnderline		   = FALSE;
	lgfnt.lfStrikeOut		   = FALSE;
	lgfnt.lfCharSet			   = DEFAULT_CHARSET;
	lgfnt.lfOutPrecision	 = OUT_DEFAULT_PRECIS;
	lgfnt.lfClipPrecision	 = CLIP_DEFAULT_PRECIS;
	lgfnt.lfQuality			   = DEFAULT_QUALITY;
	lgfnt.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    wcscpy_s(lgfnt.lfFaceName, L"Malgun Gothic");

	m_TextFont.DeleteObject();
	m_TextFont.CreateFontIndirect(&lgfnt);
	SetFont(&m_TextFont, TRUE);
	ReleaseDC(pDC);

	return TRUE;
}

void CEditEx::SetTextColor(COLORREF color)
{
	m_TextColor = color;
}

HBRUSH CEditEx::CtlColor(CDC* pDC, UINT /*nCtlColor*/) 
{
	pDC->SetBkColor(m_bFocus?m_FocusBKColor:m_NormalBKColor);
	pDC->SetTextColor(m_TextColor);

	return m_bFocus?(HBRUSH)m_FocusBKBrush:(HBRUSH)m_NormalBKBrush;
}

void CEditEx::OnSetFocus(CWnd* /*pOldWnd*/)
{
	m_bFocus = TRUE;
	Invalidate();

	CEdit::OnSetFocus(NULL);
	//CEdit::OnSetFocus(pOldWnd);
}

void CEditEx::OnKillFocus(CWnd* /*pNewWnd*/)
{
	m_bFocus = FALSE;
	Invalidate();

	CEdit::OnKillFocus(NULL);
}
