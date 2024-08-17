#pragma once
#include "dtXMLHandler.h"
#include "dtEmployeeIDManager.h"

class CdtEmployeeDataHandler : public CdtXMLHandler
{
public:
	CdtEmployeeDataHandler(const CString& lpszFilePath, const CString& FileName);
	~CdtEmployeeDataHandler();

	bool AddEmployee(stEmpData EmpData);
	bool UpdateEmployee(stEmpData EmpData);
	bool DeleteEmployee(CString EmpID);
	bool LoadAllEmployees();

	const mapEmpData& GetAllEmployeeData();
	const stEmpData GetEmployeeDataFor(CString lpszId);
	const CString GenerateEmployeeID();
private:
	void InitializeXMLFileIfNeeded();
	mapEmpData m_employeeMap;
	std::unique_ptr<CdtEmployeeIDManager> m_idManager;
};
