#include<stdio.h>
#include<omp.h>

double pi_calculate(long int n){
	double sum=0.0,factor=1.0;
	long int k;
	
	for(k=0;k<n;k++){
		sum=sum+(factor/(2*k+1));
		factor=-factor;
	}
	return 4.0*sum;
}

int main(){
	long int n;
	double pi,start,end;
	scanf("%ld",&n);
	
	start=omp_get_wtime();
	pi=pi_calculate(n);
	end=omp_get_wtime();
	
	printf("Pi: %.12f Time: %.12f\n",pi,(end-start));
	return 0;
}
