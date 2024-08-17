#pragma once
#include "afxwin.h"
#include "PXButton.h"
#include "uiDialogEx.h"
#include "StaticEx.h"
#include "EditEx.h"

class CuiInsertEmpDlg : public CuiDialogEx
{
	DECLARE_DYNAMIC(CuiInsertEmpDlg)
public:
	CuiInsertEmpDlg(CString EmpID, CWnd* pParent = NULL);  
	~CuiInsertEmpDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDATA_INSERT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedInsert();
	afx_msg void OnClose();
private:
	HICON m_hIcon;
	CEditEx m_edtEmpName;
	CEditEx m_edtEmpAge;
	CPXButton m_btnInsert;
	CStaticEx m_stName;
	CStaticEx m_stAge;
	CString m_strEmpID;
	CString m_strEmpName, m_strEmpAge;
public:
	stEmpData GetEmpData();	

};
