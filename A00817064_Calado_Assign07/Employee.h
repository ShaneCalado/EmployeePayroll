// Assignment 7: Employee.h
// Declaration of Employee class.
// Calculate gross pay, net pay, pension and deductions 
// for employees of Rogers Hostpital Supplies Company.
//
// Author: Shane Calado
// Date: 03/10/18

#pragma once
#include <vector>

const static int SIN_NUMBER_LENGTH = 9;
const static float HOURLY_RATE_MAX = 99.99;
const static float HOURLY_RATE_MIN = 0.00;
const static float OVERTIME_HOURLY_RATE = 1.50;
const static int EXEMPTIONS_MAX = 19;
const static int EXEMPTIONS_MIN = 0;
const static float HOURS_WORKED_MAX = 54.00;
const static float HOURS_WORKED_MIN = 0.00;
const static float REGULAR_HOURS_MAX = 40.00;
const static float PROVINCIAL_INCOME_TAX_PERCENT = 0.35;
const static float FEDERAL_INCOME_TAX_PERCENT = 0.14;
const static float FEDERAL_TAX_VAR_1 = 14.00;
const static float FEDERAL_TAX_VAR_2 = 11.00;
const static float FEDERAL_TAX_VAR_3 = 0.00023;
const static float PENSION_WITHHOLD_PERCENT = 0.077;
const static float PENSION_WITHHOLD_MIN = 16.50;

class Employee
{
public:
	Employee();

	Employee(int socialInsuranceNum,
		float hourlyRate,
		int exemptions,
		float hoursWorked);

	int getSocialInsuranceNum(); // Return employee's social insurance number.
	float getHourlyRate(); // Return employee's hourly rate.
	int getExemptions(); // Return employee's total number of tax exemtions.
	float getHoursWorked(); // Return employee's total hours worked.
	float getGrossPay(); // Return employee's total gross pay.
	float getDeductions(); // Return employee's total deductions.
	float getPensionWithhold(); // Return employee's total pension withhold;
	float getNetPay(); // Return employee's total net pay.

	std::stringstream printEmployee(); // Returns formated Employee data.

	// Verifies Emplyee data before saving.
	// Returns a list of error codes.
	static std::vector<int> verifyInput(int socialInsuranceNum, 
		float hourlyRate, 
		int exemptions, 
		float hoursWorked);

private:
	int socialInsuranceNum; // Employee's social insurance number.
	float hourlyRate; // Employee's hourly rate.
	int exemptions; // Employee's total number of tax exemtions.
	float hoursWorked; // REmployee's total hours worked.

};

