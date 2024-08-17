#pragma once
#include "afxwin.h"
#include "uiDialogEx.h"
#include "PXButton.h"
#include "StaticEx.h"
#include "EditEx.h"

class CuiUpdateEmpDlg : public CuiDialogEx
{
	DECLARE_DYNAMIC(CuiUpdateEmpDlg)
public:
	CuiUpdateEmpDlg(stEmpData employeeData, CWnd* pParent = NULL);
	~CuiUpdateEmpDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDATA_UPDATE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnClose();
	afx_msg void OnBnClickedUpdate();
private:
	HICON m_hIcon;
	CEditEx m_edtEmpName;
	CEditEx m_edtEmpAge;
	CStaticEx m_stName;
	CStaticEx m_stAge;
	CPXButton m_btnUpdate;
	stEmpData m_stEmpDataToUpdate;
public:
	stEmpData GetEmpUpdatedData();
};
