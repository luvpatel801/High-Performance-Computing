#include <stdio.h>
#include <omp.h>
#include <math.h>
// #define num_steps 1000000000
#define NTHREADS 4
// double f(double x)
// {
//     return (4.0/(1.0+x*x));
// }

int main(int argc, char *argv[])
{
    double t1,t2;
    t1=omp_get_wtime();
    long long int num_steps=atoll(argv[1]);
    // scanf("%lf",&num_steps);
    printf("Steps = %d\n",(int)num_steps);
    int i;
    double step = 1.0/(double) num_steps;
    double sum[NTHREADS];
    double pi=3*step;
    // #pragma omp parallel num_threads(2)
    // omp_set_num_threads(NTHREADS);
    #pragma omp parallel num_threads(NTHREADS)
    {
        int ID=omp_get_thread_num();
        double x;
        sum[ID]=0.0;
        int i;
        //for(i=(ID*num_steps)/NTHREADS;i<((ID+1)*num_steps)/NTHREADS;i++)
        #pragma omp for
        for(i=1;i<=num_steps-1;i++)
        {
         x=(i)*step;
         sum[ID]=sum[ID]+(4.0/(1.0+(x*x)));
         
        }
        sum[ID]=sum[ID]*step;
        printf("ID = %d ; sum = %.12f\n",omp_get_thread_num(),sum[ID]);
    }
    int j;
    for(j=0;j<NTHREADS;j++)
        pi +=sum[j];
    printf("Pi = %.10f\n", pi);
    t2=omp_get_wtime();
    printf("Time %0.12f\n",t2-t1);
    return 0;
}
