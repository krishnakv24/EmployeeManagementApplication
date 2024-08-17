#include "stdafx.h"
#include "afxdialogex.h"
#include "EDataDisplay.h"
#include "EDataDisplayDlg.h"
#include "uiInsertEmpDlg.h"
#include "uiUpdateEmpDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CEDataDisplayDlg::CEDataDisplayDlg(CWnd* pParent) :
	CuiDialogEx(IDD_EDATADISPLAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEDataDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CuiDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_GRP_BOX_EMP_TABLE, m_gbEmployeTable);
	DDX_Control(pDX, IDC_LIST_EMPLOYE_DETAILS_TABLE, m_lstEmployeData);
	DDX_Control(pDX, IDC_BUTTON_INSERT, m_btnInsertEmpData);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_btnUpdateEmpData);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelEmpData);
	DDX_Control(pDX, IDC_GRP_BOX_ACTION, m_gbAction);
}

BEGIN_MESSAGE_MAP(CEDataDisplayDlg, CuiDialogEx)
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CEDataDisplayDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CEDataDisplayDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CEDataDisplayDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

/**
* Initializes the dialog when it is created.
* - Displays an initialization popup to the user.
* - Sets the dialog's icon.
* - Attempts to load employee data from an XML file.
* - Prepares the UI by aligning and initializing elements.
* If initialization of the employee data handler fails,
* it displays an error message, logs the error, and closes the dialog.
* Returns FALSE if initialization fails, otherwise returns TRUE.
*
*/
BOOL CEDataDisplayDlg::OnInitDialog()
{
	CuiDialogEx::OnInitDialog();
	
	theApp.ShowPopupInitialize();

	SetIcon(m_hIcon, TRUE); 
	SetIcon(m_hIcon, FALSE); 

	CString FilePath = theApp.GetExePath().c_str();
	try
	{
		m_ptrEmpData = make_unique<CdtEmployeeDataHandler>(FilePath,L"EData.xml");
	}
	catch (const exception& e)
	{
		CString errorMsg;
		errorMsg.Format(L"Failed to initialize employee data handler: %S", e.what());
		MessageBox(errorMsg,L"Error", MB_ICONERROR | MB_OK);
		LOG_ERROR(errorMsg);

		CuiDialogEx::EndDialog(IDCANCEL);
		return FALSE; 
	}
	
	AlignUIElements();
	InitUIElements();

	theApp.HidePopupInitialize();
	return TRUE; 
}

/**
* Initializes and sets up the UI elements of the dialog.
*
* Sets the title of the dialog window to "Employee Data Manager".
* Initializes the employee list control and populates it with all employee data retrieved from the employee data handler.
* If there is any employee data available, it fills the list control with that data.
*/
void CEDataDisplayDlg::InitUIElements()
{
	SetWindowText(L"Employee Data Manager");

	m_btnInsertEmpData.InitStyle(RGB(0, 100, 0), RGB(0, 100, 0), RGB(229, 244, 234), RGB(0, 100, 0), TRUE);
	m_btnUpdateEmpData.InitStyle(RGB(0, 0, 139), RGB(0, 0, 139), RGB(224, 238, 255), RGB(0, 0, 139), TRUE);
	m_btnDelEmpData.InitStyle(RGB(139, 0, 0), RGB(139, 0, 0), RGB(255, 228, 225), RGB(139, 0, 0), TRUE);

	m_lstEmployeData.InitEmployeList();
	auto AllEmpData = m_ptrEmpData->GetAllEmployeeData();
	if (AllEmpData.size())
	{
		m_lstEmployeData.FillEmployeData(AllEmpData);
	}
}

/**
* Handles the insertion of a new employee when the "Insert" button is clicked.
*
* Validates the employee data handler, generates a new employee ID,
* and opens a dialog for entering the new employee's details.
* If the user confirms, the new employee is added to the XML and
* the employee list is updated. Displays appropriate messages for success or failure.
*/
void CEDataDisplayDlg::OnBnClickedButtonInsert()
{
	if (!m_ptrEmpData)
	{
		MessageBox(L"Employee data pointer is not initialized.", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	CString StrEmpID = m_ptrEmpData->GenerateEmployeeID();
	CuiInsertEmpDlg insertEmpDlg(StrEmpID);
	if (insertEmpDlg.DoModal() != IDOK)
	{
		m_lstEmployeData.RedrawSelectedRow();
		return;  
	}

	auto EmpData = insertEmpDlg.GetEmpData();
	if (!m_ptrEmpData->AddEmployee(EmpData))
	{
		MessageBox(L"Failed to add new employee, " + EmpData.GetName(), L"Error", MB_OK | MB_ICONERROR);
		return;
	}
	m_lstEmployeData.InsertEmployeItemData(EmpData);
	LOG_INFO(L"Employee successfully added," + EmpData.GetEmpDataAsString());
	MessageBox(L"Employee successfully added.",L"Sucess", MB_OK | MB_ICONINFORMATION);
}

/**
* Handles the update process when the "Update" button is clicked.
*
* Retrieves the selected employee's ID and loads their data.
* Opens a dialog for editing the employee's details. If the user confirms the changes,
* the employee data is updated in the xml and the list is refreshed.
* Displays messages for successful updates or errors.
*/
void CEDataDisplayDlg::OnBnClickedButtonUpdate()
{
	CString strEID = m_lstEmployeData.GetSelectedEId();
	if (strEID.IsEmpty())
	{
		MessageBox(L"Please select an employee to update.",L"Error", MB_OK | MB_ICONWARNING);
		return;
	}

	auto EmpData = m_ptrEmpData->GetEmployeeDataFor(strEID);
	CuiUpdateEmpDlg updateEmpDlg(EmpData);
	if (updateEmpDlg.DoModal() != IDOK)
	{
		m_lstEmployeData.RedrawSelectedRow();  
		return;
	}

	auto EmpDataUpdated = updateEmpDlg.GetEmpUpdatedData();
	if (!m_ptrEmpData->UpdateEmployee(EmpDataUpdated))
	{
		MessageBox(L"Failed to update employee, " + EmpDataUpdated.GetName(),L"Error", MB_OK | MB_ICONERROR);
	}
	m_lstEmployeData.UpdateSelectedEmployData(EmpDataUpdated);

	LOG_INFO(L"Employee successfully updated, Preveious Data:" + EmpData.GetEmpDataAsString() + L", New Data:" + EmpDataUpdated.GetEmpDataAsString());
	MessageBox(L"Employee successfully updated.",L"Sucess", MB_OK | MB_ICONINFORMATION);
}

/**
* Handles the deletion of an employee when the "Delete" button is clicked.
*
* Retrieves the selected employee's ID and confirms the deletion with the user.
* If confirmed, the employee data is removed from the xml and the list is updated.
* Displays appropriate messages for confirmation, success, or failure.
*/
void CEDataDisplayDlg::OnBnClickedButtonDelete()
{
	CString RemoveEID = m_lstEmployeData.GetSelectedEId();
	if (RemoveEID.IsEmpty())
	{
		MessageBox(L"Please select an employee to remove.",L"Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	auto EmpData = m_ptrEmpData->GetEmployeeDataFor(RemoveEID);
	if (MessageBox(L"Are you want to remove Employee " + EmpData.GetName() + "?",L"Confirmation", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		m_lstEmployeData.RedrawSelectedRow();
		return;
	}

	if (!m_ptrEmpData->DeleteEmployee(RemoveEID))
	{
		MessageBox(L"Failed to remove employee data.",L"Error", MB_OK | MB_ICONERROR);
		return;
	}
	m_lstEmployeData.DeleteSelectedEmploye();

	LOG_INFO(L"Employee successfully removed." + EmpData.GetEmpDataAsString());
	MessageBox(L"Employee successfully removed.",L"Sucess", MB_OK | MB_ICONINFORMATION);
}

void CEDataDisplayDlg::OnClose()
{
	int result = MessageBox(L"Do you want to close the Employee Data Management Application?",L"Confirmation", MB_YESNO | MB_ICONQUESTION);
	if (result == IDYES)
	{
		CuiDialogEx::OnCancel();
	}
}


/**
* Sets the minimum size of the dialog window.
*
* Ensures the window cannot be resized smaller than 850x600 pixels.
*/
void CEDataDisplayDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 850; 
	lpMMI->ptMinTrackSize.y = 600; 

	CuiDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CEDataDisplayDlg::OnSize(UINT nType, int cx, int cy)
{
	CuiDialogEx::OnSize(nType, cx, cy);

	AlignUIElements();
	Invalidate();
}

/**
* Aligns and resizes the UI elements within the dialog to fit the client area.
*
* Adjusts the positions and sizes of the employee table, action buttons,
* and other controls based on the current size of the dialog. Ensures
* that all elements are properly aligned with consistent margins and spacing.
*/
void CEDataDisplayDlg::AlignUIElements()
{
	CRect rectClient;
	GetClientRect(&rectClient);

	if (m_gbEmployeTable.GetSafeHwnd())
	{
		int margin = 10;
		int minGrpBoxWidth = 200; 

		int width = max(static_cast<int>(rectClient.Width() * 0.70), minGrpBoxWidth);
		int height = rectClient.Height() - 2 * margin;

		CRect grpEmpTableRect(margin, margin, width, height);
		m_gbEmployeTable.MoveWindow(grpEmpTableRect, TRUE);

		CRect rectListControl(
			grpEmpTableRect.left + margin,
			grpEmpTableRect.top + 20,
			grpEmpTableRect.right - margin,
			grpEmpTableRect.bottom - margin
		);
		m_lstEmployeData.MoveWindow(rectListControl);
		m_lstEmployeData.AdjustEmployeeTableColumnWidths();

		int btnHeight = 40;
		int marginbtn = 8;
		int btnCnt = 3;
		int TotalActionGrpBoxHeight = (btnHeight + marginbtn * 2) * btnCnt;
		int actionWidth = max(rectClient.Width() - width - 3 * margin, minGrpBoxWidth);

		CRect actionRect(
			grpEmpTableRect.right + margin,
			grpEmpTableRect.top,
			grpEmpTableRect.right + margin + actionWidth,
			grpEmpTableRect.top + TotalActionGrpBoxHeight
		);
		m_gbAction.MoveWindow(actionRect);

		CRect InsertBtnRect(
			actionRect.left + marginbtn,
			actionRect.top + 20,
			actionRect.right - marginbtn,
			actionRect.top + 20 + btnHeight
		);
		m_btnInsertEmpData.MoveWindow(InsertBtnRect);

		CRect UpdateBtnRect(
			InsertBtnRect.left,
			InsertBtnRect.bottom + marginbtn,
			InsertBtnRect.right,
			InsertBtnRect.bottom + marginbtn + btnHeight
		);
		m_btnUpdateEmpData.MoveWindow(UpdateBtnRect);

		CRect DeleteBtnRect(
			UpdateBtnRect.left,
			UpdateBtnRect.bottom + marginbtn,
			UpdateBtnRect.right,
			UpdateBtnRect.bottom + marginbtn + btnHeight
		);
		m_btnDelEmpData.MoveWindow(DeleteBtnRect);
	}
}







