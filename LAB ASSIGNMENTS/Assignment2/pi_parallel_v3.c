/* Using "omp for" and atomic construct */

#include<stdio.h>
#include<omp.h>
#include<math.h>
#define NTHREADS 4

double pi_calculate(long int n){
	double pi=0.0;
	#pragma omp parallel num_threads(NTHREADS)
	{	
		long int k;
		double sum=0.0;
		double factor;
		
		int ID=omp_get_thread_num();
		
		if(ID%2==0)
			factor=1.0;
		else
			factor=-1.0;
		#pragma omp for
		for(k=0;k<n;k++){
			sum=sum+((pow(-1,k)*factor)/(2*k+1));
		}
		#pragma omp atomic
			pi=pi+sum;
	}
	return 4.0*pi;
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
