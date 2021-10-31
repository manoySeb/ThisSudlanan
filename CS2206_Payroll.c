#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define T_LEN 256
#define MAX 16

typedef struct{
	int ID;
	//int employeeID;
	
	char Name[20]; // For Now rani
	
	float monthlyRate; // Fixed Wage
	float dailyRate; // Needs Calculation

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



void displayPayRoll(PayRoll payroll[], int count);
void displayEmployeePayroll(PayRoll A);
void employeePayrollMenu(PayRoll *A);

void payrollHeader();

float calculateTax(float);
float calculateSSS(float);
int main(){
	int i,select;
	
	PayRoll payroll[3];
	
	initPayRoll(payroll,3);
	strcpy(payroll[1].Name,"GUIDO, CELSO JR.");
	payroll[1].ID = 1;
	displayPayRoll(payroll, 3);	
}

void initPayRoll(PayRoll payroll[], int count){
	int i;
	
	for(i=0;i<count;i++){
		payroll[i].ID=0;
		//payroll[i].employeeID=0;
		
		payroll[i].monthlyRate=0; 		// Fixed Wage
		payroll[i].dailyRate=0; 		// Needs Calculation
		payroll[i].daysCount=15;		//1-15 , 16 to [28,29,30,31]
		payroll[i].daysDuty=0;
		payroll[i].daysAbsent=0;
		payroll[i].daysLate=0;
		payroll[i].grossPay=0;
		payroll[i].PhilHealth=0; 		//If 10k below : 350, 70k up : 2450, 10k - 70k : 3.50%
		payroll[i].PagIbig=0;			// 2% from employee
		payroll[i].SSS=0; 				// Monthly Compensation * 4.5%
		payroll[i].Tax=0;				// Table sent sa GC
		payroll[i].adjustment=0; 		// Default 0;
		payroll[i].totalDeduction=0; 	//Based on Late
		payroll[i].netPay=0;
	}
}

void displayPayRoll(PayRoll payroll[],int count){
	int i,select,input;
	
	printf("\nPAYROLL RECORD");
	payrollHeader();
	for(i=0;i<count;i++){
		displayEmployeePayroll(payroll[i]);
	}
	
	do{
		printf("\n\n[1] Select Employee");
		printf("\n[0] <- Back");
		printf("\nSelect Option:");
		scanf(" %d",&select);
	}while(select < 0 || 1 < select);
	
	if(select==1){
		printf("\nEnter Employee ID: ");
		scanf(" %d", &input);
		for(i=0;i<count && payroll[i].ID != input;i++){}
		if(i!=count){
			employeePayrollMenu(&(payroll[i]));
		}
	}
}

void employeePayrollMenu(PayRoll *A){
	int select;
	
	printf("\nEmployee Pay Roll");
	payrollHeader();
	displayEmployeePayroll(*A);	
	
	do{
		printf("\n\n[1] Employee Time Sheet");
		printf("\n[0] <-Back");
		printf("\nSelect Option: ");
		scanf(" %d",&select);
	}while(select < 0);
}

void payrollHeader(){
	printf("\n\n%8s|%18s|%12s|%12s|%2s|%2s|%2s|%12s|%10s|%12s|%7s|%12s|%10s|%12s|%12s|","EMP ID","EMPLOYEE NAME","MONTHLY PAY","DAILY PAY","DD","DA","DL","GROSS PAY","PHILHEALTH",
		"PAG-IBIG","SSS","TAX","ADJUSTMENT","DEDUCTIONS","NET PAY");
}

void displayEmployeePayroll(PayRoll A){
	printf("\n%8d|%18s|%12.2f|%12.2f|%2d|%2d|%2d|%12.2f|%10.2f|%12.2f|%7.2f|%12.2f|%10.2f|%12.2f|%12.2f|",A.ID,A.Name,		
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

float calculatePagibig(float pay){
	return pay * 0.02;
}

float calculatePhilHealth(float pay){
	float retVal;
	
	if(pay < 10000){
		retVal = 350;
	}else if(pay > 70000){
		retVal = 2450;
	}else{
		retVal = pay * 0.035;
	}
	
	return retVal;
}

