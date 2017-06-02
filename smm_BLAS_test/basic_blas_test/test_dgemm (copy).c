#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "time.h"
#include "sys/time.h"


//volatile double gtod(void)
//{
//  static struct timeval tv;
//  static struct timezone tz;
//  gettimeofday(&tv,&tz);
//  return tv.tv_sec + 1.e-6*tv.tv_usec;
//}


long long readTSC(void)
{
 /* read the time stamp counter on Intel x86 chips */
  union { long long complete; unsigned int part[2]; } ticks;
  __asm__ ("rdtsc; mov %%eax,%0;mov %%edx,%1"
            : "=mr" (ticks.part[0]),
              "=mr" (ticks.part[1])
            : /* no inputs */
            : "eax", "edx");
  return ticks.complete;
}
void dgemm_(char *transa, char *transb, int *m, int *n, int *k, 
	double *alpha, double *matrixA, int *lda, double *matrixB, 
	int *ldb, double *beta, double *c, int *ldc);

int main(int argc, char const *argv[])
{
	int num=atoi(argv[1]);
	double *left_m;
	double *right_m;
	double *multi_m;
	left_m = (double*) malloc (num*num*sizeof(double));
	right_m= (double*) malloc (num*num*sizeof(double));
	multi_m= (double*) malloc (num*num*sizeof(double));

	//initialize the matrices A, B, and C
	int i,j,k;
	for (i=0;i<num;++i){
		for (j = 0; j < num; ++j){
			double tmp=rand()/33333333.3+1.0;
			left_m[i+num*j]=pow(-1,(int)tmp)*tmp;
			//left_m[i+num*j]=1.0;
			tmp=rand()/33333333.3+1.0;
			right_m[i+j*num]=pow(-1,(int)tmp)*tmp;
			//right_m[i+j*num]=1.0;
			multi_m[i+num*j]=0.0;
		}
	}

    double t_real;
    long long tm;
    float flop_per_clock,Gflop_per_s;
	


//-----------part--C----------------------------------------------
 	char normal='N';
 	double one=1.0;
 	double neg=-1.0;
 	double zero=0.0;
 	//clock_t clk;
	//clk=clock();
	tm = readTSC();
    dgemm_(
    	&normal,//transa,
    	&normal,//transb,
    	&num,//m,the number of row of the matrix op(A) and c
    	&num,//n,the number of col of the matrix op(B) and c
    	&num,//k,the of col of op(A) and the row of op(B)
    	&one,//alpha,
    	left_m,//A,1D array
    	&num,//lda,
    	right_m,//b,1D array
    	&num,//ldb,
    	&zero,//beta,
    	multi_m,//c,1D array
    	&num);//ldc);
//-----------part--C----------------------------------------------
	tm = readTSC() - tm;
	//long long delta_clock = clock() - clk;
	//t_real = gtod() - t_real;
	flop_per_clock=(float)num*num*(num*2.0-1)/tm;
	//Gflop_per_s=(float)num*num*num/t_real/pow(10,9);
	Gflop_per_s=flop_per_clock*2.7;
	printf("dgemm_:\n");
	printf("Flop_per_clock:   %15.6f \n",flop_per_clock);
    printf("Gflop_per_second: %15.6f \n", Gflop_per_s );
    //printf(" clock:  %15lld  \n\n", delta_clock );


	//print the matrices A and B for verification.
	//for (i = 0; i < 2; ++i)
	//{
	//	for (j = 0; j < 2; ++j)
	//	{
	//		printf("%f\t", left_m[i*num+j]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");
	//printf("\n");
	//for (i = 0; i < 2; ++i)
	//{
	//	for (j = 0; j < 2; ++j)
	//	{
	//		printf("%f\t", right_m[i*num+j]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");
	//printf("\n");
	//for (i = 0; i < 2; ++i)
	//{
	//	for (j = 0; j < 2; ++j)
	//	{
	//		printf("%f\t", multi_m[i*num+j]);
	//	}
	//	printf("\n");
	//}

	//ijk----------------------------ijk--------------start-------------------
    //t_real = gtod();
	//for (i=0;i<num;++i){
	//	for (j = 0; j < num; ++j){
	//		multi_m[i+num*j]=0.0;
	//	}
	//}
	//tm = readTSC();
	////multiplication C=A*B
	//for ( i = 0; i < num; ++i)
	//{
	//	for ( j = 0; j < num; ++j)
	//	{
	//		for ( k = 0; k < num; ++k)
	//		{
	//			multi_m[i+num*j]+=left_m[i+num*k]*right_m[k+num*j];
	//		}
	//	}
	//}
	//tm = readTSC() - tm;
	////t_real = gtod() - t_real;
	//flop_per_clock=(float)num*num*num*2.0/tm;
	////Gflop_per_s=(float)num*num*num/t_real/pow(10,9);
	//Gflop_per_s=flop_per_clock*2.7;
	//printf("My function Loop ijk:\n");
	//printf("Flop_per_clock:   %15.6f \n",flop_per_clock);
    //printf("Gflop_per_second: %15.6f \n\n", Gflop_per_s );
	//ijk----------------------------ijk--------------end-------------------


//print the matrices A and B for verification.
	//for (i = 0; i < 2; ++i)
	//{
	//	for (j = 0; j < 2; ++j)
	//	{
	//		printf("%f\t", multi_m[i*num+j]);
	//	}
	//	printf("\n");
	//}

	free(left_m);
	free(right_m);
	free(multi_m);

	return 0;
}