#include <mpi.h>
#include <stdio.h>

double f(double x){
	return x*x;
}

int main(int argc, char *argv[]){
	double t1,t2;
	t1=MPI_Wtime();
	if(argc<4){
		printf("Low argument count\n");
	}
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	int n=atoi(argv[3]);
	int p;
	double local_a, local_b, local_n, integral, total,h;
	int my_rank,source, dest=0;	// For message passing
	int tag;
	MPI_Status status;

	MPI_Init(&argc,&argv);
	int i;
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	h=((double)(b-a)/(double)n);
	local_n=n/p;

	local_a=a+local_n*h*my_rank;
	local_b=local_a+local_n*h;

	integral=(f(local_a)+f(local_b))/2;
	for(i=1;i<local_n;i++){
		double temp=local_a+i*h;
		integral=integral+f(temp);
	}
	integral=integral*h;

	//printf("%d\n",p );

	if(my_rank==0){
		total=integral;
		for(source=1;source<p;source++){
			MPI_Recv(&integral,1,MPI_DOUBLE,source,tag,MPI_COMM_WORLD,&status);
			total=total+integral;
		}
	}
	else{
		MPI_Send(&integral,1,MPI_DOUBLE,dest,tag,MPI_COMM_WORLD);
	}
	if(my_rank==0){
		//printf("%lf\n",total);	// ANSWER

		t2=MPI_Wtime();
		printf("%d %lf\n",n,t2-t1);
	}

	MPI_Finalize();
	return 0;
}