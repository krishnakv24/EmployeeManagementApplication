#include "stdafx.h"
#include "dtEmployeeIDManager.h"

/*
* This class is crucial for ensuring that each employee is assigned a unique and sequential ID.
* The IDs are stored in a binary file to persist across sessions, preventing any duplication.
*
* Importance:
*
* 1. Unique Identification:
*    - The class ensures that every employee is assigned a unique ID, which is vital for tracking,
*      referencing, and managing employee records accurately within the system.
*
* 2. Sequential Assignment:
*    - Employee IDs are assigned in a sequential order, which simplifies database indexing and
*      allows for easy identification of the order of employee creation.
*
* 3. Persistence Across Sessions:
*    - By storing the highest ID in a binary file, the system guarantees that no IDs are reused,
*      even if the application is restarted, thereby maintaining consistency and integrity of employee records.
*
* 4. Prevention of ID Conflicts:
*    - The use of methods like `UpdateEmpId` ensures that the highest ID is only updated when necessary,
*      preventing accidental overwrites and ensuring that the ID sequence remains intact and reliable.
*
* 5. Recovery and Initialization:
*    - The class handles scenarios where the ID file might be missing or corrupted by reinitializing
*      the ID sequence, thus preventing the creation of duplicate or conflicting IDs in the system.
*/

CdtEmployeeIDManager::CdtEmployeeIDManager(CString directoryPath) :
	m_strIDFilePath(directoryPath + L"\\idmax.dat"),
	m_highestID(L"000000")
{
	InitializeIDFile();
}

CString CdtEmployeeIDManager::GetEmpId()
{
	CString tempHighestID;
	LoadHighestID();

	int intID = _ttoi(m_highestID);
	intID++;
	tempHighestID.Format(_T("%06d"), intID);

	return tempHighestID;
}

void CdtEmployeeIDManager::SetEmpId(CString newId)
{
	m_highestID = newId;
	SaveHighestID();
}

void CdtEmployeeIDManager::UpdateEmpId(CString newId)
{
	LoadHighestID();

	int newIdInt = _ttoi(newId);
	int highestIdInt = _ttoi(m_highestID);

	if (newIdInt > highestIdInt)
	{
		m_highestID = newId;
		SaveHighestID();
	}
}

void CdtEmployeeIDManager::InitializeIDFile()
{
	ifstream file(m_strIDFilePath, ios::binary);
	if (!file.is_open())
	{
		m_highestID = L"000000";
		SaveHighestID();
	}
}

void CdtEmployeeIDManager::LoadHighestID()
{
	ifstream file(m_strIDFilePath, ios::binary);
	if (file.is_open())
	{
		char buffer[7] = { 0 };
		file.read(buffer, 6);
		m_highestID = CString(buffer);
		file.close();
	}
	else
	{
		m_highestID = L"000000";
	}
}

void CdtEmployeeIDManager::SaveHighestID()
{
	ofstream file(m_strIDFilePath, ios::binary | ios::trunc);
	if (file.is_open())
	{
		CT2A asciiID(m_highestID); 
		file.write(asciiID, 6);     
		file.close();
	}
}
