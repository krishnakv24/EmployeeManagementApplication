#include "stdafx.h"
#include "uiListEmployeData.h"


CuiListEmployeData::CuiListEmployeData()
{
	m_mapEmpListTitle = { { eEmpID, L"Emp ID" },{ eEmpName, L"Name" },{ eEmpAge, L"Age" } };
}

CuiListEmployeData::~CuiListEmployeData()
{
}

/**
* Sets up the employee list view.
*
* This method configures the list view to display items in a report style with
* full row selection and gridlines. It calculates the width of each column and
* adds columns to the list view based on the employee list titles.
*/
void CuiListEmployeData::InitEmployeList()
{
	SetView(LVS_REPORT);
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect RectList;
	GetClientRect(&RectList);
	int totalWidthCol =static_cast<int>(RectList.Width() / eColCount);

	int i = 0;
	for (const auto& entry : m_mapEmpListTitle)
	{
		InsertColumn(i++, entry.second, LVCFMT_LEFT, totalWidthCol);
	}
	SetHeaderColors(RGB(224, 238, 255),RGB(0, 0, 139));
}

/**
* Populates the list view with employee data.
*
* This method clears the current items in the list view and fills it with
* employee data from the provided map. For each employee, it adds a new row
* with the employee ID, name, and age. After populating the list, it ensures
* no items are selected.
*
*/
void CuiListEmployeData::FillEmployeData(mapEmpData& employeeDataMap)
{
	DeleteAllItems();  
	int rowIndex = 0;
	for (auto& entry : employeeDataMap)
	{
		CString empId = entry.first;
		stEmpData empData = entry.second;

		InsertItem(rowIndex, empId);
		SetItemText(rowIndex, eEmpName, empData.GetName());
		SetItemText(rowIndex, eEmpAge, empData.GetAge());
		++rowIndex; 
	}
	SetItemState(-1, 0, LVIS_SELECTED);
}

/**
* Inserts a new employee item into the list view.
*
* This method adds a new row to the list view with the provided employee data,
* including the employee's ID, name, and age. After inserting the item, it makes
* sure the newly added row is visible and clears any item selection.
*
*/
void CuiListEmployeData::InsertEmployeItemData(stEmpData& employeeData)
{
	int rowIndex = GetItemCount(); 
	int nItem = InsertItem(rowIndex, employeeData.GetId());
	SetItemText(nItem, eEmpName, employeeData.GetName());
	SetItemText(nItem, eEmpAge, employeeData.GetAge());

	EnsureVisible(nItem, FALSE);
	SetItemState(-1, 0, LVIS_SELECTED);
}

/**
* Updates the selected employee data in the list view.
*
* This method finds the currently selected item in the list view and updates
* its name and age with the provided employee data. If an item is selected
* and updated, the row is redrawn for visual confirmation.
*
*/
bool CuiListEmployeData::UpdateSelectedEmployData(stEmpData& employeeData)
{
	int selectedItem = GetNextItem(-1, LVNI_SELECTED);
	if (selectedItem != -1)
	{
		SetItemText(selectedItem, eEmpName, employeeData.GetName());
		SetItemText(selectedItem, eEmpAge, employeeData.GetAge());

		return RedrawSelectedRow();
	}
	return false;
}

/**
* Deletes the selected employee from the list view.
*
* This method identifies the currently selected item in the list view and deletes
* it. If an item is successfully deleted, the method returns `true`. If no item
* is selected, it returns `false`.
*
*/
bool CuiListEmployeData::DeleteSelectedEmploye()
{
	int selectedItem = GetNextItem(-1, LVNI_SELECTED);
	if (selectedItem != -1)
	{
		DeleteItem(selectedItem);
		return true;
	}
	return false;
}

/**
* Retrieves the employee ID of the selected item.
*
* This method returns the employee ID of the currently selected item in the list view.
* If no item is selected, it returns an empty string.
*
*/
CString CuiListEmployeData::GetSelectedEId()
{
	int selectedItem = GetNextItem(-1, LVNI_SELECTED);
	if (selectedItem != -1)
	{
		return GetItemText(selectedItem, eEmpID);
	}
	return L"";
}

/**
* Redraws the selected row in the list view.
*
* This method refreshes the appearance of the currently selected row by reapplying
* the selection and focus state. It also ensures that the selected row is visible
* within the list view and sets focus to the control.
*
*/
bool CuiListEmployeData::RedrawSelectedRow()
{
	int selectedItem = GetNextItem(-1, LVNI_SELECTED);
	if (selectedItem != -1)
	{
		SetItemState(selectedItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		EnsureVisible(selectedItem, FALSE);
		SetFocus();
		return true;
	}
	return false;
}

void CuiListEmployeData::AdjustEmployeeTableColumnWidths()
{
	if (GetSafeHwnd() == nullptr)
		return;

	CRect rect;
	GetClientRect(&rect);

	int columnCount = GetHeaderCtrl()->GetItemCount();
	if (columnCount > 0)
	{
		int columnWidth = rect.Width() / columnCount;
		for (int i = 0; i < columnCount; ++i)
		{
			SetColumnWidth(i, columnWidth);
		}
	}
}
