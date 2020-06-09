// Assignment 7: Employee.cpp
// Member-Function definitions for Employee class.
// Calculate gross pay, net pay, pension and deductions 
// for employees.
//
// Author: Shane Calado
// Date: 03/10/18

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Employee.h"

using namespace std;

// Default Ctor for employee.
Employee::Employee()
{

}

// Overloaded Ctor for employee.
// Takes in verified employee data and stores it.
Employee::Employee(int socialInsuranceNum,
	float hourlyRate,
	int exemptions,
	float hoursWorked)
{
	this->socialInsuranceNum = socialInsuranceNum;
	this->hourlyRate = hourlyRate;
	this->exemptions = exemptions;
	this->hoursWorked = hoursWorked;
}

//Implementation of the getSocialInsuranceNum() member function.
// Return employee's social insurance number.
int Employee::getSocialInsuranceNum()
{
	return socialInsuranceNum;
}

//Implementation of the getHourlyRate() member function.
// Return employee's hourly rate.
float Employee::getHourlyRate()
{
	return hourlyRate;
}

//Implementation of the getExemptions() member function.
// Return employee's total number of tax exemtions.
int Employee::getExemptions()
{
	return exemptions;
}

//Implementation of the getHoursWorked() member function.
// Return employee's total hours worked.
float Employee::getHoursWorked()
{
	return hoursWorked;
}

//Implementation of the getGrossPay() member function.
// Return employee's total gross pay.
float Employee::getGrossPay()
{
	float hours = getHoursWorked();

	if (hours <= REGULAR_HOURS_MAX)
	{
		return hours * hourlyRate;
	}
	else
	{
		return (REGULAR_HOURS_MAX * hourlyRate)
			+ ((hours - REGULAR_HOURS_MAX) * hourlyRate * OVERTIME_HOURLY_RATE);
	}
}

//Implementation of the getDeductions() member function.
// Return employee's total deductions.
float Employee::getDeductions()
{
	//Federal income tax deductions.
	float taxableAmount = getGrossPay() - (FEDERAL_TAX_VAR_1 * getExemptions()) - FEDERAL_TAX_VAR_2;
	float federalTax = taxableAmount * (FEDERAL_INCOME_TAX_PERCENT + (FEDERAL_TAX_VAR_3 * taxableAmount));

	//Provincial income tax deductions.
	float provincialTax = federalTax * PROVINCIAL_INCOME_TAX_PERCENT;

	float taxDeductions = federalTax + provincialTax;

	if (taxDeductions > 0)
	{
		return taxDeductions + getPensionWithhold();
	}
	else
	{
		return 0 + getPensionWithhold();
	}
}

//Implementation of the getPensionWithhold() member function.
// Return employee's total pension withhold;
float Employee::getPensionWithhold()
{
	float pensionWithold = getGrossPay() * PENSION_WITHHOLD_PERCENT;

	if (pensionWithold >= PENSION_WITHHOLD_MIN)
	{
		pensionWithold = PENSION_WITHHOLD_MIN;
	}

	return pensionWithold;
}

//Implementation of the getNetPay() member function.
// Return employee's total net pay.
float Employee::getNetPay()
{
	return getGrossPay() - getDeductions();
}

//Implementation of the printEmployee() member function.
// Returns formated Employee data.
stringstream Employee::printEmployee()
{
	stringstream returnString;

	returnString << left << setw(20) << getSocialInsuranceNum()
		<< right << fixed << setprecision(2) << setw(12) << getGrossPay()
		<< fixed << setprecision(2) << setw(11) << getNetPay()
		<< fixed << setprecision(2) << setw(11) << getPensionWithhold()
		<< fixed << setprecision(2) << setw(14) << getDeductions();

	return returnString;
}

//Implementation of the verifyInput() member function.
// Verifies Emplyee data before saving.
// Returns a list of error codes.
std::vector<int> Employee::verifyInput(int soicialInsuranceNum, 
	float hourlyRate, 
	int exemptions, 
	float hoursWorked)
{
	std::vector<int> errorCodes;
	string SIN = to_string(soicialInsuranceNum);

	if (SIN.length() != SIN_NUMBER_LENGTH || SIN.substr(0, 1) == "0")
	{
		errorCodes.push_back(1);
	}

	if (hourlyRate < HOURLY_RATE_MIN || hourlyRate > HOURLY_RATE_MAX)
	{
		errorCodes.push_back(2);
	}

	if (exemptions < EXEMPTIONS_MIN || exemptions > EXEMPTIONS_MAX)
	{
		errorCodes.push_back(3);
	}

	if (hoursWorked < HOURS_WORKED_MIN || hoursWorked > HOURS_WORKED_MAX)
	{
		errorCodes.push_back(4);
	}

	errorCodes.push_back(0);

	return errorCodes;
}


