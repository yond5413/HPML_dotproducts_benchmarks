#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
Just for rn ig 
*/
/// C1 -> ask about making a benchmarks ig
///FLOPS: hw performance counters for FLOP divided by time
// ie floating point operations per second?
//// GB/s hw perfomance counters for memory-ops divided
/////from slides
float dp(long N, float *pA, float *pB){
    float R = 0.0;
    int j; 
    for (j=0;j<N;j++){
        R += pA[j]*pB[j];
    }
    return R;
}

int main( int argc, char *argv[] ){
    //printf("Hello World");
    if( argc == 3 ) {
      printf("The arguments supplied are %s  %s \n", argv[1],argv[2] );
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
        float ta_advice; ta_advice = dp(vec_size,vec1,vec2);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("TA advice or declare volatile? %f \n", ta_advice);
        /*
        from slides
        double time_usec=(((double)end.tv_sec *1000000 + (double)end.tv_nsec/1000)
            - ((double)start.tv_sec *1000000 + (double)start.tv_nsec/1000));
        */
        completed_time[j] = ((double)end.tv_sec*1000000+(double)end.tv_nsec/1000) - ((double)start.tv_sec *1000000 + (double)start.tv_nsec/1000);
    }
    
    // for execution time need arithmetic mean
    double exec_time = 0;
    double half = measurements/2;
    //printf("idk what instructions are asking so heres completed_time array \n");
    for(int k = 0; k<measurements;k++){
        //printf("%f \n", completed_time[k]);
        if(k<= half){
            exec_time += completed_time[k];
        }
    }
    ////
    /*
        -compute mean using arithmetic mean for execution times 
        - F: arithemtic operations ie 3*iterations/ execution time?
        - B: input size of vectors / execution time 
        - <T>: execution time 
    */
    exec_time /= half;
    exec_time *=0.000001; //for microseconds 
    float b = 8.0/(100000000*exec_time);//sizeof(float)*(measurements*vec_size);
    float F = 2.0/exec_time;
    printf("N: %d, <T>: %f sec, B: %f GB/s, F: %f FLOP/sec \n", vec_size,exec_time,b,F);
    return 0;
   }
   else {
      printf("Insufficent amount of arguments supplied expecting 3.\n");
    return 1;
   }   
}
