#include "stdafx.h"
#include "dtEmployeeDataHandler.h"
#include <afx.h>

CdtEmployeeDataHandler::CdtEmployeeDataHandler(const CString& lpszFilePath, const CString& FileName)
	: CdtXMLHandler(lpszFilePath + L"\\" + FileName)
{
	m_idManager = std::make_unique<CdtEmployeeIDManager>(lpszFilePath);

	InitializeXMLFileIfNeeded();
	LoadAllEmployees();
}

CdtEmployeeDataHandler::~CdtEmployeeDataHandler() 
{
}

/**
* Ensures the existence and integrity of the XML file containing employee data.
*
* Checks if the XML file exists and attempts to load it. If the file is missing,
* corrupted, or fails to load, the function creates a backup of the corrupted file (if it exists)
* and generates a new XML document. The new XML document is initialized with a root element
* and saved to the file system.
*
*/
void CdtEmployeeDataHandler::InitializeXMLFileIfNeeded()
{
	CFileFind fileFind;
	VARIANT_BOOL loadSuccess = VARIANT_FALSE;
	CComPtr<IXMLDOMElement> pRootElement;

	if (!fileFind.FindFile(m_strFilePath) ||
		m_pXMLDoc->load(CComVariant(m_strFilePath.AllocSysString()), &loadSuccess) != S_OK ||
		m_pXMLDoc->get_documentElement(&pRootElement) != S_OK ||
		pRootElement == nullptr)
	{
		if (fileFind.FindFile(m_strFilePath))
		{
			CString strTimestamp;
			SYSTEMTIME st;
			GetLocalTime(&st);
			strTimestamp.Format(L"_%04d%02d%02d_%02d%02d%02d",st.wYear, st.wMonth, st.wDay,st.wHour, st.wMinute, st.wSecond);
			CString strBackupFilePath = m_strFilePath + strTimestamp + L".bak";

			if (!CopyFile(m_strFilePath, strBackupFilePath, FALSE))
			{
				throw runtime_error("Failed to create backup of the corrupted XML document.");
			}
		}

		if (m_pXMLDoc->loadXML(L"<Employees></Employees>", &loadSuccess) != S_OK || loadSuccess != VARIANT_TRUE)
		{
			throw runtime_error("Failed to create or load new XML document.");
		}
		SaveXML();
	}
}

/**
* Loads all employee data from the XML document into an internal map.
*
* This function clears the existing employee data and retrieves all "Person" nodes from the XML document.
* For each "Person" node, it extracts the ID, Name, and Age values and stores them in an internal map with the ID as the key.
* During this process, it also tracks the highest employee ID encountered.
* After all employees are loaded, the function updates the ID manager with the highest ID found.
*
*/
bool CdtEmployeeDataHandler::LoadAllEmployees()
{
	m_employeeMap.clear();

	CComPtr<IXMLDOMNodeList> pPersonNodes;
	if (m_pXMLDoc->selectNodes(CComBSTR(_T("/Employees/Person")), &pPersonNodes) != S_OK || !pPersonNodes)
	{
		return false;
	}

	long length = 0;
	pPersonNodes->get_length(&length);

	CString highestEID = L"000000";
	for (long i = 0; i < length; ++i)
	{
		CComPtr<IXMLDOMNode> pPersonNode;
		if (pPersonNodes->get_item(i, &pPersonNode) == S_OK && pPersonNode)
		{
			CComPtr<IXMLDOMNode> pIdNode = SelectSingleNode(_T("Id"), pPersonNode);
			CComPtr<IXMLDOMNode> pNameNode = SelectSingleNode(_T("Name"), pPersonNode);
			CComPtr<IXMLDOMNode> pAgeNode = SelectSingleNode(_T("Age"), pPersonNode);

			if (pIdNode && pNameNode && pAgeNode)
			{
				CComBSTR bstrId, bstrName, bstrAge;
				pIdNode->get_text(&bstrId);
				pNameNode->get_text(&bstrName);
				pAgeNode->get_text(&bstrAge);

				CString id(bstrId);
				CString name(bstrName);
				CString age(bstrAge);

				m_employeeMap[id] = stEmpData(id, name, age);

				if (_ttoi(id) > _ttoi(highestEID))
				{
					highestEID = id;
				}
			}
		}
	}

	if (m_employeeMap.size())
	{
		m_idManager->UpdateEmpId(highestEID);
	}
	return true;
}

/**
* Adds a new employee to the XML document and internal map.
*
* The function first checks if the employee ID already exists in the map to prevent duplicates.
* If the ID is unique, it inserts a new "Person" node in the XML document, populating it with
* the employee's ID, Name, and Age. The new employee is then added to the internal map.
* After successfully adding the employee to both the XML document and the map, the updated XML document is saved to disk.
* The employee ID is also updated in the ID manager to reflect the most recent ID.
*
*/
bool CdtEmployeeDataHandler::AddEmployee(stEmpData EmpData)
{
	CString EmpId = EmpData.GetId();

	if (m_employeeMap.find(EmpId) != m_employeeMap.end())
	{
		return false;
	}

	if (!InsertNode(_T("/Employees"), _T("Person"), _T("")) ||
		!InsertNode(_T("/Employees/Person[last()]"), _T("Id"), EmpId) ||
		!InsertNode(_T("/Employees/Person[last()]"), _T("Name"), EmpData.GetName()) ||
		!InsertNode(_T("/Employees/Person[last()]"), _T("Age"), EmpData.GetAge()))
	{
		return false;
	}

	m_employeeMap[EmpId] = EmpData;

	if (!SaveXML())
	{
		return false;
	}
	m_idManager->SetEmpId(EmpId);
	return true;
}

/**
* Updates an existing employee's information in the XML document and internal map.
*
* Checks if the employee ID exists in the map. If found, constructs an XPath to locate
* the corresponding "Person" node in the XML document. The employee's Name and Age
* are then updated in the XML. The internal map is also updated with the new data.
* Finally, the updated XML document is saved to disk.
* Returns true if the update is successful, false if the employee ID is not found or if an error occurs.
*
*/
bool CdtEmployeeDataHandler::UpdateEmployee(stEmpData EmpData)
{
	auto empID = EmpData.GetId();
	if (m_employeeMap.find(empID) == m_employeeMap.end())
	{
		return false;
	}

	CString xpath;
	xpath.Format(_T("/Employees/Person[Id='%s']"), empID);

	if (!UpdateNode(xpath + _T("/Name"), EmpData.GetName()) ||
		!UpdateNode(xpath + _T("/Age"), EmpData.GetAge()))
	{
		return false;
	}

	m_employeeMap[empID] = EmpData;

	return SaveXML();
}

/**
* Deletes an employee from the XML document and internal map.
*
* Checks if the employee ID exists in the map. If found, constructs an XPath to locate
* the corresponding "Person" node in the XML document. The function then deletes this node
* from the XML and removes the employee from the internal map.
* Finally, the updated XML document is saved to disk.
* Returns true if the employee is successfully deleted, false if the employee ID is not found or if an error occurs.
*
*/
bool CdtEmployeeDataHandler::DeleteEmployee(CString EmpID)
{
	if (m_employeeMap.find(EmpID) == m_employeeMap.end())
	{
		return false;
	}

	CString xpath;
	xpath.Format(_T("/Employees/Person[Id='%s']"), EmpID);

	if (!DeleteNode(xpath))
	{
		return false;
	}

	m_employeeMap.erase(EmpID);

	return SaveXML();
}

const mapEmpData& CdtEmployeeDataHandler::GetAllEmployeeData()
{
	return m_employeeMap;
}

const stEmpData CdtEmployeeDataHandler::GetEmployeeDataFor(CString lpszId)
{
	auto it = m_employeeMap.find(lpszId);
	if (it != m_employeeMap.end())
	{
		return it->second;
	}
	return stEmpData();
}

/**
* Retrieves the next unique employee ID.
*
* This function does not generate a new employee ID on its own. Instead, it delegates
* the responsibility to the ID manager by calling `GetEmpId()` on `m_idManager`.
* The ID manager is responsible for managing and providing the next unique employee ID,
* ensuring that no duplicate IDs are issued.
*
*/
const CString CdtEmployeeDataHandler::GenerateEmployeeID()
{
	return m_idManager->GetEmpId();
}
