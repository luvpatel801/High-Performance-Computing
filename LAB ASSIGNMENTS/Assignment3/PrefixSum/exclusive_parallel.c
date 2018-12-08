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
	long long n=(65536),sum;
	int NTHREADS=4;
	long long I[n];
	long long O[n];
	generate(n, I);
	double t1,t2;
	t1=omp_get_wtime();
	omp_set_num_threads(0);
	long long d,i;
	for(d=0;d<=log2(n)-1;d++)
	{
		long long step=pow(2,d+1);
		#pragma omp parallel for shared(d,n,I,O,sum,step) private(i)
		for(i = 0; i < n; i+=step)
		{
			I[i+step-1]=I[i+(step/2)-1]+I[i+step-1];
		}
	}
	long long total=I[n-1];
	I[n-1]=0;
	for(d=log2(n)-1;d>=0;d--)
	{
		long long step=pow(2,d+1);
		#pragma omp parallel for shared(d,n,I,O,sum,step) private(i)
		for(i = 0; i < n; i+=step)
		{
			long long t=I[i+(step/2)-1];
			I[i+(step/2)-1]=I[i+step-1];
			I[i+step-1]=t+I[i+step-1];
		}
	}
	t2=omp_get_wtime();
	// print(I,n);
	printf("%f\n",t2-t1);
}
