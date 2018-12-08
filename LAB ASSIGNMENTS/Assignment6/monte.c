#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double* generateCoordinates();
double findDistance(double*);
double getValue(long long int);

int main(int argc, char const *argv[]){
	if(argc<2){
		printf("TOO FEW ARGUMENTS\n");
		exit(1);
	}

	long long int iterations=atoi(argv[1]);
	printf("%lf\n",getValue(iterations));

	return 0;
}

double* generateCoordinates(){
	double c[2];
	srand(time(NULL));
	c[0]=((double)rand())/((double)RAND_MAX);
	srand(time(NULL));
	c[1]=((double)rand())/((double)RAND_MAX);

	return c;
}

double findDistance(double c[2]){
	return ((c[0]*c[0])+(c[1]*c[1]));
}

double getValue(long long int iterations){
	long long int i,inside=0,outside=0;
	double ans;
	for(i=0;i<iterations;i++){
		if(findDistance(generateCoordinates())<=1.0)
			inside++;
		else
			outside++;
	}
	ans=(double)inside/((double)(inside+outside));	// = pi/4

	return 4*ans;
}