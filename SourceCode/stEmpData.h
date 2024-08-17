#pragma once
#include <afxstr.h>

class stEmpData;

/**
* Comparator for sorting Employee IDs with mixed text and numeric parts.
*
* Compares numeric parts first; if equal or absent, falls back to lexicographical comparison.
* Ensures IDs like "EMP001" are correctly ordered before "EMP010" and "123" before "124".
* Handles any combination of text and numbers, making it adaptable to varying ID formats.
* This approach provides intuitive and logical ID ordering without additional complexity.
*
*/
struct EmployeeIDAlphaNumericCompare
{
	bool operator()(const CString& lhs, const CString& rhs) const
	{
		auto extractNumericPart = [](const CString& str) -> int 
		{
			int start = str.FindOneOf(_T("0123456789"));
			return (start != -1) ? _ttoi(str.Mid(start)) : 0;
		};

		int lhsNum = extractNumericPart(lhs);
		int rhsNum = extractNumericPart(rhs);

		if (lhsNum != rhsNum)
		{
			return lhsNum < rhsNum;
		}
		return lhs.Compare(rhs) < 0;
	}
};

/**
* Typedef for a map with CString keys and stEmpData values, using a custom comparator.
*
* Benefit:
* - Simplifies the declaration and usage of the map throughout the codebase.
* - Enhances readability by providing a clear, descriptive name for the map.
* - Encapsulates the complex map definition, making future modifications easier.
*/
typedef std::map<CString, stEmpData, EmployeeIDAlphaNumericCompare> mapEmpData;

/**
* Class representing employee data.
*
* This class encapsulates the details of an employee, including their ID, name, and age.
* It provides methods to retrieve individual attributes as well as a formatted string
* representation of the employee's data.
*/
class stEmpData
{
public:
	explicit stEmpData(CString strEmpID, CString strName, CString strAge)
		: m_strEmpID(strEmpID), m_strName(strName), m_strAge(strAge) 
	{
	}

	explicit stEmpData()
	{
	}
	
public:
	CString GetName()  { return m_strName; }
	CString GetAge()  { return m_strAge; }
	CString GetId() { return m_strEmpID; }

	CString GetEmpDataAsString() 
	{
		return L" ID:" + m_strEmpID + L", Name:" + m_strName + L", Age:" + m_strAge;
	}

private:
	CString m_strEmpID;
	CString m_strName;
	CString m_strAge;
};