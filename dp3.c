#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mkl_cblas.h>
///C3 

float bdp(long N, float *pA, float *pB) {
    float R = cblas_sdot(N, pA, 1, pB, 1);
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