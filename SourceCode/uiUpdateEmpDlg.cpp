#include "stdafx.h"
#include "EDataDisplay.h"
#include "uiUpdateEmpDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CuiUpdateEmpDlg, CDialogEx)

CuiUpdateEmpDlg::CuiUpdateEmpDlg(stEmpData employeeData, CWnd* pParent) :
	CuiDialogEx(IDD_EDATA_UPDATE_DIALOG, pParent), m_stEmpDataToUpdate(employeeData)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CuiUpdateEmpDlg::~CuiUpdateEmpDlg()
{
}

void CuiUpdateEmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CuiDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edtEmpName);
	DDX_Control(pDX, IDC_EDIT_AGE, m_edtEmpAge);
	DDX_Control(pDX, IDC_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stName);
	DDX_Control(pDX, IDC_STATIC_AGE, m_stAge);
}

BEGIN_MESSAGE_MAP(CuiUpdateEmpDlg, CuiDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_UPDATE, &CuiUpdateEmpDlg::OnBnClickedUpdate)
END_MESSAGE_MAP()


BOOL CuiUpdateEmpDlg::OnInitDialog()
{
	CuiDialogEx::OnInitDialog();
	SetWindowText(L"Update Employee Data");

	m_btnUpdate.InitStyle(RGB(0, 0, 139), RGB(0, 0, 139), RGB(224, 238, 255), RGB(0, 0, 139), TRUE);

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_edtEmpName.SetWindowTextW(m_stEmpDataToUpdate.GetName());
	m_edtEmpAge.SetWindowTextW(m_stEmpDataToUpdate.GetAge());

	return TRUE;
}

/**
* Handles the Update button click event in the employee update dialog.
*
* Retrieves the employee name and age from the corresponding input fields.
* If both fields are empty, displays a warning message prompting the user to enter either a name or age.
* If the age field is not empty, validates that the age is a positive number. If the age is invalid,
* displays a warning message and sets focus back to the age input field.
* If the input is valid, updates the `m_stEmpDataToUpdate` structure with the new name and age while keeping the existing ID.
* Finally, closes the dialog by invoking the default `OnOK` method.
*
*/
void CuiUpdateEmpDlg::OnBnClickedUpdate()
{
	CString strEmpName, strEmpAge = L"";
	m_edtEmpName.GetWindowTextW(strEmpName);
	m_edtEmpAge.GetWindowTextW(strEmpAge);

	if (strEmpName.IsEmpty() && strEmpAge.IsEmpty())
	{
		MessageBox(L"Please enter employee name or age.",L"Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	if (!strEmpAge.IsEmpty())
	{
		int iAge = _ttoi(strEmpAge);
		if (iAge <= 0 || iAge >= 150)
		{
			MessageBox(L"Please enter a valid age between 1 and 149.", L"Warning", MB_ICONWARNING | MB_OK);
			m_edtEmpAge.SetFocus();
			return;
		}
	}

	m_stEmpDataToUpdate = stEmpData(m_stEmpDataToUpdate.GetId(), strEmpName, strEmpAge);

	CuiDialogEx::OnOK();
}

/**
* Retrieves the updated employee data.
*
* Returns the `stEmpData` structure that contains the updated employee information
* (ID, name, and age) as entered in the update dialog.
*
*/
stEmpData CuiUpdateEmpDlg::GetEmpUpdatedData()
{
	return m_stEmpDataToUpdate;
}

void CuiUpdateEmpDlg::OnClose()
{
	CuiDialogEx::OnCancel();
}




