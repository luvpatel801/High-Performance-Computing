#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>

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
	long long a[n];
	generate(a,n);
	// print(a,n);
	double t1,t2;
	t1=omp_get_wtime();
	long long out[n];
	long long i,j=0;
	for ( i = 0; i < n; ++i)
	{
		if(a[i]>con)
			out[j++]=a[i];
	}
	t2=omp_get_wtime();
	// print(out,j);
	printf("%f\n",t2-t1);
}