#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	double t1,t2;
	t1=omp_get_wtime();
	double x,y;
	struct drand48_data drand_buf;
	long long iter=1000000000, i, in=0;
	int my_rank,source, dest=0;	// For message passing
	int tag;
	int numprocs;

	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	long long local_in=0;
	srand48_r (time(NULL), &drand_buf);
	for (i = 0; i < iter/numprocs; ++i)
	{
		drand48_r (&drand_buf, &x);
		drand48_r (&drand_buf, &y);
		if(sqrt((x*x)+(y*y))<1)
			local_in++;
	}
	MPI_Reduce(&local_in, &in, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	if(my_rank==0){
		t2=omp_get_wtime();
		printf("pi: %lf\ntime: %.12lf\n",4*((double)in/(double)iter),t2-t1);
	}

	MPI_Finalize();
	return 0;
}