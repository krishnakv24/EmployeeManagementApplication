#pragma once
#include <afxcmn.h>

class CuiHeaderCtrl : public CHeaderCtrl
{
public:
	CuiHeaderCtrl();
	virtual ~CuiHeaderCtrl();

	void SetHeaderColors(COLORREF bgColor, COLORREF textColor);

protected:
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

private:
	COLORREF m_headerBgColor;
	COLORREF m_headerTextColor;
};