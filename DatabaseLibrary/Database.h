#pragma once
#include<vector>
#include"../AdminApp/Employee.h"
using namespace std;
class Database
{
public:
	Database();
public:
	void InsertRecord(Employee record);
	void UpdateRecord(Employee record);
	void DeleteRecord(CString id);
	CString GetNextAutoNumber();
	vector<Employee> FetchAllRecords();
};

