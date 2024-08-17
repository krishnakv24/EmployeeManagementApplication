#include "stdafx.h"
#include "afxdialogex.h"
#include "EDataDisplay.h"
#include "uiInsertEmpDlg.h"

IMPLEMENT_DYNAMIC(CuiInsertEmpDlg, CDialogEx)

CuiInsertEmpDlg::CuiInsertEmpDlg(CString EmpID, CWnd* pParent):
	CuiDialogEx(IDD_EDATA_INSERT_DIALOG, pParent), m_strEmpName(L""), m_strEmpAge(L""),m_strEmpID(EmpID)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CuiInsertEmpDlg::~CuiInsertEmpDlg()
{
}

void CuiInsertEmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CuiDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_NAME, m_edtEmpName);
	DDX_Control(pDX, IDC_EDIT_AGE, m_edtEmpAge);
	DDX_Control(pDX, IDC_INSERT, m_btnInsert);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stName);
	DDX_Control(pDX, IDC_STATIC_AGE, m_stAge);
}

BEGIN_MESSAGE_MAP(CuiInsertEmpDlg, CuiDialogEx)
	ON_BN_CLICKED(IDC_INSERT, &CuiInsertEmpDlg::OnBnClickedInsert)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CuiInsertEmpDlg::OnInitDialog()
{
	CuiDialogEx::OnInitDialog();
	SetWindowText(L"Insert Employee Data");

	m_btnInsert.InitStyle(RGB(0, 100, 0), RGB(0, 100, 0), RGB(229, 244, 234), RGB(0, 100, 0), TRUE);
	
	SetIcon(m_hIcon, TRUE); 
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

/**
* Handles the Insert button click event in the employee insertion dialog.
*
* Retrieves the employee name and age from the corresponding input fields.
* If both fields are empty, displays a warning message prompting the user to enter either a name or age.
* If the age field is not empty, validates that the age is a positive number. If the age is invalid,
* displays a warning message and sets focus back to the age input field.
* If the input is valid, closes the dialog by invoking the default `OnOK` method.
*
*/
void CuiInsertEmpDlg::OnBnClickedInsert()
{
	m_edtEmpName.GetWindowTextW(m_strEmpName);
	m_edtEmpAge.GetWindowTextW(m_strEmpAge);

	if (m_strEmpName.IsEmpty() && m_strEmpAge.IsEmpty())
	{
		MessageBox(L"Please enter employee name or age.",L"Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	if (!m_strEmpAge.IsEmpty())
	{
		int iAge = _ttoi(m_strEmpAge);
		if (iAge <= 0 || iAge >= 150)
		{
			MessageBox(L"Please enter a valid age between 1 and 149.", L"Warning", MB_ICONWARNING | MB_OK);
			m_edtEmpAge.SetFocus();
			return;
		}
	}

	CuiDialogEx::OnOK();
}

/**
* Retrieves the employee data entered in the dialog.
*
* Constructs and returns a `stEmpData` structure containing the employee's ID, name, and age
* based on the values entered in the dialog fields.
*
*/
stEmpData CuiInsertEmpDlg::GetEmpData()
{
	return stEmpData(m_strEmpID,m_strEmpName, m_strEmpAge);
}

void CuiInsertEmpDlg::OnClose()
{
	CuiDialogEx::OnCancel();
}


