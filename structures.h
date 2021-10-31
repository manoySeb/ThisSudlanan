#ifndef STRUCTURES_H
#define STRCUTURES_H
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct{
	char firstname[50];
	char lastname[50];
}Fullname;

typedef struct{
	int SSS;
	int PhilHealth;
	int PagIbig;
}Government_id;

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
	int employee_id;
 	Personal_Information information;
 	Government_id ids;
}Employee;

typedef struct{
	int admin_id;
 	Personal_Information information;
 	Credentials credential;
}Admin;

 	
 
#endif
