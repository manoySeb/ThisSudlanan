#ifndef STRUCTURES
#define STRCUTURES
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct{
	char firstname[50];
	char lastname[50];
	char mi;
}Fullname;

typedef struct{
	char username[50];
	char password[50];
}Credentials;

typedef struct{
	char month[15];
	int day;
	int year;
}Date;
 
typedef struct{
 	Fullname name;
 	Date birthdate;
 	int age;
 	char gender;
}Personal_Information;

typedef struct{
	int empID;
 	Personal_Information information;
 	
 	int SSS;
 	int Philhealth;
 	int PagIbig;
 	
 	float Rate;
 	enum Type{
 		HOURLY, MONTHLY
	};
}Employee;

typedef struct{
 	Personal_Information information;
 	Credentials credential;
}Admin;

typedef struct{
	int employeeID;

	int daysDuty;
	int daysAbsent;
	int daysLate;
	
	float grossPay;
	
	float PhilHealth; 		//If 10k below : 350, 70k up : 2450, 10k - 70k : 3.50%
	float PagIbig;			// 2% from employee
	float SSS; 				// Monthly Compensation * 4.5%
	float Tax; 				// Table sent sa GC
	
	float adjustment; 		// Default 0;
	float totalDeduction; 	//Based on Late
	float netPay;
}PayRoll;

#endif
