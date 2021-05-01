#include <stdio.h>
#include <stdlib.h>

int Ps[3][100], realTimeCapacity[3][100], processNumber = 0, LCM;
void getSystem(){
	FILE *inputfile;
	inputfile = fopen("sys.txt","r");
	while(!feof(inputfile)){
		fscanf(inputfile,"%d %d %d", &Ps[0][processNumber], &Ps[1][processNumber], &Ps[2][processNumber]);
		processNumber++;
	}
}

int lcm(int t[], int tSize){
	int initialArray[100];
	for(int i=0;i<tSize;i++)
		initialArray[i] = t[i];
	
	int index,m,x,b = 1;
	while(b==1){
		b=0;
		x=t[0];
		m=t[0];
		index = 0;
		for(int i=0;i<tSize;i++){
			if(x!=t[i])
				b=1;
			if(m > t[i]){
				m = t[i];
				index = i;
			}
		}
		if(b == 1)
			t[index] = t[index] + initialArray[index];
	}
	return t[0];
}

int priorProcess(){
	int prior = -1, lessPeriode = LCM;
	for(int i=0;i<processNumber;i++){
		if(realTimeCapacity[0][i]!=0){
			if(lessPeriode > realTimeCapacity[2][i]){
				prior = i;
				lessPeriode = realTimeCapacity[2][i];
			}
		}
	}
	return prior;
}

void schedule(){
	int t,prior;
	printf("DEADLINE MONOTONIC SCHEDULING\n");
	for(int i=0;i<processNumber;i++){
		realTimeCapacity[0][i] = Ps[0][i];
		realTimeCapacity[1][i] = Ps[1][i];
		realTimeCapacity[2][i] = Ps[2][i];
	}
	for(t =0;t<LCM;t++){
		
		prior = priorProcess();
		if(prior != -1){
			printf("\n(%d-%d) | P%d",t,t+1,prior);
		}
		else{
			printf("\n(%d-%d) | -- ",t,t+1);
		}
		realTimeCapacity[0][prior]--;
		for(int i=0;i<processNumber;i++){
			realTimeCapacity[1][i]--;
			if(realTimeCapacity[1][i] == 0){
				realTimeCapacity[0][i] = Ps[0][i];
				realTimeCapacity[1][i] = Ps[1][i];
				realTimeCapacity[2][i] = Ps[2][i];
			}
		}
	}
}


int main(){
	int help[100];
	getSystem();
	float sum = 0;
	for(int i=0;i<processNumber;i++)
		sum += ((float)Ps[0][i]/(float)Ps[1][i]);
	if(sum>1)
		printf("System is not schedulable");

	for(int i=0;i<processNumber;i++)
		help[i] = Ps[1][i];
	LCM = lcm(help,processNumber);
	schedule();
}
