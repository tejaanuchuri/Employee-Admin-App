// Insert.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "Insert.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include "AdminAppDlg.h"
#include "Database.h"
#include "Employee.h"
#include <regex>
#include <iostream>
using namespace std;
// Insert dialog

IMPLEMENT_DYNAMIC(Insert, CDialogEx)

Insert::Insert(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INSERT, pParent)
	, Title(_T(""))
	, FirstName(_T(""))
	, LastName(_T(""))
	, Gender(_T(""))
	, Email(_T(""))
	, PhoneNumber(_T(""))
	, DateOfBirth(COleDateTime::GetCurrentTime())
	, Address(_T(""))
	, HireDate(COleDateTime::GetCurrentTime())
	, JobTitle(_T(""))
	, Salary(_T(""))
	, Id(_T(""))
	, Age(_T(""))
	, YearsOfExperience(_T(""))
{
}

Insert::~Insert()
{
}

void Insert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_I_TITLE, TitleControl);
	DDX_CBString(pDX, IDC_COMBO_I_TITLE, Title);
	DDX_Control(pDX, IDC_EDIT_I_FIRSTNAME, FirstNameControl);
	DDX_Text(pDX, IDC_EDIT_I_FIRSTNAME, FirstName);
	DDX_Control(pDX, IDC_EDIT_LASTNAME, LastNameControl);
	DDX_Text(pDX, IDC_EDIT_LASTNAME, LastName);
	DDX_Control(pDX, IDC_COMBO_GENDER, GenderControl);
	DDX_CBString(pDX, IDC_COMBO_GENDER, Gender);
	DDX_Control(pDX, IDC_EDIT_EMAIL, EmailControl);
	DDX_Text(pDX, IDC_EDIT_EMAIL, Email);
	DDX_Control(pDX, IDC_EDIT_PHONE_NUMBER, PhoneNumberControl);
	DDX_Text(pDX, IDC_EDIT_PHONE_NUMBER, PhoneNumber);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATEOFBIRTH, DOBControl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATEOFBIRTH, DateOfBirth);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, AddressControl);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, Address);
	DDX_Control(pDX, IDC_DATETIMEPICKER_HIREDATE, HiredateControl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_HIREDATE, HireDate);
	DDX_Control(pDX, IDC_COMBO_JOBTITLE, JobTitleControl);
	DDX_CBString(pDX, IDC_COMBO_JOBTITLE, JobTitle);
	DDX_Control(pDX, IDC_EDIT_SALARY, SalaryControl);
	DDX_Text(pDX, IDC_EDIT_SALARY, Salary);
	DDX_Text(pDX, IDC_EDIT_EMPLOYEEID, Id);
	DDX_Text(pDX, IDC_EDIT_AGE, Age);
	DDX_Text(pDX, IDC_EDIT_YEARSOFEXP, YearsOfExperience);
	DDX_Control(pDX, IDC_BUTTON_INSERT, SubmitBtnCtrl);
	DDX_Control(pDX, IDC_STATIC_FIRSTNAMEREQUIRED, FirstNameError);
	DDX_Control(pDX, IDC_EDIT_AGE, AgeControl);
	DDX_Control(pDX, IDC_STATIC_PHONENUMBERREQUIRED, PhoneNumberValidateControl);
	DDX_Control(pDX, IDC_STATIC_TITLEREQUIRED, TitleShowErrorControl);
	DDX_Control(pDX, IDC_STATIC_LASTNAME, LastNameShowErrorControl);
	DDX_Control(pDX, IDC_STATIC_GENDERREQUIRED, GenderShowErrorControl);
	DDX_Control(pDX, IDC_STATIC_EMAILREQUIRED, EmailShowErrorControl);
	DDX_Control(pDX, IDC_STATIC_ADDRESSREQUIRED, AddressShowErrorControl);
	DDX_Control(pDX, IDC_STATIC_JOBTITLEREQUIRED, JobTitleShowErrorControl);
	DDX_Control(pDX, IDC_STATIC_SALARYREQUIRED, SalaryShowErrorControl);
	DDX_Control(pDX, IDC_STATIC_TITLEEX, TitleExControl);
	DDX_Control(pDX, IDC_STATIC_FIRSTNAMEEX, FirstNameExControl);
	DDX_Control(pDX, IDC_STATIC_LASTNAMEEXX, LastNameExControl);
	DDX_Control(pDX, IDC_STATIC_GENDEREX, GenderExControl);
	DDX_Control(pDX, IDC_STATIC_EMAILEX, EmailExControl);
	DDX_Control(pDX, IDC_STATIC_PHONENUMBEREX, PhoneNumberExControl);
	DDX_Control(pDX, IDC_STATIC_ADDRESSEX, AddressExControl);
	DDX_Control(pDX, IDC_STATIC_JOBTITLEEX, JobTitleExControl);
	DDX_Control(pDX, IDC_STATIC_SALARYEX, SalaryExControl);
}


BEGIN_MESSAGE_MAP(Insert, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &Insert::OnBnClickedButtonInsert)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_I_FIRSTNAME, &Insert::OnEnChangeEditIFirstname)
	ON_CBN_EDITCHANGE(IDC_COMBO_I_TITLE, &Insert::OnCbnEditchangeComboITitle)
	ON_EN_CHANGE(IDC_EDIT_LASTNAME, &Insert::OnEnChangeEditLastname)
	ON_CBN_EDITCHANGE(IDC_COMBO_GENDER, &Insert::OnCbnEditchangeComboGender)
	ON_EN_CHANGE(IDC_EDIT_EMAIL, &Insert::OnEnChangeEditEmail)
	ON_EN_CHANGE(IDC_EDIT_PHONE_NUMBER, &Insert::OnEnChangeEditPhoneNumber)
	ON_EN_CHANGE(IDC_EDIT_ADDRESS, &Insert::OnEnChangeEditAddress)
	ON_CBN_EDITCHANGE(IDC_COMBO_JOBTITLE, &Insert::OnCbnEditchangeComboJobtitle)
	ON_EN_CHANGE(IDC_EDIT_SALARY, &Insert::OnEnChangeEditSalary)
	ON_CBN_SELCHANGE(IDC_COMBO_I_TITLE, &Insert::OnCbnSelchangeComboITitle)
	ON_CBN_SELCHANGE(IDC_COMBO_GENDER, &Insert::OnCbnSelchangeComboGender)
	ON_CBN_SELCHANGE(IDC_COMBO_JOBTITLE, &Insert::OnCbnSelchangeComboJobtitle)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DATEOFBIRTH, &Insert::OnDtnDatetimechangeDatetimepickerDateofbirth)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_HIREDATE, &Insert::OnDtnDatetimechangeDatetimepickerHiredate)
	ON_EN_UPDATE(IDC_EDIT_EMAIL, &Insert::OnEnUpdateEditEmail)
END_MESSAGE_MAP()


// Insert message handlers

BOOL Insert::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (Id.IsEmpty()) {
		GetDlgItem(IDC_BUTTON_INSERT)->SetWindowTextW(_T("Insert"));
		TitleControl.SetWindowText(_T(""));
		FirstNameControl.SetWindowText(_T(""));
		LastNameControl.SetWindowText(_T(""));
		PhoneNumberControl.SetWindowText(_T(""));
		EmailControl.SetWindowText(_T(""));
		AddressControl.SetWindowText(_T(""));
		JobTitleControl.SetWindowText(_T(""));
		SalaryControl.SetWindowText(_T(""));
		GenderControl.SetWindowText(_T(""));
	}
	else {
		GetDlgItem(IDC_BUTTON_INSERT)->SetWindowTextW(_T("Update"));
		GetDlgItem(IDC_STATIC_EMPLOYEEIDTEXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_EMPLOYEEID)->ShowWindow(SW_SHOW);
	}

	GetDlgItem(IDC_STATIC_FIRSTNAMEREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_FIRSTNAMEEX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TITLEREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TITLEEX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_LASTNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_LASTNAMEEXX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_GENDERREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_GENDEREX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EMAILREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EMAILEX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PHONENUMBERREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PHONENUMBEREX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ADDRESSREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ADDRESSEX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_JOBTITLEREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_JOBTITLEEX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SALARYREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SALARYEX)->ShowWindow(SW_HIDE);
	return TRUE;
}

void Insert::OnBnClickedButtonInsert()
{
	UpdateData(TRUE); // flow direction database <- ui
	Database database;
	Employee record;
	record.Id = Id;
	record.HireDate = ConvertDateTimeToString(HireDate);
	record.YearsOfExperience = YearsOfExperience;
	record.Title = Title;
	record.Age = Age;
	record.FirstName = FirstName;
	record.LastName = LastName;
	record.Gender = Gender;
	record.MobileNumber = PhoneNumber;
	record.Email = Email;
	record.Address = Address;
	record.JobTitle = JobTitle;
	record.Salary = Salary;
	record.DateOfBirth = ConvertDateTimeToString(DateOfBirth);

	if (!TitleExControl.IsWindowVisible() && !TitleShowErrorControl.IsWindowVisible() && !Title.IsEmpty() && !FirstNameExControl.IsWindowVisible() && !FirstNameError.IsWindowVisible() && !FirstName.IsEmpty() && !LastNameExControl.IsWindowVisible() && !LastNameShowErrorControl.IsWindowVisible() && !LastName.IsEmpty() && !GenderExControl.IsWindowVisible() && !GenderShowErrorControl.IsWindowVisible() && !Gender.IsEmpty() && !EmailExControl.IsWindowVisible() && !EmailShowErrorControl.IsWindowVisible() && !Email.IsEmpty() && !PhoneNumberExControl.IsWindowVisible() && !PhoneNumberValidateControl.IsWindowVisible() && !PhoneNumber.IsEmpty() && !AddressExControl.IsWindowVisible() && !AddressShowErrorControl.IsWindowVisible() && !Address.IsEmpty() && !JobTitleExControl.IsWindowVisible() && !JobTitleShowErrorControl.IsWindowVisible() && !JobTitle.IsEmpty() && !SalaryExControl.IsWindowVisible() && !SalaryShowErrorControl.IsWindowVisible() && !Salary.IsEmpty()) {
		if (Id.IsEmpty()) {
			Id = database.GetNextAutoNumber();
			record.Id = Id;
			database.InsertRecord(record);
		}
		else {
			database.UpdateRecord(record);
		}
		UpdateData(FALSE);
		Insert::OnOK();
	}

}

CString Insert::GetAge(COleDateTime dateofbirth)
{
	Date currentDate = GetCurrentDate();
	Date dateOfBirth = GetDate(dateofbirth);
	CString age;
	age.Format(_T("%d"), ((GetDifference(currentDate, dateOfBirth) - CountLeapYears(dateOfBirth.Year, currentDate.Year)) / 365));
	return age;
}

CString Insert::GetYearsOfExperience(COleDateTime hiredate)
{
	Date currentDate = GetCurrentDate();
	Date hireDate = GetDate(hiredate);
	CString experience;
	experience.Format(_T("%d"), ((GetDifference(currentDate, hireDate) - CountLeapYears(hireDate.Year, currentDate.Year)) / 365));
	return experience;
}

int Insert::GetCurrentYear()
{
	return _wtoi(COleDateTime::GetCurrentTime().Format(_T("%Y")));
}

int Insert::GetCurrentMonth()
{
	return _wtoi(COleDateTime::GetCurrentTime().Format(_T("%m")));
}

int Insert::GetCurrentDay()
{
	return _wtoi(COleDateTime::GetCurrentTime().Format(_T("%d")));
}

Date Insert::GetCurrentDate()
{
	Date currentDate;
	currentDate.Year = GetCurrentYear();
	currentDate.Month = GetCurrentMonth();
	currentDate.Day = GetCurrentDay();
	return currentDate;
}

Date Insert::GetDate(COleDateTime empdate)
{
	Date date;
	date.Day = _wtoi(empdate.Format(_T("%d")));
	date.Month = _wtoi(empdate.Format(_T("%m")));
	date.Year = _wtoi(empdate.Format(_T("%Y")));
	return date;

}

int Insert::GetDifference(Date currentdate, Date pastdate)
{
	int totalDays = 0;
	int startYear = pastdate.Year;
	int startMonth = pastdate.Month;
	int startDay = pastdate.Day;
	int endYear = currentdate.Year;
	int endMonth = currentdate.Month;
	int endDay = currentdate.Day;
	if (startYear == endYear)
	{
		if (startMonth == endMonth)
		{
			if (startDay == endDay)      //for same dates
				return 0;
			else
				return abs(startDay - endDay);  //for same year, same month but diff days
		}
		else if (startMonth < endMonth)
		{
			int totalDays = 0;
			for (int i = startMonth; i < endMonth; i++)
				totalDays = totalDays + monthDays[i];

			if (startDay == endDay)      //for same year, same day but diff month 
				return totalDays;
			else if (startDay < endDay)
			{
				totalDays = totalDays + (endDay - startDay);
				return totalDays;
			}
			else
			{
				totalDays = totalDays - (startDay - endDay);
				return totalDays;
			}
		}
		else
		{
			int totalDays = 0;
			for (int i = endMonth; i < startMonth; i++)
				totalDays = totalDays + monthDays[i];

			if (startDay == endDay)
				return totalDays;
			else if (endDay < startDay)
			{
				totalDays = totalDays + (startDay - endDay);
				return totalDays;
			}
			else
			{
				totalDays = totalDays - (endDay - startDay);
				return totalDays;
			}
		}
	}
	else if (startYear < endYear)
	{
		int temp = 0;
		for (int i = startYear; i < endYear; i++)
		{
			if (CHECKLEAPYEAR(i))
				temp = temp + 366;
			else
				temp = temp + 365;
		}

		if (startMonth == endMonth)
		{
			if (startDay == endDay)      //for same month, same day but diff year
				return temp;
			else if (startDay < endDay)
				return temp + (endDay - startDay);
			else
				return temp - (startDay - endDay);
		}
		else if (startMonth < endMonth)
		{
			int totalDays = 0;
			for (int i = startMonth; i < endMonth; i++)
				totalDays = totalDays + monthDays[i];

			if (startDay == endDay)      // for same day, diff year and diff month
				return temp + totalDays;
			else if (startDay < endDay)
			{
				totalDays = totalDays + (endDay - startDay);
				return temp + totalDays;
			}
			else
			{
				totalDays = totalDays - (startDay - endDay);
				return temp + totalDays;
			}
		}
		else
		{
			int totalDays = 0;
			for (int i = endMonth; i < startMonth; i++)
				totalDays = totalDays + monthDays[i];

			if (startDay == endDay)
				return temp - totalDays;
			else if (endDay < startDay)
			{
				totalDays = totalDays + (startDay - endDay);
				return temp - totalDays;
			}
			else
			{
				totalDays = totalDays - (endDay - startDay);
				return temp - totalDays;
			}
		}
	}
	else
	{
		int temp = 0;
		for (int i = endYear; i < startYear; i++)
		{
			if (CHECKLEAPYEAR(i))
				temp = temp + 366;
			else
				temp = temp + 365;
		}

		if (startMonth == endMonth)
		{
			if (startDay == endDay)      // for same day, same month but diff year
				return temp;
			else if (endDay < startDay)
				return temp + (startDay - endDay);
			else
				return temp - (endDay - startDay);
		}
		else if (endMonth < startMonth)
		{
			int totalDays = 0;
			for (int i = endMonth; i < startMonth; i++)
				totalDays = totalDays + monthDays[i];

			if (startDay == endDay)
				return temp + totalDays;
			else if (endDay < startDay)
			{
				totalDays = totalDays + (startDay - endDay);
				return temp + totalDays;
			}
			else
			{
				totalDays = totalDays - (endDay - startDay);
				return temp + totalDays;
			}
		}
		else
		{
			int totalDays = 0;
			for (int i = startMonth; i < endMonth; i++)
				totalDays = totalDays + monthDays[i];

			if (startDay == endDay)
				return temp - totalDays;
			else if (startDay < endDay)
			{
				totalDays = totalDays + (endDay - startDay);
				return temp - totalDays;
			}
			else
			{
				totalDays = totalDays - (startDay - endDay);
				return temp - totalDays;
			}
		}
	}
	return 0;
}

int Insert::CountLeapYears(int startyear, int endyear)
{
	int countYears = 0;
	for (int year = startyear; year <= endyear; year++) {
		if (CHECKLEAPYEAR(year))
			countYears++;
	}
	return countYears;
}


CString Insert::ConvertDateTimeToString(COleDateTime HireDate)
{
	COleDateTime Date(HireDate);
	return Date.Format(_T("%d-%m-%Y"));
}




HBRUSH Insert::OnCtlColor(CDC* pdc, CWnd* pwnd, UINT nctlcolor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pdc, pwnd, nctlcolor);

	if (pwnd->GetDlgCtrlID() == IDC_STATIC_TITLEREQUIRED)
	{
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_TITLEEX) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_FIRSTNAMEREQUIRED) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_FIRSTNAMEEX) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_LASTNAME) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_LASTNAMEEXX) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_GENDERREQUIRED) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_GENDEREX) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_EMAILREQUIRED) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_PHONENUMBERREQUIRED) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_EMAILEX) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_PHONENUMBEREX) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_ADDRESSREQUIRED) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_ADDRESSEX) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_JOBTITLEREQUIRED) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_JOBTITLEEX) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_SALARYREQUIRED) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}
	else if (pwnd->GetDlgCtrlID() == IDC_STATIC_SALARYEX) {
		pdc->SetTextColor(RGB(255, 0, 0));
	}

	return hbr;
}

void Insert::OnEnChangeEditIFirstname()
{
	int length = FirstNameControl.GetWindowTextLengthW();
	if (length == 0) {
		GetDlgItem(IDC_STATIC_FIRSTNAMEREQUIRED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_FIRSTNAMEEX)->ShowWindow(SW_SHOW);
	}
	else {
		GetDlgItem(IDC_STATIC_FIRSTNAMEREQUIRED)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_FIRSTNAMEEX)->ShowWindow(SW_HIDE);
	}
	return;
}

void Insert::OnCbnEditchangeComboITitle()
{
	int length = TitleControl.GetWindowTextLengthW();
	if (length == 0) {
		GetDlgItem(IDC_STATIC_TITLEREQUIRED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_TITLEEX)->ShowWindow(SW_SHOW);
	}
	else {
		GetDlgItem(IDC_STATIC_TITLEREQUIRED)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_TITLEEX)->ShowWindow(SW_HIDE);
	}
}


void Insert::OnEnChangeEditLastname()
{
	int length = LastNameControl.GetWindowTextLengthW();
	if (length == 0) {
		GetDlgItem(IDC_STATIC_LASTNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASTNAMEEXX)->ShowWindow(SW_SHOW);
	}
	else {
		GetDlgItem(IDC_STATIC_LASTNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASTNAMEEXX)->ShowWindow(SW_HIDE);
	}
}


void Insert::OnCbnEditchangeComboGender()
{
	int length = GenderControl.GetWindowTextLengthW();
	if (length == 0) {
		GetDlgItem(IDC_STATIC_GENDERREQUIRED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_GENDEREX)->ShowWindow(SW_SHOW);
	}
	else {
		GetDlgItem(IDC_STATIC_GENDERREQUIRED)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_GENDEREX)->ShowWindow(SW_HIDE);
	}
}


void Insert::OnEnChangeEditEmail()
{
	const regex pattern("^([a-z]+)@([a-z]+)\.([a-z]{2,5})$");
	GetDlgItemText(IDC_EDIT_EMAIL, Email);
	string email = CT2A(Email.GetString());
	bool IsEmailValid = regex_match(email.begin(), email.end(), pattern);

	int length = EmailControl.GetWindowTextLengthW();
	if (length == 0) {
		GetDlgItem(IDC_STATIC_EMAILREQUIRED)->SetWindowTextW(L"Email must be required");
		GetDlgItem(IDC_STATIC_EMAILREQUIRED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_EMAILEX)->ShowWindow(SW_SHOW);

	}
	else {
		if (IsEmailValid) {
			GetDlgItem(IDC_STATIC_EMAILREQUIRED)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_EMAILEX)->ShowWindow(SW_HIDE);
		}
		else {
			GetDlgItem(IDC_STATIC_EMAILREQUIRED)->SetWindowTextW(L"Enter a valid email");
			GetDlgItem(IDC_STATIC_EMAILREQUIRED)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_EMAILEX)->ShowWindow(SW_SHOW);
		}
	}
}


void Insert::OnEnChangeEditPhoneNumber()
{
	int length = PhoneNumberControl.GetWindowTextLengthW();
	if (length == 0) {
		PhoneNumberValidateControl.SetWindowTextW(_T("PhoneNumber must be required"));
		GetDlgItem(IDC_STATIC_PHONENUMBERREQUIRED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PHONENUMBEREX)->ShowWindow(SW_SHOW);
	}
	else if (length == 10) {

		GetDlgItem(IDC_STATIC_PHONENUMBERREQUIRED)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PHONENUMBEREX)->ShowWindow(SW_HIDE);
	}
	else if (length > 10 || length < 10) {
		PhoneNumberValidateControl.SetWindowTextW(_T("Enter a valid PhoneNumber"));
		GetDlgItem(IDC_STATIC_PHONENUMBERREQUIRED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PHONENUMBEREX)->ShowWindow(SW_SHOW);
	}
}


void Insert::OnEnChangeEditAddress()
{
	int length = AddressControl.GetWindowTextLengthW();
	if (length == 0) {
		GetDlgItem(IDC_STATIC_ADDRESSREQUIRED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ADDRESSEX)->ShowWindow(SW_SHOW);
	}
	else {
		GetDlgItem(IDC_STATIC_ADDRESSREQUIRED)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ADDRESSEX)->ShowWindow(SW_HIDE);
	}
}


void Insert::OnCbnEditchangeComboJobtitle()
{
	int length = JobTitleControl.GetWindowTextLengthW();
	if (length == 0) {
		GetDlgItem(IDC_STATIC_JOBTITLEREQUIRED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_JOBTITLEEX)->ShowWindow(SW_SHOW);
	}
	else {
		GetDlgItem(IDC_STATIC_JOBTITLEREQUIRED)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_JOBTITLEEX)->ShowWindow(SW_HIDE);
	}
}


void Insert::OnEnChangeEditSalary()
{

	int length = SalaryControl.GetWindowTextLengthW();
	if (length == 0) {
		GetDlgItem(IDC_STATIC_SALARYREQUIRED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SALARYEX)->ShowWindow(SW_SHOW);
	}
	else {
		GetDlgItem(IDC_STATIC_SALARYREQUIRED)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SALARYEX)->ShowWindow(SW_HIDE);
	}
}


void Insert::OnCbnSelchangeComboITitle()
{
	GetDlgItem(IDC_STATIC_TITLEREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TITLEEX)->ShowWindow(SW_HIDE);
}


void Insert::OnCbnSelchangeComboGender()
{
	GetDlgItem(IDC_STATIC_GENDERREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_GENDEREX)->ShowWindow(SW_HIDE);
}


void Insert::OnCbnSelchangeComboJobtitle()
{
	GetDlgItem(IDC_STATIC_JOBTITLEREQUIRED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_JOBTITLEEX)->ShowWindow(SW_HIDE);
}


void Insert::OnDtnDatetimechangeDatetimepickerDateofbirth(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	COleDateTime dateOfBirth;
	DOBControl.GetTime(dateOfBirth);
	GetDlgItem(IDC_EDIT_AGE)->SetWindowTextW(GetAge(dateOfBirth));
	*pResult = 0;
}


void Insert::OnDtnDatetimechangeDatetimepickerHiredate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	COleDateTime hireDate;
	HiredateControl.GetTime(hireDate);
	GetDlgItem(IDC_EDIT_YEARSOFEXP)->SetWindowTextW(GetAge(hireDate));
	*pResult = 0;
}


void Insert::OnEnUpdateEditEmail()
{

}
