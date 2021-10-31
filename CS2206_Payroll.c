#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

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
	
	float monthlyRate; // Fixed Wage
	float dailyRate; // Needs Calculation
	
	timeStamp TimeSheet[MAX];
	int daysCount;//1-15 , 16 to [28,29,30,31]
	
	int daysDuty;
	int daysAbsent;
	int daysLate;
	
	float grossPay;
	float PhilHealth; //If 10k below : 350, 70k up : 2450, 10k - 70k : 3.50%
	float PagIbig;// 2% from employee
	float SSS; // Monthly Compensation * 4.5%
	float Tax; // Table sent sa GC
	float adjustment; // Default 0;
	float totalDeduction; //Based on Late
	float netPay;
	
}PayRoll;

void initPayRoll(PayRoll payroll[], int count);

void employeeTimeSheet(char Name[], Time in, Time out,PayRoll payroll[]);
void employeeTimeIn(char Name[], Time in, Time out);

void initTimeSheet(timeStamp A[]);
void setTime(Time *A,int hour, int min);
void setDate(Date *A,int month, int day, int year);

void displayTimeSheet(timeStamp A[]);
void displayPayRoll(PayRoll payroll[]);
void displayEmployeePayroll(PayRoll A);

float calculateTax(float);
float calculateSSS(float);
int main(){
	int i,select;
	
	PayRoll payroll[2];
		
	Time in, out;
	
	in.hour = 8;
	in.min = 0;
	
	out.hour = 16;
	out.min = 0;
	
	initPayRoll(payroll,2);
	displayPayRoll(payroll);
	
//	printf("Time Sheet");
//	printf("\n\nList of Employees:");
//	
//	for(i=1;i<=1;i++){
//		printf("\n[%d] %s ",i,"GUIDO, CELSO JR., A.");
//	}
//	
//	printf("\n\nSelect Employee: ");
//	scanf(" %d",&select);
//	
//	if(select==1){
//		employeeTimeSheet("GUIDO, CELSO JR., A",in,out, payroll);
//	}
	
	
}

void initPayRoll(PayRoll payroll[], int count){
	int i;
	
	for(i=0;i<count;i++){
		payroll[i].ID=0;
		payroll[i].employeeID=0;
		
		payroll[i].monthlyRate=0; // Fixed Wage
		payroll[i].dailyRate=0; // Needs Calculation
		
		payroll[i].daysCount=15;//1-15 , 16 to [28,29,30,31]
		
		payroll[i].daysDuty=0;
		payroll[i].daysAbsent=0;
		payroll[i].daysLate=0;
		
		payroll[i].grossPay=0;
		payroll[i].PhilHealth=0; //If 10k below : 350, 70k up : 2450, 10k - 70k : 3.50%
		payroll[i].PagIbig=0;// 2% from employee
		payroll[i].SSS=0; // Monthly Compensation * 4.5%
		payroll[i].Tax=0; // Table sent sa GC
		payroll[i].adjustment=0; // Default 0;
		payroll[i].totalDeduction=0; //Based on Late
		payroll[i].netPay=0;
		initTimeSheet(payroll[i].TimeSheet);
	}
}

void initTimeSheet(timeStamp A[]){
	int i;
	for(i=0;i<MAX;i++){
		setDate(&(A[i].current),1,1,2000);
	
		A[i].isLate = 0;
		
		setTime(&(A[i].timeIn),0,0);
		setTime(&(A[i].timeOut),0,0);
		
		setTime(&(A[i].overtime),0,0);
		setTime(&(A[i].underTime),0,0);
		setTime(&(A[i].totalTime),0,0);
	}

}

void setTime(Time *A,int hour, int min){
	A->hour = (hour==24)? A->hour : hour;
	A->min = (min==60)? A->min : min;
}

void setDate(Date *A,int month, int day, int year){
	A->month = month;
	A->day = day;
	A->year = year;
}

void employeeTimeSheet(char Name[], Time in, Time out, PayRoll payroll[]){
	int select;
	
	do{
		printf("\nEmployee Schedule: %02d:%02d - %02d:%02d", in.hour, in.min, out.hour, out.min);
	
		printf("\n[1] Time Sheet Record");
		printf("\n[2] Employee Time Stamp");
		printf("\n[0] <- Back");
		printf("\n\nSelect Option: ");
		scanf(" %d",&select);
		if(select==1){
			displayTimeSheet(payroll[0].TimeSheet);
		}else if(select==2){
			employeeTimeIn(Name, in, out);
		}
	}while(select != 0);
}

void employeeTimeIn(char Name[], Time in, Time out){
	printf("\nWew %s",Name);
	
}

void displayTimeSheet(timeStamp stamp[]){	
	int i;
	
	
	printf("\nTIMESHEET RECORD");
	printf("\n\n%20s | %6s   |  %2s   |   %2s   |  %s  |%s |%s| %s ","NAME", "DATE", "IN", "OUT", "TOTAL", "OVERTIME", "UNDERTIME","LATE");
	for(i=0;i<16;i++){
		printf("\n%20s | %d/%d/%d | %02d:%02d |  %02d:%02d  |  %02d:%02d  |  %02d:%02d  |  %02d:%02d  | %d ","GUIDO, CELSO JR., A.", stamp[i].current.month, stamp[i].current.day,stamp[i].current.year,
																				stamp[i].timeIn.hour, stamp[i].timeIn.min, stamp[i].timeOut.hour, stamp[i].timeOut.min, stamp[i].totalTime.hour, stamp[i].totalTime.min, stamp[i].overtime.hour, stamp[i].overtime.min, stamp[i].underTime.hour, stamp[i].underTime.min,stamp[i].isLate);
	}
}

void displayPayRoll(PayRoll payroll[]){
	int i,select;
	
	printf("\nPAYROLL RECORD");
	printf("\n\n%8s|%18s|%12s|%12s|%2s|%2s|%2s|%12s|%10s|%12s|%7s|%12s|%10s|%12s|%12s|","EMP ID","EMPLOYEE NAME","MONTHLY PAY","DAILY PAY","DD","DA","DL","GROSS PAY","PHILHEALTH",
		"PAG-IBIG","SSS","TAX","ADJUSTMENT","DEDUCTIONS","NET PAY");
	for(i=0;i<2;i++){
		displayEmployeePayroll(payroll[i]);
	}
	
	do{
		printf("\n\n[0] <- Back");
		printf("\nSelect Option:");
		scanf(" %d",&select);
	}while(select!=0);
}

void displayEmployeePayroll(PayRoll A){
	printf("\n%8d|%18s|%12.2f|%12.2f|%2d|%2d|%2d|%12.2f|%10.2f|%12.2f|%7.2f|%12.2f|%10.2f|%12.2f|%12.2f|",A.ID,"Name Name",		
		A.monthlyRate,
		A.dailyRate,
		A.daysDuty,
		A.daysAbsent,
		A.daysLate,
		A.grossPay,
		A.PhilHealth,
		A.PagIbig,
		A.SSS,
		A.Tax,
		A.adjustment ,
		A.totalDeduction,
		A.netPay);
}


float calculateSSS(float pay){
	float modulo;
	float retVal;
	
	if(pay < 3250){
		retVal = 3000;
	}else if(pay >= 24750){
		retVal = 20000;
	}else{
		modulo = fmod(pay,1000);
		
		if(250 > modulo){
			retVal = pay - modulo;
		}else if(modulo >= 750){
			retVal = (pay - modulo) + 1000;
		}else{
			retVal = (pay - modulo) + 500;
		}
	}
	
	return retVal * .045;
}

float calculateTax(float pay){
	float retVal;
	
	if(pay < 10416 ){
		retVal = 0;
	}else if(pay <= 16666){
		retVal = (pay - 10416) * .20;
	}else if(pay <= 33333){
		retVal = ((pay - 1666) * .25 ) + 1250;
	}else if(pay <= 83333){
		retVal = ((pay - 33333) * .30 ) + 5416;
	}else if(pay <= 333333){
		retVal = ((pay - 83333) * .32 ) + 20416;
	}else{
		retVal = ((pay - 333333) * .35 ) + 100416;
	}
	
	return retVal;
}





