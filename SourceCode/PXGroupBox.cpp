#include "stdafx.h"
#include "PXGroupBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CPXGroupBox, CStatic)
	ON_WM_PAINT()
	ON_WM_SIZE()  
END_MESSAGE_MAP()

CPXGroupBox::CPXGroupBox()
{
	m_TitleColor = RGB(0, 128, 128);
	m_LineColor = RGB(216, 191, 216);
	m_TitleFont.CreateFont(16, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Malgun Gothic");
	m_TitleAlign = BS_LEFT;
	m_HTextOffset = 10;
	m_VTextOffset = 0;

	m_LineWidth = 2; 
}

CPXGroupBox::~CPXGroupBox()
{
	m_TitleFont.DeleteObject();
}

void CPXGroupBox::SetTitleColor(COLORREF color)
{
	m_TitleColor = color;
	Invalidate(TRUE);
}

void CPXGroupBox::SetLineColor(COLORREF color)
{
	m_LineColor = color;
	Invalidate(TRUE);
}

void CPXGroupBox::SetLineWidth(int width)
{
	m_LineWidth = width;
	Invalidate(TRUE);
}

void CPXGroupBox::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();
	GetClientRect(&m_BoxRect);
}

void CPXGroupBox::OnPaint()
{
	CPaintDC dc(this);

	CPoint spoint;
	CPoint epoint;

	CPen newpen, *poldpen;

	CString title;
	GetWindowText(title);

	CSize txtextent = dc.GetTextExtent(title);

	spoint.y = epoint.y = m_BoxRect.top + txtextent.cy / 2 - 1;
	switch (m_TitleAlign)
	{
	case BS_RIGHT:
	{
		epoint.x = m_BoxRect.right - m_HTextOffset;
		spoint.x = epoint.x - txtextent.cx;
		break;
	}
	case BS_LEFT:
	{
		spoint.x = m_BoxRect.left + m_HTextOffset;
		epoint.x = spoint.x + txtextent.cx;
		break;
	}
	default:
	{
		spoint.x = (m_BoxRect.Width() - txtextent.cx) / 2;
		epoint.x = spoint.x + txtextent.cx;
		break;
	}
	}

	CFont* poldfont = dc.SelectObject(&m_TitleFont);
	newpen.CreatePen(PS_SOLID, m_LineWidth, m_LineColor);
	poldpen = dc.SelectObject(&newpen);

	dc.MoveTo(spoint);
	dc.LineTo(m_BoxRect.left, spoint.y);
	dc.LineTo(m_BoxRect.left, m_BoxRect.bottom);
	dc.LineTo(m_BoxRect.right, m_BoxRect.bottom);
	dc.LineTo(m_BoxRect.right, epoint.y);
	dc.LineTo(epoint);

	COLORREF oldColor = dc.GetTextColor();
	dc.SetTextColor(m_TitleColor);
	dc.SetBkMode(TRANSPARENT);

	if (!title.IsEmpty())
	{
		spoint.y -= m_VTextOffset;
		dc.DrawText(title, CRect(spoint, epoint), DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOCLIP);
	}

	dc.SelectObject(poldfont);
	dc.SetTextColor(oldColor);
	dc.SelectObject(poldpen);
}

void CPXGroupBox::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	if (cx > 0 && cy > 0)
	{
		GetClientRect(&m_BoxRect);
		Invalidate();
	}	
}
