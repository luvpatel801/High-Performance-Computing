/* ASSUMPTION - INPUT SIZE GREATER THAN 2 - answer becomes after n=92*/

#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#define NTHREADS 4

void printFib(long long int *arr,long long int size){
	long int i;
	for(i=0;i<size;i++)
		printf("%lld ",arr[i]);
	printf("\n");
}

long long int fib(long long int n){
	long long int i, j;
	if (n==1)
		return 1;
	if(n==0)
		return 1;
	else{
		#pragma omp task shared(i) firstprivate(n)
			i=fib(n-1);

		#pragma omp task shared(j) firstprivate(n)
			j=fib(n-2);

		#pragma omp taskwait
			return i+j;
	}
}

long long int *getFib(long long int n){
	long long int *arr=(long long int *)malloc(sizeof(long long int)*n); 
	long long int i;
	arr[0]=arr[1]=1;
	
	#pragma omp parallel for num_threads(NTHREADS)
	for(i=2;i<n;i++){
		if(arr[i-1]==0)
			arr[i-1]=fib(i-1);

		if(arr[i-2]==0)
			arr[i-2]=fib(i-2);
		
		if(arr[i]==0)
			arr[i]=arr[i-1]+arr[i-2];
	}
		
	return arr;
}


int main(){
	long long int n,*arr;
	double start,end;
	scanf("%lld",&n);
	
	start=omp_get_wtime();
	arr=getFib(n);
	end=omp_get_wtime();
	
	printFib(arr,n);
	printf("Time: %0.12f\n",(end-start));
	return 0;
}
