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

void init_matrix(int m, int n, double *matrix){
	int i,j;
	for (i = 0; i < m; ++i)	{
		for (j = 0; j < n; ++j) {
			double tmp=rand()/33333333.3+1.0;
			matrix[i*n + j] = pow(-1,(int)tmp)*tmp;
		}
	}
}

int main(int argc, char const *argv[])
{
	if(argc<3){perror("Error. Please provide the m, n, k matrix size.\n"); return -1;}
	int MM=atoi(argv[1]);
	int NN=atoi(argv[2]);
	int KK=atoi(argv[3]);
	double *AA;
	double *BB;
	double *CC;
	AA = (double*) malloc (MM*NN*sizeof(double));
	BB = (double*) malloc (NN*KK*sizeof(double));
	CC = (double*) malloc (MM*KK*sizeof(double));

	//initialize the matrices A, B, and C
	init_matrix( MM, NN, AA);
	init_matrix( NN, KK, BB);
	init_matrix( MM, KK, CC);

    long long tm;
    float flop_per_clock,Gflop_per_s;
//-----------Call dgemm----------------------------------------------
 	char normal='N';
 	double one=1.0;
 	double zero=0.0;
	tm = readTSC();
    dgemm_(
    	&normal,//transa,
    	&normal,//transb,
    	&MM,//m,the number of row of the matrix op(A) and c
    	&KK,//n,the number of col of the matrix op(B) and c
    	&NN,//k,the of col of op(A) and the row of op(B)
    	&one,//alpha,
    	AA,//A,1D array
    	&MM,//lda,
    	BB,//b,1D array
    	&NN,//ldb,
    	&zero,//beta,
    	CC,//c,1D array
    	&MM);//ldc);
//-----------part--C----------------------------------------------
	tm = readTSC() - tm;
	//long long delta_clock = clock() - clk;
	//t_real = gtod() - t_real;
	flop_per_clock=(float)MM*KK*(NN*2.0-1)/tm;
	//Gflop_per_s=(float)num*num*num/t_real/pow(10,9);
	Gflop_per_s=flop_per_clock*2.7;
	printf("dgemm_:\n");
	printf("Flop_per_clock:   %15.6f \n",flop_per_clock);
    printf("Gflop_per_second: %15.6f \n", Gflop_per_s );


    free(AA);
    free(BB);
    free(CC);

    return 0;




    //printf(" clock:  %15lld  \n\n", delta_clock );


	//print the matrices A and B for verification.
	//for (i = 0; i < 2; ++i)
	//{
	//	for (j = 0; j < 2; ++j)
	//	{
	//		printf("%f\t", AA[i*num+j]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");
	//printf("\n");
	//for (i = 0; i < 2; ++i)
	//{
	//	for (j = 0; j < 2; ++j)
	//	{
	//		printf("%f\t", BB[i*num+j]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");
	//printf("\n");
	//for (i = 0; i < 2; ++i)
	//{
	//	for (j = 0; j < 2; ++j)
	//	{
	//		printf("%f\t", CC[i*num+j]);
	//	}
	//	printf("\n");
	//}

	//ijk----------------------------ijk--------------start-------------------
    //t_real = gtod();
	//for (i=0;i<num;++i){
	//	for (j = 0; j < num; ++j){
	//		CC[i+num*j]=0.0;
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
	//			CC[i+num*j]+=AA[i+num*k]*BB[k+num*j];
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
	//		printf("%f\t", CC[i*num+j]);
	//	}
	//	printf("\n");
	//}


}