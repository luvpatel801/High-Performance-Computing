#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]){
	if(argc<3){
		printf("ARGUMENT COUNT IS 2\n");
		exit(1);
	}

	srand(time(NULL));
	
	long long int iterations=atoi(argv[1]);
	double t2,t1=omp_get_wtime();
	long long int inside=0;
	long long int i;
	double *arr;
	arr=malloc(atoi(argv[2])*sizeof(double));
	
	for(i=0;i<atoi(argv[2]);i++)
		arr[i]=0;

	#pragma omp parallel num_threads(atoi(argv[2]))
	{
		for(i=0;i<iterations/atoi(argv[2]);i++){
			double x,y;
		
			x=(double)rand() / (double)RAND_MAX ;
			y=(double)rand() / (double)RAND_MAX ;
			x=x*2;
			y=y*2;
		
			x=x-1;
			y=y-1;
			double d=((x*x)+(y*y));
			if(d<=1.0){
				arr[omp_get_thread_num()]++;
			}
		}
	}

	for(i=1;i<atoi(argv[2]);i++)
		arr[0]=arr[0]+arr[i];

	inside=arr[0];

	double pi = (((double)inside)/((double)(iterations)))*4;
	t2=omp_get_wtime();
	printf("%lf %lf\n",pi,(t2-t1));
}
