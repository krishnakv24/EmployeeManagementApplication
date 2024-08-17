#include "stdafx.h"
#include "uiListControl.h"


CuiListControl::CuiListControl()
{
}

CuiListControl::~CuiListControl()
{
}

BEGIN_MESSAGE_MAP(CuiListControl, CListCtrl)
	
END_MESSAGE_MAP()

void CuiListControl::PreSubclassWindow()
{
	CListCtrl::PreSubclassWindow();
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	if (pHeader != nullptr)
	{
		m_HeaderCtrl.SubclassWindow(pHeader->GetSafeHwnd());
	}
}

void CuiListControl::SetHeaderColors(COLORREF Bk, COLORREF Text)
{
	m_HeaderCtrl.SetHeaderColors(Bk, Text);
}

