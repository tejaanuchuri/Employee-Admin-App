#include "CXml.h"
#include <afxwin.h>
IMPLEMENT_DYNAMIC(CXml, CStdioFile)
CXml::CXml()
{
}

CXml::~CXml()
{
}



void CXml::Export(vector<Employee> employeerecords)
{
	CXml file;
	file.Open(L"Emp.xml", CXml::modeCreate | CXml::modeWrite);

	file.WriteString(StringToStartTag(L"AdminApp"));

	for (unsigned int EmpIndex = 0; EmpIndex < employeerecords.size(); EmpIndex++) {
		Employee Record = employeerecords[EmpIndex];
		file.WriteString(StringToStartTag(L"Employee"));
		file.WriteString(ConvertXmlFormat(L"Id", Record.Id));
		file.WriteString(ConvertXmlFormat(L"HireDate", Record.HireDate));
		file.WriteString(ConvertXmlFormat(L"YearsofExperience", Record.YearsOfExperience));
		file.WriteString(ConvertXmlFormat(L"Title", Record.Title));
		file.WriteString(ConvertXmlFormat(L"Age", Record.Age));
		file.WriteString(ConvertXmlFormat(L"FirstName", Record.FirstName));
		file.WriteString(ConvertXmlFormat(L"LastName", Record.LastName));
		file.WriteString(ConvertXmlFormat(L"Gender", Record.Gender));
		file.WriteString(ConvertXmlFormat(L"PhoneNumber", Record.MobileNumber));
		file.WriteString(ConvertXmlFormat(L"Email", Record.Email));
		file.WriteString(ConvertXmlFormat(L"DateofBirth", Record.DateOfBirth));
		file.WriteString(ConvertXmlFormat(L"Address", Record.Address));
		file.WriteString(ConvertXmlFormat(L"JobTitle", Record.JobTitle));
		file.WriteString(ConvertXmlFormat(L"Salary", Record.Salary));
		file.WriteString(StringToEndTag(L"Employee"));
	}
	file.WriteString(StringToEndTag(L"AdminApp"));
	return;
}
vector<Employee> CXml::Import(CString filepath)
{
	vector<Employee> employeeRecords;
	Employee record;
	stack<CString> xmlElements;
	CXml file;
	file.Open(filepath, CXml::modeRead | CXml::typeText);
	CString singleLine;
	CString XmlElement;
	CString TagName;
	while (file.ReadString(singleLine))
	{
		if (IsEmployeeStartTag(singleLine)) {
			while (file.ReadString(singleLine)) {
				if (IsEmployeeEndTag(singleLine)) {
					employeeRecords.push_back(record);
					break;
				}
				else {
					switch (GetXmlElement(singleLine))
					{
					case Id:
						record.Id = GetRecordFieldValue(singleLine);
						break;
					case HireDate:
						record.HireDate = GetRecordFieldValue(singleLine);
						break;
					case YearOfExperience:
						record.YearsOfExperience = GetRecordFieldValue(singleLine);
						break;
					case Title:
						record.Title = GetRecordFieldValue(singleLine);
						break;
					case Age:
						record.Age = GetRecordFieldValue(singleLine);
						break;
					case FirstName:
						record.FirstName = GetRecordFieldValue(singleLine);
						break;
					case LastName:
						record.LastName = GetRecordFieldValue(singleLine);
						break;
					case Gender:
						record.Gender = GetRecordFieldValue(singleLine);
						break;
					case PhoneNumber:
						record.MobileNumber = GetRecordFieldValue(singleLine);
						break;
					case Email:
						record.Email = GetRecordFieldValue(singleLine);
						break;
					case DateOfBirth:
						record.DateOfBirth = GetRecordFieldValue(singleLine);
						break;
					case Address:
						record.Address = GetRecordFieldValue(singleLine);
						break;
					case JobTitle:
						record.JobTitle = GetRecordFieldValue(singleLine);
						break;
					case Salary:
						record.Salary = GetRecordFieldValue(singleLine);
						break;
					default:
						break;
					}
				}

			}
		}
	}
	file.Close();
	return employeeRecords;
}
bool CXml::CompareTwoStrings(CString p, CString q)
{
	if (p.GetLength() != q.GetLength())
		return false;
	for (int i = 0; i < p.GetLength(); i++) {
		if (p[i] != q[i]) {
			return false;
		}
	}
	return true;
}
CString CXml::GetTagName(CString XmlElement)
{
	CString TagName;
	if (IsStartTag(XmlElement)) {
		for (int i = 1; i < XmlElement.GetLength() - 1; i++) {
			TagName.AppendChar(XmlElement[i]);
		}
	}
	else if (IsEndTag(XmlElement)) {
		for (int i = 2; i < XmlElement.GetLength() - 1; i++) {
			TagName.AppendChar(XmlElement[i]);
		}
	}
	CString x = TagName;
	return TagName;
}
CString CXml::GetXmlTagName(CString s)
{
	vector<CString> XmlElements = StringSplitIntoXmlElements(s);

	return GetTagName(XmlElements[0]);
}
CString CXml::GetRecordFieldValue(CString s)
{
	vector<CString> XmlElements = StringSplitIntoXmlElements(s);

	return XmlElements[1];
}
bool CXml::IsEmployeeStartTag(CString singleLine)
{
	CString TagName = GetXmlTagName(singleLine);
	if (TagName == L"Employee") {
		return true;
	}
	return false;
}
RecordField CXml::GetXmlElement(CString singleLine)
{
	CString TagName = GetXmlTagName(singleLine);
	if (TagName == L"Id") {
		return Id;
	}
	else if (TagName == L"HireDate") {
		return HireDate;
	}
	else if (TagName == L"YearsofExperience") {
		return YearOfExperience;
	}
	else if (TagName == L"Title") {
		return Title;
	}
	else if (TagName == L"Age") {
		return Age;
	}
	else if (TagName == L"FirstName") {
		return FirstName;
	}
	else if (TagName == L"LastName") {
		return LastName;
	}
	else if (TagName == L"Gender") {
		return Gender;
	}
	else if (TagName == L"PhoneNumber") {
		return PhoneNumber;
	}
	else if (TagName == L"Email") {
		return Email;
	}
	else if (TagName == L"DateofBirth") {
		return DateOfBirth;
	}
	else if (TagName == L"Address") {
		return Address;
	}
	else if (TagName == L"JobTitle") {
		return JobTitle;
	}
	else if (TagName == L"Salary") {
		return Salary;
	}
	return Nothing;
}
bool CXml::IsEmployeeEndTag(CString singleLine)
{
	CString TagName = GetXmlTagName(singleLine);
	if (TagName == L"Employee") {
		return true;
	}
	return false;
}
CString CXml::RemoveWhiteSpaces(CString s)
{
	s.TrimRight();
	s.TrimLeft();
	return s;
}
int CXml::GetXmlElementType(CString singleline)
{
	vector<CString> XmlElements = StringSplitIntoXmlElements(singleline);
	if (XmlElements.size() == 1) {
		if (IsStartTag(XmlElements[0])) {
			return 0;
		}
		else if (IsEndTag(XmlElements[0])) {
			return 1;
		}
	}
	else if (XmlElements.size() == 3) {
		return 2;
	}
	return -1;
}

vector<CString> CXml::StringSplitIntoXmlElements(CString s)
{
	CString temp;
	vector<CString> XmlElements;
	for (int i = 0; i < s.GetLength(); i++) {
		if (s[i] == '<') {
			if (temp.IsEmpty()) {
				temp.AppendChar(s[i]);
			}
			else {
				XmlElements.push_back(temp);
				temp.Empty();
				temp.AppendChar(s[i]);
			}
		}
		else if (s[i] != '>') {
			temp.AppendChar(s[i]);
		}
		else if ((s[i] == '>') && (temp[0] == '<')) {
			temp.AppendChar(s[i]);
			XmlElements.push_back(temp);
			temp.Empty();
		}
		else if ((s[i] == '>') && (temp[0] != '<')) {
			XmlElements.push_back(temp);
			temp.Empty();
		}
	}
	s.Empty();

	return XmlElements;
}
/*
bool CXml::isvalidxml(vector<CString>& v)
{
	stack<CString> s;
	for (unsigned int i = 0; i < v.size(); i++) {
		if (isstarttag(v[i])) {
			s.push(stagname(v[i]));
			//MessageBox(stagname(v[i]));
		}
		else if (isendtag(v[i])) {
			CString temp = s.top();
			if ((ismatchingtagname(temp, etagname(v[i])))) {
				s.pop();
			}
			//MessageBox(etagname(v[i]));
		}
	}
	return s.empty();
}

bool CXml::isstarttag(CString s)
{
	int n = s.GetLength();
	for (int i = 0; i < s.GetLength(); i++) {
		if (s[0] != '<') {
			return false;
		}
		if (s[1] == '/') {
			return false;
		}
		if (s[n - 1] != '>') {
			return false;
		}
	}
	return true;
}

bool CXml::isendtag(CString s)
{
	int l = s.GetLength();
	if (l <= 2)
		return false;
	if (s[0] != '<')
		return false;
	if (s[1] != '/')
		return false;
	if (s[l - 1] != '>')
		return false;
	return true;
}

CString CXml::stagname(CString s)
{
	CString temp;
	temp.Empty();
	for (int i = 1; i < s.GetLength() - 1; i++) {
		temp.AppendChar(s[i]);
	}
	return temp;
}

CString CXml::etagname(CString s)
{
	CString temp;
	temp.Empty();
	for (int i = 2; i < s.GetLength() - 1; i++) {
		temp.AppendChar(s[i]);
	}
	return temp;
}

bool CXml::ismatchingtagname(CString s, CString d)
{
	if (s.GetLength() >= d.GetLength()) {
		for (int i = 0; i < d.GetLength(); i++) {
			if (s[i] != d[i]) {
				return false;
			}
		}
	}
	else {
		return false;
	}
	return true;
}

pair< vector<vector<pair<CString, CString>>>, int> CXml::xmlimport(CString filepath)
{
	CXml file;
	file.Open(filepath, CXml::modeRead | CXml::typeText);
	CString one_line_string;
	CString Read_entire_file;

	vector<CString> out;
	vector<pair<CString, CString>> res;
	vector< vector<pair<CString, CString>>> emp;
	one_line_string.Empty();
	out.clear();
	Read_entire_file.Empty();
	int flag = 1;
	int check = 0;
	while (file.ReadString(one_line_string))
	{
		removespaces(one_line_string);
		Read_entire_file += one_line_string;
	}

	file.Close();
	vector<CString> vector_of_elements = xmlelements(Read_entire_file);
	flag = 0;
	for (vector<CString>::iterator i = vector_of_elements.begin(); i != vector_of_elements.end(); i++) {
		*i = removespaces(*i);
		CString t = *i;

		for (int j = 0; j < t.GetLength(); j++) {
			if (t[j] != ' ') {
				flag = 1;
			}
		}
		if (flag == 1) {
			out.push_back(t);
			flag = 0;
		}
	}
	vector_of_elements.clear();
	for (vector<CString>::iterator k = out.begin(); k != out.end(); k++) {
		*k = removespaces(*k);
	}
	if (!isvalidxml(out)) {
		check = 0;
	}
	else {
		check = 1;
		stack<CString> s;
		res.clear();
		emp.clear();
		CString temp_value;
		CString temp;
		temp.Empty();
		temp_value.Empty();
		for (unsigned int i = 0; i < out.size(); i++) {
			if (isstarttag(out[i])) {
				s.push(stagname(out[i]));
			}
			else if (isendtag(out[i])) {
				temp = s.top();
				if ((ismatchingtagname(temp, etagname(out[i]))) && !(temp_value.IsEmpty())) {
					res.push_back(make_pair(etagname(out[i]), temp_value));
					temp.Empty();
					temp_value.Empty();
					s.pop();
				}
				else if (temp == etagname(out[i])) {
					emp.push_back(res);
					res.clear();
				}
			}
			else {
				temp_value.Append(out[i]);
			}
		}
	}
	return make_pair(emp, check);
	//return vector<vector<pair<CString, CString>>>();
}
*/

bool CXml::IsStartTag(CString s)
{
	int n = s.GetLength();
	for (int i = 0; i < s.GetLength(); i++) {
		if (s[0] != '<') {
			return false;
		}
		if (s[1] == '/') {
			return false;
		}
		if (s[n - 1] != '>') {
			return false;
		}
	}
	return true;

}
bool CXml::IsEndTag(CString s)
{
	int l = s.GetLength();
	if (l <= 2)
		return false;
	if (s[0] != '<')
		return false;
	if (s[1] != '/')
		return false;
	if (s[l - 1] != '>')
		return false;
	return true;
}
CString CXml::StringToStartTag(CString s)
{
	return OPENSTARTTAG + s + CLOSETAGNEWLINE;
}

CString CXml::StringToEndTag(CString s)
{
	return OPENENDTAG + s + CLOSETAGNEWLINE;
}

CString CXml::ConvertXmlFormat(CString s, CString v)
{
	return StartTag(s) + v + EndTag(s);
}

CString CXml::StartTag(CString s)
{
	return OPENSTARTTAG + s + CLOSETAGSYMBOL;
}

CString CXml::EndTag(CString s)
{
	return OPENENDTAG + s + CLOSETAGNEWLINE;
}

