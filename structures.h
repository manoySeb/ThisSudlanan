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

#endif
