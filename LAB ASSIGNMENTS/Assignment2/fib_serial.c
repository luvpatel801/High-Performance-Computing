/* ASSUMPTION - INPUT SIZE GREATER THAN 2 - answer becomes after n=92*/

#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

void printFib(long long int *arr,long long int size){
	long int i;
	for(i=0;i<size;i++)
		printf("%lld ",arr[i]);
	printf("\n");
}

long long int *getFib(long long int n){
	long long int *arr=(long long int *)malloc(sizeof(long long int)*n); 
	long long int i;
	arr[0]=arr[1]=1;
	
	for(i=2;i<n;i++)
		arr[i]=arr[i-1]+arr[i-2];
		
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
