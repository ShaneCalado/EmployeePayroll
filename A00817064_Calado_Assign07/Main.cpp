// Assignment 7: Main.cpp
// Calculate gross pay, net pay, pension and deductions 
// for employees of Rogers Hostpital Supplies Company.
//
//

#include <iostream>
#include <conio.h>  // Required for _getch() function
#include <fstream>  // Required for file input/output
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include "Employee.h"

using namespace std;

//global constants

// One way to specify a file name:
const char * IN_FILE = "EmployeePayInput.txt";

// A second way to specify a file name:
#define OUT_FILE "EmployeePayOutput.txt"

int main()
{
	//Declare variables
	vector <Employee> employees; 
	int numberOfEmployees = 0;
	float totalGrossPay = 0.00;
	float totalNetPay = 0.00;
	float totalPension = 0.00;
	float totalDeductions = 0;

	Employee tempEmployee;

	long socialInsuranceNum;  // Will store social security number of employee
	int numberOfExemptions;  // Will store number of excemptions for employee

	double payRate,			// Will store the pay rate for the employee
		hoursWorked;		// Will store hours worked for the employee

	//Define ifstream object and open file
	ifstream ins;
	ins.open(IN_FILE);

	//Check that file opened without any issues
	if (ins.fail())
	{
		cerr << "ERROR--> Unable to open input file : " << IN_FILE << endl;
		cerr << '\n' << endl;
		_getch(); // causes execution to pause until a char is entered
		return -1; //error return code
	}

	//Define ofstream object and open file
	ofstream outs;
	outs.open(OUT_FILE);

	//Check that file opened without any issues
	if (outs.fail())
	{
		cerr << "ERROR--> Unable to open output file : " << OUT_FILE << endl;
		cerr << '\n' << endl;
		_getch(); // causes execution to pause until a char is entered
		return -2; //error return code
	}

	// Read in first social security number
	ins >> socialInsuranceNum;

	// Process data until end of file is reached
	while (!ins.eof()){

		// Read in other data for the employee
		ins >> payRate >> numberOfExemptions >> hoursWorked;
		vector<int> errorCodes = Employee::verifyInput(socialInsuranceNum, payRate, numberOfExemptions, hoursWorked);

		if (errorCodes[0] == 0)
		{
			tempEmployee = Employee((int)socialInsuranceNum, (float)payRate, numberOfExemptions, (float)hoursWorked);

			numberOfEmployees++;
			totalGrossPay += tempEmployee.getGrossPay();
			totalNetPay += tempEmployee.getNetPay();
			totalPension += tempEmployee.getPensionWithhold();
			totalDeductions += tempEmployee.getDeductions();

			employees.push_back(tempEmployee);
		}
		else
		{

			for (int errorCode : errorCodes)
			{

				if (errorCode != 0)
				{
					cout << setw(10) << socialInsuranceNum << right << setw(22) << "INPUT DATA ERROR:  ";
				}

				switch (errorCode)
				{
				case 0:
					break;
				case 1:
					cout << "Invalid social security #" << endl;
					break;
				case 2:
					cout << "Invalid pay rate: " << fixed << setprecision(2) << payRate << endl;
					break;
				case 3:
					cout << "Invalid number of exemptions: " << numberOfExemptions << endl;
					break;
				case 4:
					cout << "Invalid hours worked: " << fixed << setprecision(2) << hoursWorked << endl;
					break;
				default:
					cout << "Invalid error code" << endl;
					break;
				}
			}

			
		}

		// The following line of code is used to confirm that reading and writing from/to files is working correctly.
		//  This line of code (and these 2 comment lines) will need to be removed in your final solution.
		//outs << socialInsuranceNum << "  " << payRate << "  " << numberOfExemptions << "  " << hoursWorked << '\n';

		// Read in next social security number
		ins >> socialInsuranceNum;
	}

	outs << "Rogers Hospital Supplies Company\n"
		<< "---------------------------------\n\n"
		<< "Social insurance no.   gross pay    net pay    pension    deductions\n"
		<< "--------------------------------------------------------------------"
		<< endl;

	for (Employee employee : employees)
	{
		//employee.printEmployee();
		outs << employee.printEmployee().rdbuf() << endl;
	}

	outs << "\n\n\nSummary\n"
		<< "-------\n\n"
		<< left << setw(42) << "Number of employees processed:" 
		<< right << setw(15) << numberOfEmployees << "\n"
		<< left << setw(42) << "Total gross pay for all employees:" 
		<< right << setw(15) << fixed << setprecision(2) << totalGrossPay << "\n"
		<< left << setw(42) << "Total net pay for all employees:" 
		<< right << setw(15) << setprecision(2) << totalNetPay << "\n"
		<< left << setw(42) << "Total pension withheld for all employees:" 
		<< right << setw(15) << setprecision(2) << totalPension << "\n"
		<< left << setw(42) << "Total deductions for all employees:" 
		<< right << setw(15) << setprecision(2) << totalDeductions << endl;

	// Close files
	ins.close();
	outs.close();

	cout << '\n' << endl;

	// Remove following line of code (and this comment) from your solution
	cout << "Type any key to continue ... \n\n";

	_getch(); // causes execution to pause until char is entered

}