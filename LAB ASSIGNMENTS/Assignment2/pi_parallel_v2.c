/* Usimg "parallel for" and array for global sum */

#include<stdio.h>
#include<omp.h>
#include<math.h>
#define NTHREADS 4

double pi_calculate(long int n){
	double sum[NTHREADS];
	int i;
	#pragma omp parallel num_threads(NTHREADS)
	{	
		double factor=1.0;
		long int k;
		int ID=omp_get_thread_num();
		sum[ID]=0;
			
		#pragma omp for
		for(k=0;k<n;k++){
			sum[ID]=sum[ID]+(pow(-1,k)*factor/(2*k+1));	// Since omp assigns threads randomly, no other way to decide "factor"
		}
		
	}
	for(i=1;i<NTHREADS;i++){
		sum[0]=sum[0]+sum[i];
	}
	return 4.0*sum[0];
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
