#pragma once
#include "afxcmn.h"
#include "dtEmployeeDataHandler.h"
#include "uiListControl.h"

class CuiListEmployeData :public CuiListControl
{
public:
	CuiListEmployeData();
	virtual ~CuiListEmployeData();
public:
	void InitEmployeList();
	void FillEmployeData(mapEmpData& employeeDataMap);
	void InsertEmployeItemData(stEmpData & employeeData);
	bool UpdateSelectedEmployData(stEmpData & employeeData);
	bool DeleteSelectedEmploye();
	CString GetSelectedEId();
	bool RedrawSelectedRow();
	void AdjustEmployeeTableColumnWidths();
private:
	enum eEmpListColTitle {eEmpID,eEmpName,eEmpAge,eColCount};
	map<eEmpListColTitle, CString> m_mapEmpListTitle;
};

