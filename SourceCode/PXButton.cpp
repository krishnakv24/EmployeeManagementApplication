#include "stdafx.h"
#include "PXButton.h"

BEGIN_MESSAGE_MAP(CPXButton, CMFCButton)
END_MESSAGE_MAP()

CPXButton::CPXButton()
{
	CMFCButton::m_bWinXPTheme = FALSE;

	m_bTransparent = FALSE;
	m_bDrawFocus = TRUE;
	m_bHighlightChecked = FALSE;

	m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;

	SetTextColor(RGB(10, 10, 10));
	SetTextHotColor(RGB(255, 50, 0));

	m_BackColor.CreateSolidBrush(RGB(240, 240, 240));
	m_FocusColor = RGB(105, 105, 105);
	m_BorderColor = RGB(0, 0, 0);


	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 16; 
	lf.lfWeight = FW_BOLD;
	_tcscpy_s(lf.lfFaceName, _T("Arial")); 
	m_boldFont.CreateFontIndirect(&lf);
}

CPXButton::~CPXButton()
{
	m_BackColor.DeleteObject();
}

void CPXButton::InitStyle(COLORREF txtclr, COLORREF txthotclr, COLORREF backclr, COLORREF focusclr, BOOL bdrawfocus)
{
	SetTextColor(txtclr);
	SetTextHotColor(txthotclr);

	m_BackColor.DeleteObject(); 
	m_BackColor.CreateSolidBrush(backclr);

	m_FocusColor = focusclr;
	m_bDrawFocus = bdrawfocus;
}

void CPXButton::OnDraw(CDC* pDC, const CRect& rect, UINT uiState)
{
	CRect rectText = rect;
	CRect rectImage = rect;

	CString strText;
	GetWindowText(strText);

	OnFillBackground(pDC, rect);

	if (m_sizeImage.cx != 0)
	{
		if (!strText.IsEmpty())
		{
			if (m_bTopImage)
			{
				rectImage.bottom = rectImage.top + m_sizeImage.cy + GetVertMargin();
				rectText.top = rectImage.bottom;
				rectText.bottom -= GetVertMargin();
			}
			else if (m_bRightImage)
			{
				rectText.right -= m_sizeImage.cx + GetImageHorzMargin() / 2;
				rectImage.left = rectText.right;
				rectImage.right -= GetImageHorzMargin() / 2;
			}
			else
			{
				rectText.left += m_sizeImage.cx + GetImageHorzMargin() / 2;
				rectImage.left += GetImageHorzMargin() / 2;
				rectImage.right = rectText.left;
			}
		}
		rectImage.DeflateRect((rectImage.Width() - m_sizeImage.cx) / 2, max(0, (rectImage.Height() - m_sizeImage.cy) / 2));
	}
	else
	{
		rectImage.SetRectEmpty();
	}

	CFont* pOldFont = pDC->SelectObject(&m_boldFont); 
	ENSURE(pOldFont != NULL);

	pDC->SetBkMode(TRANSPARENT);
	COLORREF clrText = m_clrRegular == ((COLORREF)-1) ? GetGlobalData()->clrBtnText : m_clrRegular;

	if (m_bHighlighted && m_clrHover != (COLORREF)-1)
	{
		clrText = m_clrHover;
	}

	UINT uiDTFlags = DT_END_ELLIPSIS;
	BOOL bIsSingleLine = FALSE;

	if (strText.Find(_T('\n')) < 0)
	{
		uiDTFlags |= DT_VCENTER | DT_SINGLELINE;
		bIsSingleLine = TRUE;
	}
	else
	{
		rectText.DeflateRect(0, GetVertMargin() / 2);
	}

	switch (m_nAlignStyle)
	{
	case ALIGN_LEFT:
		uiDTFlags |= DT_LEFT;
		rectText.left += GetImageHorzMargin() / 2;
		break;

	case ALIGN_RIGHT:
		uiDTFlags |= DT_RIGHT;
		rectText.right -= GetImageHorzMargin() / 2;
		break;

	case ALIGN_CENTER:
		uiDTFlags |= DT_CENTER;
	}

	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		uiDTFlags |= DT_RTLREADING;
	}

	if ((uiState & ODS_DISABLED) && m_bGrayDisabled)
	{
		pDC->SetTextColor(GetGlobalData()->clrBtnHilite);

		CRect rectShft = rectText;
		rectShft.OffsetRect(1, 1);
		OnDrawText(pDC, rectShft, strText, uiDTFlags, uiState);

		clrText = GetGlobalData()->clrGrayedText;
	}

	if (uiState & ODS_FOCUS)
	{
		clrText = RGB(0, 0, 150);
	}

	pDC->SetTextColor(clrText);

	if (m_bDelayFullTextTooltipSet)
	{
		BOOL bIsFullText = pDC->GetTextExtent(strText).cx <= rectText.Width();
		SetTooltip(bIsFullText || !bIsSingleLine ? NULL : (LPCTSTR)strText);
		m_bDelayFullTextTooltipSet = FALSE;
	}

	OnDrawText(pDC, rectText, strText, uiDTFlags, uiState);

	if (!rectImage.IsRectEmpty())
	{
		if (m_nStdImageId != (CMenuImages::IMAGES_IDS) - 1)
		{
			CMenuImages::IMAGES_IDS id = m_nStdImageId;

			if ((uiState & ODS_DISABLED) && m_bGrayDisabled && m_nStdImageDisabledId != 0)
			{
				id = m_nStdImageDisabledId;
			}

			CMenuImages::Draw(pDC, id, rectImage.TopLeft(), m_StdImageState);
		}
		else
		{
			BOOL bIsDisabled = (uiState & ODS_DISABLED) && m_bGrayDisabled;

			CMFCToolBarImages& imageChecked = (bIsDisabled && m_ImageCheckedDisabled.GetCount() != 0) ? m_ImageCheckedDisabled :
				(m_bHighlighted && m_ImageCheckedHot.GetCount() != 0) ? m_ImageCheckedHot : m_ImageChecked;

			CMFCToolBarImages& image = (bIsDisabled && m_ImageDisabled.GetCount() != 0) ? m_ImageDisabled :
				(m_bHighlighted && m_ImageHot.GetCount() != 0) ? m_ImageHot : m_Image;

			if (m_bChecked && imageChecked.GetCount() != 0)
			{
				CAfxDrawState ds;

				imageChecked.PrepareDrawImage(ds);
				imageChecked.Draw(pDC, rectImage.left, rectImage.top, 0, FALSE, bIsDisabled && m_ImageCheckedDisabled.GetCount() == 0);
				imageChecked.EndDrawImage(ds);
			}
			else if (image.GetCount() != 0)
			{
				CAfxDrawState ds;

				image.PrepareDrawImage(ds);
				image.Draw(pDC, rectImage.left, rectImage.top, 0, FALSE, bIsDisabled && m_ImageDisabled.GetCount() == 0);
				image.EndDrawImage(ds);
			}
		}
	}

	OnDrawBorder(pDC, rect);
	pDC->SelectObject(pOldFont);  
}

void CPXButton::OnFillBackground(CDC* pdc, const CRect& rectclient)
{
	pdc->FillRect(rectclient, &m_BackColor);

	if (m_bChecked && m_bHighlightChecked && !(m_bPushed && m_bHighlighted))
	{
		CDrawingManager dm(*pdc);
		dm.HighlightRect(rectclient);
	}
}

void CPXButton::OnDrawFocusRect(CDC* pdc, const CRect& rectclient)
{
	if (m_bDrawFocus)
	{
		CRect rectfocus = rectclient;
		rectfocus.InflateRect(2, 2);
		pdc->Draw3dRect(rectfocus, m_FocusColor, m_FocusColor);
	}
}

void CPXButton::OnDrawBorder(CDC* pdc, const CRect& rect)
{
	CRect borderRect = rect;
	borderRect.DeflateRect(1, 1);
	pdc->Draw3dRect(borderRect, m_BorderColor, m_BorderColor);
}
