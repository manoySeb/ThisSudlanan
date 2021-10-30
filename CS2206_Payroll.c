#include <stdio.h>
#include <string.h>
#include <time.h>

#define T_LEN 256
#define MAX 15

typedef struct{
//	int ID;
//	Date curr_date;
//	Time Time_in;
//	Time Time_out;
//	Time Overtime;
//	Time UnderTime;
//	boolean isLate;
}timeStamp;

typedef struct{
	int ID;
	int employeeID;
	timeStamp sheet[MAX];
}timeSheet;

void employeeTimeSheet(char Name[], time_t schedule);
void employeeTimeIn(char Name[], time_t schedule);

int main(){
	int i,select;
	
	time_t sampleSched;

	sampleSched = time(&sampleSched);
	
	printf("Time Sheet");
	printf("\n\nList of Employees:");
	
	for(i=1;i<=1;i++){
		printf("\n[%d] %s ",i,"GUIDO, CELSO JR., A");
	}
	
	printf("\n\nSelect Employee: ");
	scanf(" %d",&select);
	
	if(select==1){
		employeeTimeSheet("GUIDO, CELSO JR., A",sampleSched);
	}
	
	
}

void employeeTimeSheet(char Name[], time_t schedule){
	int select;
	
//	struct tm *ptm = gmtime(&schedule);
	
//	printf("\nEmployee Schedule: %s",asctime(ptm));
	
	
	
	printf("\n[1] Time Sheet Record");
	printf("\n[2] Employee Time Stamp");
	printf("\n\nSelect Option: ");
	scanf(" %d",&select);
	if(select==0){
		
	}else if(select==2){
		employeeTimeIn(Name,schedule);
	}
	
}

void employeeTimeIn(char Name[], time_t schedule){
	printf("\nWew %s",Name);
	
	
	
}





