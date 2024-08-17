#pragma once
#include "afxcmn.h"
#include "uiHeaderCtrl.h"
class CuiListControl :public CListCtrl
{
public:
	CuiListControl();
	virtual ~CuiListControl();
protected:
	virtual void PreSubclassWindow();
	void SetHeaderColors(COLORREF Bk, COLORREF Text);

	DECLARE_MESSAGE_MAP()
	CuiHeaderCtrl m_HeaderCtrl;
};

