/* Input size till 10^6 */

#include<stdio.h>
#include<omp.h>
#define SIZE 10

void initialize(long long int *arr,long long int n){ // Create worst case scenario for bubble sort - DO NOT PARALLELIZE
	long long int i,j;
	for(i=0;i<n;i++){
		arr[i]=n-i; // N to 1 stored in decreasing order
	}
}

void sort(long long int *arr,long long int n){
	long long int i,j;
	
	for(i=0;i<n-1;i++){
		for(j=0;j<n-1-i;j++){
			if(arr[j]>arr[j+1]){
				long long int temp=arr[j+1];
				arr[j+1]=arr[j];
				arr[j]=temp;
			}
		}
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
