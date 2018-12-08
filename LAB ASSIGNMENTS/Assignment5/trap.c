#include <stdio.h>
#include <mpi.h>

double f(double);

int main(int argc, char *argv[]){
	double t1,t2;
	t1=MPI_Wtime();
	if(argc<4){
		printf("Low argument count\n");
	}
	int a=atoi(argv[1]);	// start point
	int b=atoi(argv[2]);	// end point
	int n=atoi(argv[3]);	// no. of divisions

	//printf("a:%d b:%d n=%d\n",a,b,n);

	double h=((double)(b-a))/(double)n;
	double partial_sum=(f(a)+f(b))/2,sum=0;
	int i;

	for(i=1;i<n;i++){
		double temp=a+i*h;
		partial_sum+=f(temp);
	}
	sum=partial_sum*h;
	//printf("%lf\n",sum);	// ANSWER

	t2=MPI_Wtime();
	printf("%d %lf\n",n,t2-t1);
	return 0;
}

double f(double x){
	return x*x;
}
