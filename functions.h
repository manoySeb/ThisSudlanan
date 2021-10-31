#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void displayInfo(Personal_Information info){
	printf("\n\n Name : %s %s",info.name.firstname,info.name.lastname);
	printf("\n Gender : %c",info.gender);
	printf("\n Birthdate : %s %d, %d",info.birthdate.month,info.birthdate.day,info.birthdate.year);
	printf("\n Age : %d",info.age);
}

Personal_Information getInfo(){
	Personal_Information perInfo;
	Fullname name;
	Date bdate;
	int age;
	char gender;
	int isExit=1,innerExit=0,error;
	char choice;
	
	do{
		system("cls");
		error=0;
		printf("\n Enter Firstname >> ");
		fflush(stdin);
		gets(name.firstname);
		printf("\n Enter Lastname >> ");
		fflush(stdin);
		gets(name.lastname);
		printf("\n Birthdate: ");
		printf("\n   Month: ");
		printf("\n     'January'\n     'February'\n     'March'\n     'April'\n     'May'\n     'June'");
		printf("\n     'July'\n     'August'\n     'September'\n     'October'\n     'November'\n     'December'");
		printf("\n   >> ");
		fflush(stdin);
		gets(bdate.month);
		printf("\n   Day >> ");
		fflush(stdin);
		scanf("%d",&bdate.day);
		printf("\n   Year >> ");
		fflush(stdin);
		scanf("%d",&bdate.year);
		printf("\n Age >> ");
		fflush(stdin);
		scanf("%d",&age);
		printf("\n Gender [M]/[F] >> ");
		fflush(stdin);
		scanf("%c",&gender);
		perInfo.name=name;
		perInfo.birthdate=bdate;
		perInfo.gender=gender;
		perInfo.age=age;
		do{
			system("cls");
			displayInfo(perInfo);
			(error==0)?printf(""):printf("\n\n **Invalid Option! ** ");
			printf("\n\n Are You Sure? ");
			printf("\n    [1] Yes\n    [2] No");
			printf("\n\n    >> ");
			fflush(stdin);
			choice=(char)getch();
			switch(choice){
				case '1':
					innerExit=1;
					isExit=1;
					break;
				case '2':
					innerExit=1;
					isExit=0;
					break;
				default:
					innerExit=0;
					error=1;
					break;
			}
		}while(innerExit!=1);
	}while(isExit!=1);
}

void system_init(){
	FILE* fp;
	Admin admin;
	Credentials cred,temp;
	int age,isExit=0,error=0;
	char gender;
	if((fp=fopen("admins.bin","rb"))==NULL){
		fp=fopen("admins.bin","ab");
		admin.information = getInfo();
		do{
			system("cls");
			(error==0)?printf(""):printf("\n **Password Do Not Match!**\n");
			printf("\n New Username >> ");
			fflush(stdin);
			gets(cred.username);
			printf("\n New Password >> ");
			fflush(stdin);
			gets(cred.password);
			printf("\n Confirm Password >> ");
			fflush(stdin);
			gets(temp.password);
			if(strcmp(cred.password,temp.password)==0)
				isExit=1;
			else
				error=1;
		}while(isExit!=1);
		admin.credential=cred;
		admin.admin_id=1;
		fwrite(&admin,sizeof(Admin),1,fp);
		fclose(fp);
		fp=fopen("employees.bin","ab");
		fclose(fp);
		fp=fopen("payrolls.bin","ab");
		fclose(fp);
	}
}

void system_turn_on(){
	system("cls");
	printf("\n System Starting...");
	printf("\n\n Press any key...\n");
	getch();
}

void system_turn_off(){
	system("cls");
	printf("\n System Shutting Down...");
	printf("\n\n Press any key...");
	fflush(stdin);
	getch();
	system("cls");
	printf("\n System Turned Off!\n");
}

int getLastID(){
	Employee emp;
	FILE* fp;
	int id = 1000;
	fp=fopen("employees.bin","ab");
	while(fread(&emp,sizeof(Employee),1,fp)){
		id=emp.employee_id+1;
	}
	fclose(fp);
	return id;
}

void displayEmployees(){
	Employee emp;
	FILE* fp;
	system("cls");
	fp=fopen("employees.bin","rb");
	while(fread(&emp,sizeof(Employee),1,fp)){
		printf("\n\n ID : %d",emp.employee_id);
		printf("\n Name : %s %s",emp.information.name.firstname,emp.information.name.lastname);
		printf("\n Gender : %c",emp.information.gender);
		printf("\n Birthdate : %s %d, %d",emp.information.birthdate.month,emp.information.birthdate.day,emp.information.birthdate.year);
		printf("\n Age : %d",emp.information.age);
		printf("\n SSS : %d",emp.SSS);
		printf("\n Philhealth : %d",emp.Philhealth);
		printf("\n PagIbig : %d",emp.PagIbig);
		printf("\n Rate : %f",emp.Rate);
		printf("\n Type : %s",emp.Type);
	}
	getch();
}


void displayPayrolls(){
	Payroll pay;
	FILE* fp;
	system("cls");
	fp=fopen("payrolls.bin","rb");
	while(fread(&pay,sizeof(Payroll),1,fp)){
		
		printf("\n%8d | %2d | %2d | %2d | %12.2f | %15d | %10.2f | %12.2f | %7.2f | %12.2f | %10.2f | %12.2f | %12.2f |",
			pay.employeeID,
			pay.daysDuty,
			pay.daysLate,
			pay.daysAbsent,
			pay.grossPay,
			pay.PhilHealth,
			pay.PagIbig,
			pay.SSS,
			pay.Tax,
			pay.adjustment,
			pay.totalDeduction,
			pay.netPay
		);
	}
	getch();
}

void add_employee(){
	Employee emp;
	Payroll payroll;
	FILE* fp;
	int isExit=0,innerExit=0,centerExit=0;;
	char choice,temp_choice;
	do{
		system("cls");
		emp.information=getInfo();
		fflush(stdin);
		do{
			system("cls");
			printf("\n Enter SSS ID (Enter 0 if none) >> ");
			scanf("%d",&emp.SSS);
			printf("\n Enter PhilHealth ID (Enter 0 if none) >> ");
			scanf("%d",&emp.Philhealth);
			printf("\n Enter PagIbig ID (Enter 0 if none) >> ");
			scanf("%d",&emp.PagIbig);
			printf("\n\n Enter Rate (in Peso) >> ");
			scanf("%f", &emp.Rate);
			printf("\n Enter Type : [DAILY]/[MONTHLY] >> ");
			scanf("%s", &emp.Type);
			fflush(stdin);
			do{
				system("cls");
				fflush(stdin);
				printf("\n SSS ID : %d",emp.SSS);
				printf("\n PhilHealth ID : %d",emp.Philhealth);
				printf("\n PagIbig ID : %d",emp.PagIbig);
				printf("\n\n Rate : %f",emp.Rate);
				printf("\n Type : %s",emp.Type);
				printf("\n\n Above Informations are correct?");
				printf("\n    [1] Yes\n    [2] No");
				printf("\n\n     >> ");
				choice=(char)getch();
				switch(choice){
					case '1':
						centerExit=1;
						innerExit=1;
						break;
					case '2':
						centerExit=1;
						innerExit=0;
						break;
					default:
						centerExit=0;
						break;	
				}
			}while(centerExit!=1);
		}while(innerExit!=1);
		emp.employee_id=getLastID();
		payroll.employeeID=getLastID();
		payroll.adjustment=0;
		payroll.daysAbsent=0;
		payroll.daysDuty=0;
		payroll.daysLate=0;
		payroll.grossPay=0;
		payroll.netPay=0;
		payroll.PagIbig=0;
		payroll.PhilHealth=0;
		payroll.SSS=0;
		payroll.Tax=0;
		payroll.totalDeduction=0;
		do{
			system("cls");
			printf("\n All Informations are Correct?");
			printf("\n   [1] Yes");
			printf("\n   [2] No");
			printf("\n   [3] Cancel");
			choice=(char)getch();
			switch(choice){
				case '1':
					fp=fopen("employees.bin","ab");
					fwrite(&emp,sizeof(Employee),1,fp);
					fclose(fp);
					fp=fopen("payrolls.bin","ab");
					fwrite(&payroll,sizeof(Payroll),1,fp);
					fclose(fp);
					innerExit=1;
					isExit=1;
					break;
				case '2':
					innerExit=1;
					isExit=0;
					break;
				default:
					innerExit=0;
					break;
			}
		}while(innerExit!=1);
	}while(isExit!=1);
}

void edit_employee(){
	system("cls");
	printf("\n Edit Employee Here");
	getch();
}

void find_employee(){
	system("cls");
	printf("\n Find Employee Here");
	getch();
}

void remove_employee(){
	system("cls");
	printf("\n Remove Employee Here");
	getch();
}

void main_menu(){
	int isExit = 0,error=0;
	char choice;
	do{
		system("cls");
		printf("\n----------\n");
		printf("Main Menu");
		printf("\n----------\n");
		printf("\n [1] Add Employee");
		printf("\n [2] Edit Employee");
		printf("\n [3] Find Employee");
		printf("\n [4] Remove Employee");
		printf("\n [5] Logout");
		(error==0)?printf(""):printf("\n\n Invalid Option!");
		printf("\n\n>>");
		fflush(stdin);
		choice=(char)getch();
		switch(choice){
			case '1':
				add_employee();
				error=0;
				break;
			case '2':
				edit_employee();
				error=0;
				break;
			case '3':
				find_employee();
				error=0;
				break;
			case '4':
				remove_employee();
				error=0;
				break;
			case '5':
				isExit=1;
				break;
			default:
				error=1;
				break;
		}
	}while(isExit!=1);
}

void system_login(){
	FILE* fp;
	Admin admin;
	int isExit=0,innerExit=0,error=0,exist=0;
	char choice,user[20],pass[20];
	do{
		system("cls");
		printf("\n Username>> ");
		fflush(stdin);
		gets(user);
		printf("\n Password>> ");
		fflush(stdin);
		gets(pass);
		fp=fopen("admins.bin","rb");
		while(fread(&admin,sizeof(Admin),1,fp)){
			if(strcmp(user,admin.credential.username)==0&&strcmp(pass,admin.credential.password)==0){
				exist=1;
				break;
			}
		}
		if(exist==1){
			main_menu();
			isExit=1;
		}
		else{
			do{
				system("cls");
				printf("\n\n **Invalid Credentials!**");
				printf("\n\n----------");
				printf("\n [1] Login");
				printf("\n [2] Cancel");
				(error==0)?printf(""):printf("\n\n Invalid Option!");
				printf("\n\n>>");
				fflush(stdin);
				choice=(char)getch();
				switch(choice){
					case '1':
						innerExit=1;
						break;
					case '2':
						innerExit=1;
						isExit=1;
						break;
					default:
						error=1;
						break;
				}
			}while(innerExit!=1);
		}
			
	}while(isExit!=1);
	
	
}

void system_menu(){
	int isExit = 0,error=0;
	char choice;
	do{
		system("cls");
		printf("\n----------\n");
		printf("System Menu");
		printf("\n----------\n");
		printf("\n [1] Login");
		printf("\n [2] Shutdown");
		(error==0)?printf(""):printf("\n\n Invalid Option!");
		printf("\n\n>>");
		fflush(stdin);
		choice=(char)getch();
		switch(choice){
			case '1':
				system_login();
				break;
			case '2':
				printf("\nShutting down");
				isExit=1;
				break;
			default:
				error=1;
				break;
		}
		
	}while(isExit!=1);
}

#endif
