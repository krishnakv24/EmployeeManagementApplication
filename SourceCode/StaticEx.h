#pragma once
#include "afxwin.h"

#define DEFAULT_STATIC_TEXTCOLOR		RGB(0,0,0)
#define DEFAULT_STATIC_BACKCOLOR		RGB(245, 245, 255)
#define DEFAULT_STATIC_FONT				_T("Arial")
#define DEFAULT_STATIC_FONTSIZE			16
#define STATIC_FONT_NORMAL				FW_THIN
#define STATIC_FONT_BOLD				FW_HEAVY
#define STATIC_DEFAULT_TRASPARENTCOLOR	RGB(255,255,255)
#define DEFAULT_STATIC_DISABLETEXTCOLOR	RGB(110, 110, 110)

class CStaticEx :public CStatic
{
private:
	COLORREF m_colBack;
	COLORREF m_colFore;
	CString m_strFontName;
	CString m_strText;
	CBrush m_brushBack;
	BOOL m_bEnabled;

	INT32 m_iFontSize;
	INT32 m_iFontWeight;
	BOOL m_bItalic;
	BOOL m_bTransparent;
	CFont m_fontDisplay;

	void CreateDisplayFont(BOOL bDelete);
public:
	COLORREF GetBackColor() { return m_colBack; }

	CStaticEx(void);
	~CStaticEx(void);
	void EnableWindow(BOOL bEnable);
	void SetBackColor(COLORREF colBack) { m_colBack = colBack; }
	void SetForeColor(COLORREF colFore) { m_colFore = colFore; }
	void SetTransparent(BOOL bTransparent) { m_bTransparent = bTransparent; }
	void SetFontName(CString strFontName);
	void SetFontSize(INT32 iSize);
	void SetFontWeight(INT32 iWeight);	
	void RecreateBackBrush();
    void SetText(CString strTxt);

	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    CBrush m_brush;
};
