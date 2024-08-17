#pragma once

class CPXGroupBox : public CStatic
{
	DECLARE_MESSAGE_MAP()

public:
	CPXGroupBox();
	virtual ~CPXGroupBox();
	void SetTitleColor(COLORREF color);
	void SetLineColor(COLORREF color);
	void SetLineWidth(int width);  

private:
	CFont m_TitleFont;
	CRect m_BoxRect;

	COLORREF m_TitleColor;
	COLORREF m_LineColor;

	int m_LineWidth;
	int m_TitleAlign;
	int m_HTextOffset;
	int m_VTextOffset;

protected:
	virtual void PreSubclassWindow();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
