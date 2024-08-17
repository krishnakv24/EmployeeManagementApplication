#pragma once
#include "afxdialogex.h"
class CuiDialogEx :public CDialogEx
{
public:
	CuiDialogEx();
	CuiDialogEx(UINT nIDTemplate, CWnd* pParent = nullptr);
	virtual ~CuiDialogEx();
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
protected:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};

