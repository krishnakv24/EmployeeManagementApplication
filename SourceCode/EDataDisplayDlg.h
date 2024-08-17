#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "uiDialogEx.h"
#include "uiListEmployeData.h"
#include "dtEmployeeDataHandler.h"
#include "PXGroupBox.h"
#include "PXButton.h"

class CEDataDisplayDlg : public CuiDialogEx
{
public:
	CEDataDisplayDlg(CWnd* pParent = NULL);	

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDATADISPLAY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonDelete();
private:
	HICON				 m_hIcon;
	CPXGroupBox          m_gbEmployeTable;
	CPXGroupBox          m_gbAction;
	CPXButton            m_btnInsertEmpData;
	CPXButton            m_btnUpdateEmpData;
	CPXButton            m_btnDelEmpData;
private:
	unique_ptr<CdtEmployeeDataHandler> m_ptrEmpData = nullptr;
	CuiListEmployeData                 m_lstEmployeData;
private:
	void AlignUIElements();
	void InitUIElements();
};
