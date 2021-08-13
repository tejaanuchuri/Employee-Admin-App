#pragma once
#include <afx.h>
#include<vector>
#include<stack>
#include "Employee.h"
using namespace std;

#define OPENSTARTTAG _T("<")
#define CLOSETAGSYMBOL _T(">")
#define CLOSETAGNEWLINE _T(">\n")
#define OPENENDTAG _T("</")
enum RecordField
{
	Id, HireDate, YearOfExperience, Title, Age, FirstName, LastName, Gender, PhoneNumber, Email, DateOfBirth, Address, JobTitle, Salary, Nothing
};
class CXml :public CStdioFile
{
	DECLARE_DYNAMIC(CXml)
public:
	CXml();
	virtual ~CXml();
public:
	void Export(vector<Employee> employeerecords);
	vector<Employee> Import(CString filepath);
	CString StringToStartTag(CString s);
	CString StringToEndTag(CString s);
	CString ConvertXmlFormat(CString s, CString v);
	CString StartTag(CString s);
	CString EndTag(CString s);
	vector<CString> StringSplitIntoXmlElements(CString s);
	CString RemoveWhiteSpaces(CString s);
	int GetXmlElementType(CString singleline);
	bool IsStartTag(CString s);
	bool IsEndTag(CString s);
	bool CompareTwoStrings(CString p, CString q);
	CString GetTagName(CString XmlElement);
	CString GetXmlTagName(CString s);
	CString GetRecordFieldValue(CString s);
	bool IsEmployeeStartTag(CString singleLine);
	RecordField GetXmlElement(CString singleLine);
	bool IsEmployeeEndTag(CString singleLine);
};

