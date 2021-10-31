#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 64
typedef struct{
	int ID;
	//int employeeID;
	
	char Name[20]; // For Now rani
	float monthlyRate; // Fixed Wage
	float dailyRate; // Needs Calculation

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

typedef struct{
	PayRoll Payroll[MAX];
	int count;
}PayList;

void initPayRoll(PayRoll *P);
void displayPayRoll(PayList P);
void displayEmployeePayroll(PayRoll A);
void employeePayrollMenu(PayRoll *A);
void payrollHeader();
void displayPaySlip(PayRoll A);

void editDays(int *A);
void editAdjustments(float *);
float calculateTax(float);
float calculateSSS(float);
float calculatePagibig(float pay);
float calculatePhilhealth(float pay);

void updateRecord(PayRoll *A);

PayList populatePayList(char filename[]);

int main(){
	int i,select;
	
	PayList P = populatePayList("payroll.bin");
	P.count = 3;
	initPayRoll(&P.Payroll[0]);
	initPayRoll(&P.Payroll[1]);
	initPayRoll(&P.Payroll[2]);
	P.Payroll[0].ID = 1000;
	P.Payroll[1].ID = 1001;
	P.Payroll[2].ID = 1002;
	strcpy(P.Payroll[0].Name, "CAPAO, BONA MARIE");
	strcpy(P.Payroll[1].Name, "GUIDO, CELSO JR.");
	strcpy(P.Payroll[2].Name, "VILLANUEVA, SEB");
	
	displayPayRoll(P);	
}

PayList populatePayList(char filename[]){	
	PayList L;
	PayRoll S;
	FILE *fptr;
	L.count = 0;
	fptr = fopen(filename,"ab");
	if(fptr!=NULL){	 	
	 	while(fread(&S,sizeof(PayRoll),1,fptr)&&L.count<MAX){
	 		L.Payroll[L.count++] = S;
		}
		fclose(fptr);
	}
	return L;
}

void initPayRoll(PayRoll *P){
	if(P != NULL){
		P->ID=0;
		//P->Payroll[i].employeeID=0;
		P->monthlyRate=0; 		// Fixed Wage
		P->dailyRate=500; 		// Needs Calculation
		P->daysDuty=0;
		P->daysAbsent=0;
		P->daysLate=0;
		P->grossPay=0;
		P->PhilHealth=0; 		//If 10k below : 350, 70k up : 2450, 10k - 70k : 3.50%
		P->PagIbig=0;			// 2% from employee
		P->SSS=0; 				// Monthly Compensation * 4.5%
		P->Tax=0;				// Table sent sa GC
		P->adjustment=0; 		// Default 0;
		P->totalDeduction=0; 	//Based on Late
		P->netPay=0;
	}
}

void displayPayRoll(PayList P){
	int i,select,input;
	
	printf("\nPAYROLL RECORD");
	payrollHeader();
	for(i=0;i<P.count;i++){
		displayEmployeePayroll(P.Payroll[i]);
	}
	
	do{
		printf("\n\n[1] Select Employee");
		printf("\n[0] <- Back");
		printf("\nSelect Option:");
		scanf(" %d",&select);
	}while(select < 0 || 1 < select);
	
	while(select==1){
		printf("\nEnter Employee ID: ");
		scanf(" %d", &input);
		for(i=0;i<P.count && P.Payroll[i].ID != input;i++){}
		if(i!=P.count){
			employeePayrollMenu(&(P.Payroll[i]));
		}
	}
}

void employeePayrollMenu(PayRoll *A){
	int select;
	
	printf("\nEmployee Pay Roll");
	payrollHeader();
	displayEmployeePayroll(*A);	
	displayPaySlip(*A);	
	do{
		printf("\n\n[1] Edit Employee's Days Duty (DD)");
		printf("\n[2] Edit Employee's Days Absent (DD)");
		printf("\n[3] Edit Employee's Days Late (DD)");
		printf("\n[4] Edit Employee's Adjustment");
		printf("\n[0] <-Back");
		printf("\n\nSelect Option: ");
		scanf(" %d",&select);
	}while(select < 0);
	
	switch(select){
		case 1:
			editDays(&(A->daysDuty));
			updateRecord(A);
			break;
		case 2:
			editDays(&(A->daysAbsent));
			updateRecord(A);
			break;
		case 3:
			editDays(&(A->daysLate));
			updateRecord(A);
			break;
		case 4:
			editAdjustments(&(A->adjustment));
			updateRecord(A);
			break;
		default:
			break;
	}
}

void editDays(int *A){
	int input;
	do{
		printf("\nEnter Days: ");
		scanf(" %d",&input);
	}while(input < 0);
	
	*A = input;
}

void editAdjustments(float *A){
	float input;
	do{
		printf("\nEnter Adjustment: ");
		scanf(" %f",&input);
	}while(input < 0);
	
	*A = input;
}

void payrollHeader(){
	printf("\n\n%8s|%18s|%9s|%12s|%2s|%2s|%2s|%12s|%10s|%12s|%7s|%12s|%10s|%12s|%12s|","EMP ID","EMPLOYEE NAME","EMP TYPE","SALARY","DD","DA","DL","GROSS PAY","PHILHEALTH",
		"PAG-IBIG","SSS","TAX","ADJUSTMENT","DEDUCTIONS","NET PAY");
}

void displayEmployeePayroll(PayRoll A){
	printf("\n%8d|%18s|%9.2f|%12.2f|%2d|%2d|%2d|%12.2f|%10.2f|%12.2f|%7.2f|%12.2f|%10.2f|%12.2f|%12.2f|",A.ID,A.Name,		
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

void updateRecord(PayRoll *A){
	
	if(1){
		A->grossPay = A->daysDuty * A->dailyRate;
		A->totalDeduction = A->daysLate * 100;
	}else{	
		A->grossPay = A->dailyRate;	
	}
	
	
	A->SSS = calculateSSS(A->grossPay);
	A->PhilHealth = calculatePhilhealth(A->grossPay);
	A->PagIbig = calculatePagibig(A->grossPay);
	A->Tax = calculateTax(A->grossPay);
		
	A->netPay = A->grossPay - A->SSS - A->PhilHealth - A->PagIbig - A->Tax + A->adjustment;
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

float calculatePhilhealth(float pay){
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

void displayPaySlip(PayRoll A){
	printf("\n\nPAYSLIP\n");
	printf("\nEmployee ID%8d\nName%30s",A.ID,A.Name);
	printf("\n---------------------------------------------\n");
	printf("%45c\n%45c\nDays Duty%20d%16c\nDays Absent%18d%16c\nDays Late%20d%16c\n%45c\nGross Pay%29.2f%7c",
		'|',
		'|',
		A.daysDuty,
		'|',
		A.daysAbsent,
		'|',
		A.daysLate,
		'|',
		'|',
		A.grossPay,
		'|'
		);
	printf("\n---------------------------------------------\n");
	printf("%45c\n%45c\nPhilHealth%22.2f%13c\nPagIbig%25.2f%13c\nSSS%29.2f%13c\nTAX%29.2f%13c\nAdjustment%22.2f%13c\nTotal Deduction%17.2f%13c\n%45c\nNet Pay%31.2f%7c",
		'|',
		'|',
		A.PhilHealth,
		'|',
		A.PagIbig,
		'|',
		A.SSS,
		'|',
		A.Tax,
		'|',
		A.adjustment,
		'|',
		A.totalDeduction,
		'|',
		'|',
		A.netPay,
		'|');
	printf("\n---------------------------------------------\n");
}

