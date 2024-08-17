#pragma once
#include "afxwin.h"
#include "RoundProgress.h"

class CuiProgressBarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CuiProgressBarDlg)

public:
	CuiProgressBarDlg(CWnd* pParent = NULL);
	virtual ~CuiProgressBarDlg();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDATA_PROGRESS_BAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()

private:
	CRoundProgress m_stProgressBar;

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
};
