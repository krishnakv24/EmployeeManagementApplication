#include "stdafx.h"
#include "dtXMLHandler.h"

/**
* Initializes the XML handler with the specified file path.
*
* This constructor sets the file path and prepares the XML handler for processing by:
*
* Initializing the COM library.
* Creating an instance of the XML DOMDocument object for handling XML data.
* Setting the XML document to load synchronously.
*
* Throws an exception if there is a failure in initializing the COM library
* or creating the XML DOM instance.
*
*/
CdtXMLHandler::CdtXMLHandler(LPCTSTR lpszFilePath) : m_strFilePath(lpszFilePath)
{
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		throw std::runtime_error("Failed to initialize COM library.");
	}

	hr = m_pXMLDoc.CoCreateInstance(__uuidof(DOMDocument60));
	if (FAILED(hr))
	{
		CoUninitialize();
		throw std::runtime_error("Failed to create XML DOM instance.");
	}

	m_pXMLDoc->put_async(VARIANT_FALSE);
}

/**
* Destructor for the CdtXMLHandler class.
*
* Releases the XML document object if it exists and uninitializes the COM library.
* Ensures that any resources allocated for XML processing are properly cleaned up.
*/
CdtXMLHandler::~CdtXMLHandler()
{
	if (m_pXMLDoc)
	{
		m_pXMLDoc.Release();
	}
	CoUninitialize();
}

/**
* Loads the XML document from the specified file path.
*
* Attempts to load the XML document using the file path stored in the handler.
* Returns true if the document is successfully loaded, false otherwise.
*
*/
bool CdtXMLHandler::LoadXML()
{
	VARIANT_BOOL loadSuccess;
	HRESULT hr = m_pXMLDoc->load(CComVariant(m_strFilePath), &loadSuccess);
	return SUCCEEDED(hr) && loadSuccess == VARIANT_TRUE;
}

/**
* Saves the current XML document to the specified file path.
*
* Attempts to save the XML document to the file path stored in the handler.
* Returns true if the document is successfully saved, false otherwise.
*
*/
bool CdtXMLHandler::SaveXML()
{
	HRESULT hr = m_pXMLDoc->save(CComVariant(m_strFilePath));
	return SUCCEEDED(hr);
}

/**
* Reads the entire XML content as a string.
*
* Retrieves the XML content from the document and returns it as a CString.
*
*/
CString CdtXMLHandler::ReadXML()
{
	CComBSTR bstrXML;
	m_pXMLDoc->get_xml(&bstrXML);
	return CString(bstrXML);
}

/**
* Deletes a specific XML node based on the given XPath.
*
* Attempts to find and delete a node in the XML document using the provided XPath.
* If the node is found and successfully deleted, the method returns true.
* Returns false if the node is not found, or if the deletion fails.
*
*/
bool CdtXMLHandler::DeleteNode(LPCTSTR lpszXPath)
{
	CComPtr<IXMLDOMNode> pNode = SelectSingleNode(lpszXPath);

	if (!pNode)
		return false;

	CComPtr<IXMLDOMNode> pParentNode;
	pNode->get_parentNode(&pParentNode);

	if (!pParentNode)
		return false;

	CComPtr<IXMLDOMNode> pRemovedNode;
	HRESULT hr = pParentNode->removeChild(pNode, &pRemovedNode);

	return SUCCEEDED(hr) && pRemovedNode != NULL;
}

/**
* Updates the value of a specific XML node based on the given XPath.
*
* Attempts to find a node in the XML document using the provided XPath and updates its value.
* If the node has existing text, it is replaced with the new value. If the node does not have
* any existing text, the new value is appended as a child text node.
* Returns true if the node is successfully updated, false otherwise.
*
*/
bool CdtXMLHandler::UpdateNode(LPCTSTR lpszXPath, LPCTSTR lpszNewValue)
{
	CComPtr<IXMLDOMNode> pNode = SelectSingleNode(lpszXPath);
	if (!pNode)
		return false;

	CComPtr<IXMLDOMNode> pOldChild;
	HRESULT hr = pNode->get_firstChild(&pOldChild);

	if (FAILED(hr) || !pOldChild)
	{
		CComPtr<IXMLDOMText> pTextNode;
		hr = m_pXMLDoc->createTextNode(CComBSTR(lpszNewValue), &pTextNode);
		if (SUCCEEDED(hr))
		{
			CComPtr<IXMLDOMNode> pAppendedChild;
			hr = pNode->appendChild(pTextNode, &pAppendedChild);
			return SUCCEEDED(hr) && pAppendedChild != NULL;
		}
		return false;
	}

	CComPtr<IXMLDOMText> pTextNode;
	hr = m_pXMLDoc->createTextNode(CComBSTR(lpszNewValue), &pTextNode);
	if (SUCCEEDED(hr))
	{
		CComPtr<IXMLDOMNode> pReplacedChild;
		hr = pNode->replaceChild(pTextNode, pOldChild, &pReplacedChild);
		return SUCCEEDED(hr) && pReplacedChild != NULL;
	}

	return false;
}

/**
* Inserts a new XML node with the specified key and value at the location identified by the given XPath.
*
* Attempts to find a node in the XML document using the provided XPath. If found, a new element is created
* with the specified key and value, and it is appended as a child to the found node.
* Returns true if the new node is successfully inserted, false otherwise.
*
*/
bool CdtXMLHandler::InsertNode(LPCTSTR lpszXPath, LPCTSTR lpszNewKey, LPCTSTR lpszNewValue)
{
	CComPtr<IXMLDOMNode> pNode = SelectSingleNode(lpszXPath);

	if (!pNode)
		return false;

	CComPtr<IXMLDOMElement> pNewElement;
	HRESULT hr = m_pXMLDoc->createElement(CComBSTR(lpszNewKey), &pNewElement);

	if (SUCCEEDED(hr) && pNewElement)
	{
		pNewElement->put_text(CComBSTR(lpszNewValue));
		hr = pNode->appendChild(pNewElement, NULL);
		return SUCCEEDED(hr);
	}

	return false;
}

/**
* Selects a single XML node based on the specified XPath.
*
* Searches the XML document using the provided XPath expression and returns the first matching node.
* If no matching node is found, returns a null pointer.
*
*/
CComPtr<IXMLDOMNode> CdtXMLHandler::SelectSingleNode(LPCTSTR lpszXPath)
{
	CComPtr<IXMLDOMNode> pNode;
	m_pXMLDoc->selectSingleNode(CComBSTR(lpszXPath), &pNode);
	return pNode;
}

/**
* Selects a single XML node based on the specified XPath, with an optional context node.
*
* Searches for a node using the provided XPath expression. If a context node is provided,
* the search is performed relative to that node. If no context node is provided, the search
* is performed on the entire XML document. Returns the first matching node, or null if no match is found.
*
*/
CComPtr<IXMLDOMNode> CdtXMLHandler::SelectSingleNode(LPCTSTR lpszXPath, IXMLDOMNode* pContextNode)
{
	CComPtr<IXMLDOMNode> pNode;
	CComPtr<IXMLDOMNode> pContext(pContextNode);
	if (pContext)
	{
		pContext->selectSingleNode(CComBSTR(lpszXPath), &pNode);
	}
	else
	{
		m_pXMLDoc->selectSingleNode(CComBSTR(lpszXPath), &pNode);
	}
	return pNode;
}
