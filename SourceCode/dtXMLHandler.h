#pragma once
#include <atlbase.h>
#include <atlcom.h>
#include <msxml6.h>
#include <afxstr.h>

class CdtXMLHandler
{
protected:
	CdtXMLHandler(LPCTSTR lpszFilePath);
	virtual ~CdtXMLHandler();

	bool LoadXML();
	bool SaveXML();
	CString ReadXML();
	bool DeleteNode(LPCTSTR lpszXPath);
	bool UpdateNode(LPCTSTR lpszXPath, LPCTSTR lpszNewValue);
	bool InsertNode(LPCTSTR lpszXPath, LPCTSTR lpszNewKey, LPCTSTR lpszNewValue);

protected:
	CString m_strFilePath;
	CComPtr<IXMLDOMDocument> m_pXMLDoc;

	CComPtr<IXMLDOMNode> SelectSingleNode(LPCTSTR lpszXPath);
	CComPtr<IXMLDOMNode> SelectSingleNode(LPCTSTR lpszXPath, IXMLDOMNode* pContextNode);
};
