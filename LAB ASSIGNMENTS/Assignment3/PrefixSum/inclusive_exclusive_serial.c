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
	long long n=(65536/2);
	long long sum;
	long long I[n];
	long long O[n];
	generate(n, I);
	double t1,t2;
	t1=omp_get_wtime();
	int x=1;
	if(x==0)
	{
		sum=0;
		O[0]=sum;
		long long i;
		for(i=1;i<n;i++)
		{
			O[i]=sum+I[i-1];
			sum=O[i];
		}
	}
	else
	{
		sum=I[0];
		O[0]=sum;
		long long i;
		for(i=1;i<n;i++)
		{
			O[i]=sum+I[i];
			sum=O[i];
		}
	}
	// print(O,n);
	t2=omp_get_wtime();
	printf("%f\n",t2-t1);
	return 0;
}
