/* Input size till 10^6 */

#include<stdio.h>
#include<omp.h>
#define SIZE 10000
#define NTHREADS 4

void initialize(long long int *arr,long long int n){ // Create worst case scenario for bubble sort - DO NOT PARALLELIZE
	long long int i,j;
	for(i=0;i<n;i++){
		arr[i]=n-i; // N to 1 stored in decreasing order
	}
}

void sort(long long int *arr,long long int n){
	long long int i,exch=1,start=0;
	
	while(exch||start){
		int ID=omp_get_thread_num();
		exch=0;
		#pragma omp parallel num_threads(NTHREADS)
		{
			for(i=(start+2*ID);i<=((n-1)/NTHREADS);i=i+2){
				#pragma omp critical
				{
					if(arr[i]>arr[i+1]){
						long long int temp=arr[i+1];
						arr[i+1]=arr[i];
						arr[i]=temp;
						exch=1;
					}
				}
			}
		}
		start=1-start;
	}
}

void print(long long int *arr,long long int n){
	long long int i;
	for(i=0;i<n;i++)
		printf("%lld ",arr[i]);
	printf("\n");
}

int main(){
	long long int arr[SIZE];
	double start, end;
	initialize(arr,SIZE);
	
	start=omp_get_wtime();
	sort(arr,SIZE);
	end=omp_get_wtime();
	
	print(arr,SIZE);
	printf("Time: %0.12f\n",(end-start));
	return 0;
}
