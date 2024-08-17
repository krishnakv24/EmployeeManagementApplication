#pragma once


class CEditEx : public CEdit
{
	DECLARE_MESSAGE_MAP()

public:
	CEditEx();
	virtual ~CEditEx();

	BOOL InitEdit(int fontsize=10);
	void SetTextColor(COLORREF color);
	
private:
	COLORREF m_NormalBKColor;
	COLORREF m_FocusBKColor;
	COLORREF m_TextColor;

	CBrush m_NormalBKBrush;
	CBrush m_FocusBKBrush;

	BOOL m_bFocus;
	CFont m_TextFont;

protected:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};