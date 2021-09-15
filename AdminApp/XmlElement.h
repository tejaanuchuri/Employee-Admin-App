#pragma once
#include<atlstr.h>
#include<vector>
using namespace std;

class XmlElement
{
public:
	CString Name;
	CString Value;
	vector<XmlElement> Child;
public:
	XmlElement();
	XmlElement(CString name, CString value) {
		Name = name;
		Value = value;
	}
};

