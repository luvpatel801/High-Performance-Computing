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
    // double sum[NTHREADS];
    double pi=3*step;
    // #pragma omp parallel num_threads(2)
    // omp_set_num_threads(NTHREADS);
    #pragma omp parallel num_threads(NTHREADS)
    {
        int ID=omp_get_thread_num();
        double x;
        double sum=0.0;
        //#pragma omp for
        int i;
        //for(i=(ID*num_steps)/NTHREADS;i<((ID+1)*num_steps)/NTHREADS;i++)
        for(i=ID+1;i<=num_steps-1;i=i+NTHREADS)
        {
         x=(i)*step;
         sum=sum+(4.0/(1.0+(x*x)));
         
        }
        sum=sum*step;
        printf("ID = %d ; sum = %.12f\n",omp_get_thread_num(),sum);
        #pragma omp atomic
            pi +=sum;
        
    }
    printf("Pi = %.10f\n", pi);
    t2=omp_get_wtime();
    printf("Time %0.12f\n",t2-t1);
    return 0;
}
