#pragma once

#include "afxbutton.h"

class CPXButton : public CMFCButton
{
	DECLARE_MESSAGE_MAP()

public:
	CPXButton();
	virtual ~CPXButton();

	void InitStyle(COLORREF txtclr, COLORREF txthotclr, COLORREF backclr, COLORREF focusclr, BOOL bdrawfocus);

private:
	CBrush m_BackColor;
	COLORREF m_FocusColor;
	COLORREF m_BorderColor;
	CFont m_boldFont; // Font for bold text

protected:
	virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState) override;
	virtual void OnFillBackground(CDC* pdc, const CRect& rectclient) override;
	virtual void OnDrawFocusRect(CDC* pdc, const CRect& rectclient) override;
	void OnDrawBorder(CDC* pdc, const CRect& rect);
};
