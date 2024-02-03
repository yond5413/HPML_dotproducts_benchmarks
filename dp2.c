#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
Just for rn ig 
*/
///FLOPS: hw performance counters for FLOP divided by time
// ie floating point operations per second?
//// GB/s hw perfomance counters for memory-ops divided
/////from slides
/// C2 
float dpunroll(long N, float *pA, float *pB){
    float R = 0.0;
    int j;
    for (j=0;j<N;j+=4)
        R += pA[j]*pB[j] + pA[j+1]*pB[j+1] \
        + pA[j+2]*pB[j+2] + pA[j+3] * pB[j+3];
    return R;
}

int main( int argc, char *argv[] )
{
    //printf("Hello World");
    if( argc == 3 ) {
      printf("The argument supplied is %s  %s \n", argv[1],argv[2] );
      int vec_size = atoi(argv[1]);
      int measurements = atoi(argv[2]);
    float *vec1 = (float * )malloc(vec_size*sizeof(float));
    float *vec2 = (float * )malloc(vec_size*sizeof(float));
    double *completed_time = (double *) malloc(measurements*sizeof(float));
        for(int i =0; i<vec_size;i++){
            vec1[i] = 1;
            vec2[i] = 1;
        }
    
    struct timespec start, end;
    for(int j = 0; j< measurements; j++ ){
        clock_gettime(CLOCK_MONOTONIC, &start); // not on windows 
        dp(vec_size,vec1,vec2);
        clock_gettime(CLOCK_MONOTONIC, &end);
        /*
        from slides
        double time_usec=(((double)end.tv_sec *1000000 + (double)end.tv_nsec/1000)
            - ((double)start.tv_sec *1000000 + (double)start.tv_nsec/1000));
        */
        completed_time[j] = ((double)end.tv_sec*1000000+(double)end.tv_nsec/1000) - ((double)start.tv_sec *1000000 + (double)start.tv_nsec/1000);
    }
    printf("idk what instructions are asking so heres completed_time array \n");

    for(int k = 0; k<measurements;k++){
        printf("%f \n", completed_time[k]);
    }
    return 0;
   }
   else {
      printf("Insufficent amount of arguments supplied expecting 3.\n");
    return 1;
   }   
}
