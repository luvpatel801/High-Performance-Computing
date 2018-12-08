#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <math.h>
// #define num_steps 1000000000
int main(int argc, char *argv[])
{

    double t1, t2, t3;
    t1=omp_get_wtime();
    long long int num_steps=atoll(argv[1]);
    // scanf("%lf",&num_steps);
    printf("Steps = %d\n",(int)num_steps);
    int i;
    double step = 1.0/(double) num_steps;
    double pi, sum = 3.0;
    t3=omp_get_wtime();
    for (i=1;i<= num_steps-1; i++){
        double x = (i)*step;
        sum = sum + (4.0/(1.0+x*x));
    }
    pi = step * sum;
    printf("Pi = %.10f\n", pi);
    t2=omp_get_wtime();
    double p=(t2-t3)/(t2-t1);
    double theo_speedup=1.0/((p/4)+(1-p));
    printf("Time %0.12f\n",t2-t1);
    printf("Theoretical_speedup  %.12f\n",theo_speedup);
    return 0;
}
