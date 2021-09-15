#pragma once

#include "Date.h"
#define CHECKLEAPYEAR(year) ((year%4==0 && year%100!=0) || year%400==0)
const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
// Insert dialog

class Insert : public CDialogEx
{
	DECLARE_DYNAMIC(Insert)

public:
	Insert(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Insert();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox TitleControl;
	CString Title;
	CEdit FirstNameControl;
	CString FirstName;
	CEdit LastNameControl;
	CString LastName;
	CComboBox GenderControl;
	CString Gender;
	CEdit EmailControl;
	CString Email;
	CEdit PhoneNumberControl;
	CString PhoneNumber;
	CDateTimeCtrl DOBControl;
	COleDateTime DateOfBirth;
	CEdit AddressControl;
	CString Address;
	CDateTimeCtrl HiredateControl;
	COleDateTime HireDate;
	CComboBox JobTitleControl;
	CString JobTitle;
	CEdit SalaryControl;
	CString Salary;
	CString YearsOfExperience;
	CString Age;
	CString Id;
	CButton SubmitBtnCtrl;
	CStatic FirstNameError;
	CEdit AgeControl;



	CString GetAge(COleDateTime dateofbirth);
	CString GetYearsOfExperience(COleDateTime hiredate);
	int GetCurrentYear();
	int GetCurrentMonth();
	int GetCurrentDay();
	Date GetCurrentDate();
	Date GetDate(COleDateTime empdate);
	int GetDifference(Date currentDate, Date pastdate);
	int CountLeapYears(int startyear, int endyear);
	CString ConvertDateTimeToString(COleDateTime HireDate);


	afx_msg void OnBnClickedButtonInsert();
	afx_msg HBRUSH OnCtlColor(CDC* pdc, CWnd* pwnd, UINT nctlcolor);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditIFirstname();
	afx_msg void OnCbnEditchangeComboITitle();
	afx_msg void OnEnChangeEditLastname();
	afx_msg void OnCbnEditchangeComboGender();
	afx_msg void OnEnChangeEditEmail();
	afx_msg void OnEnChangeEditPhoneNumber();
	afx_msg void OnEnChangeEditAddress();
	afx_msg void OnCbnEditchangeComboJobtitle();
	afx_msg void OnEnChangeEditSalary();
	afx_msg void OnCbnSelchangeComboITitle();
	afx_msg void OnCbnSelchangeComboGender();
	afx_msg void OnCbnSelchangeComboJobtitle();
	afx_msg void OnDtnDatetimechangeDatetimepickerDateofbirth(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerHiredate(NMHDR* pNMHDR, LRESULT* pResult);
	CStatic PhoneNumberValidateControl;
	afx_msg void OnEnUpdateEditEmail();
	CStatic TitleShowErrorControl;
	CStatic LastNameShowErrorControl;
	CStatic GenderShowErrorControl;
	CStatic EmailShowErrorControl;
	CStatic AddressShowErrorControl;
	CStatic JobTitleShowErrorControl;
	CStatic SalaryShowErrorControl;
	CStatic TitleExControl;
	CStatic FirstNameExControl;
	CStatic LastNameExControl;
	CStatic GenderExControl;
	CStatic EmailExControl;
	CStatic PhoneNumberExControl;
	CStatic AddressExControl;
	CStatic JobTitleExControl;
	CStatic SalaryExControl;
};
