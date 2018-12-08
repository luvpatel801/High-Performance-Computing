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

int generate(long long n, long long a[])
{
	long long i;
	for(i=0;i<n;i++)
	{
		a[i]=i+1;
	}
	return 0;
}

int main()
{
	long long n=(262144);
	int NTHREADS=4;
	long long I[n];
	generate(n, I);
	// print(I,n);
	double t1,t2;
	t1=omp_get_wtime();
	long long d,i;
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
	t2=omp_get_wtime();
	// print(I,n);
	printf("%f\n",t2-t1);
}