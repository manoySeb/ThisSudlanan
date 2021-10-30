#include <stdio.h>
#include <string.h>
#include <time.h>

#define T_LEN 256
#define MAX 16

typedef struct{
	int hour; // 0 -> 23
	int min; // 0 -59
}Time;

typedef struct{
	int month; // 1 - 12
	int day; // 1 - 31
	int year; // Default 2000
}Date;

typedef struct{
	Date current; 

	Time timeIn; // Input
	Time timeOut;// Input
	
	Time totalTime;
	Time overtime; // If TotalTime - 8 hours exceeds 1 hour
	Time underTime; // If TotalTime < 8 hours;
	int isLate; // 1 if late 0 if not;
}timeStamp;

typedef struct{
	int ID;
	int employeeID;
	
	int monthlyRate; // Fixed Wage
	int dailyRate; // Needs Calculation
	
	timeStamp TimeSheet[MAX];
	int daysCount;//1-15 , 16 to [28,29,30,31]
	
	int daysDuty;
	int daysAbsent;
	int daysLate;
	
	int grossPay;
	int PhilHealth;
	int PagIbig;//
	int SSS; //If 10k below : 350, 70k up : 2450, between : 3.50%
	int Tax;
	int totalDeduction;
	int netPay;
	
	
}PayRoll;

void employeeTimeSheet(char Name[], Time in, Time out);
void employeeTimeIn(char Name[], Time in, Time out);

int main(){
	int i,select;
	
	Time in, out;
	
	in.hour = 8;
	in.min = 0;
	
	out.hour = 16;
	out.min = 0;
	
	printf("Time Sheet");
	printf("\n\nList of Employees:");
	
	for(i=1;i<=1;i++){
		printf("\n[%d] %s ",i,"GUIDO, CELSO JR., A");
	}
	
	printf("\n\nSelect Employee: ");
	scanf(" %d",&select);
	
	if(select==1){
		employeeTimeSheet("GUIDO, CELSO JR., A",in,out);
	}
	
	
}

void employeeTimeSheet(char Name[], Time in, Time out){
	int select;
	
	do{
		printf("\nEmployee Schedule: %02d:%02d - %02d:%02d", in.hour, in.min, out.hour, out.min);
	
		printf("\n[1] Time Sheet Record");
		printf("\n[2] Employee Time Stamp");
		printf("\n[0] <- Back");
		printf("\n\nSelect Option: ");
		scanf(" %d",&select);
		if(select==1){
			
		}else if(select==2){
			employeeTimeIn(Name, in, out);
		}
	}while(select != 0);
}

void employeeTimeIn(char Name[], Time in, Time out){
	printf("\nWew %s",Name);
	
	
	
}





