#include <stdio.h>
#include <math.h>
#include <omp.h>

int print(long long O[], long long n)
{
	long long i;
	for(i=0;i<n;i++)
	{
		printf("%lld ",O[i]);
	}
	printf("\n");
	return 0;
}

int generate(long long a[], long long n)
{
	srand(time(NULL));
	long long i;
	for(i=0;i<n;i++)
	{
		a[i]=(rand()%100);
	}
	return 0;
}

int main()
{
	long long n=(65536/2),con=50;
	int NTHREADS=4;
	long long a[n];
	generate(a,n);
	// print(a,n);
	double t1,t2;
	t1=omp_get_wtime();
	long long bit[n];
	long long I[n];
	long long out[n];
	long long i,j;
	#pragma omp parallel for num_threads(NTHREADS) shared(n,bit,a,con) private(i)
	for ( i = 0; i < n; ++i)
	{
		if(a[i]>con)
		{
			bit[i]=1;
			I[i]=1;
		}
		else
		{
			bit[i]=0;
			I[i]=0;
		}
	} 
	long long d;
	for(d=0;d<=log2(n)-1;d++)
	{
		long long step=pow(2,d+1);
		#pragma omp parallel for num_threads(NTHREADS) shared(d,n,I,step) private(i)
			for(i = 0; i < n; i+=step)
			{
				I[i+step-1]=I[i+(step/2)-1]+I[i+step-1];
			}
	}
	long long stride;
	for(stride=n/2;stride>=2;stride = stride/2)
	{
		#pragma omp parallel for num_threads(NTHREADS) shared(d,n,I,stride) private(i)
			for(i=stride-1; i<n; i += stride)
			{
				if(i+stride/2<n)
				{	
					I[i+(stride/2)] = I[i+(stride/2)] + I[i];
				}
			}
	}
	j=0;
	#pragma omp parallel for num_threads(NTHREADS) shared(out,n,I,a,j) private(i)
	for(i = 0; i < n; i++)
	{
		if(bit[i]==1)
		{
			// #pragma omp atomic
				j=j+1;
			
			out[I[i]-1]=a[i];
		}
	}

	t2=omp_get_wtime();
	// print(I,n);
	// print(out,j);
	printf("%f\n",t2-t1);
}