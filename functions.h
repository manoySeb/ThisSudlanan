#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define USERNAME "admin"
#define PASSWORD "adminpass"

void system_init(){
	FILE* fp;
	Admin admin;
	Credentials cred;
	int age;
	char gender;
	if((fp=fopen("admins.bin","rb"))==NULL){
		fp=fopen("admins.bin","ab");
		fclose(fp);
		fp=fopen("employees.bin","ab");
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

void add_employee(){
	printf("\n Add Employee Here");
	getch();
}

void edit_employee(){
	printf("\n Edit Employee Here");
	getch();
}

void find_employee(){
	printf("\n Find Employee Here");
	getch();
}

void remove_employee(){
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
				system("cls");
				add_employee();
				error=0;
				break;
			case '2':
				system("cls");
				edit_employee();
				error=0;
				break;
			case '3':
				system("cls");
				find_employee();
				error=0;
				break;
			case '4':
				system("cls");
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
	int isExit=0,innerExit=0,error=0;
	char choice,user[20],pass[20];
	do{
		system("cls");
		printf("\n Username>> ");
		fflush(stdin);
		gets(user);
		printf("\n Password>> ");
		fflush(stdin);
		gets(pass);
		if(strcmp(user,USERNAME)==0&&strcmp(pass,PASSWORD)==0){
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