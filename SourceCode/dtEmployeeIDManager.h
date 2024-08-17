#pragma once
#include <afx.h>
#include <fstream>

class CdtEmployeeIDManager
{
public:
	CdtEmployeeIDManager(CString directoryPath);

	CString GetEmpId();
	void SetEmpId(CString newId);
	void UpdateEmpId(CString newId);

private:
	CString m_strIDFilePath;
	CString m_highestID;

	void InitializeIDFile();
	void LoadHighestID();
	void SaveHighestID();
};
