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
    double mean_time = 0;
    double exec_time = 0; 
    double half = measurements/2;
    //printf("idk what instructions are asking so heres completed_time array \n");
    for(int k = 0; k<measurements;k++){
        //printf("%f \n", completed_time[k]);
        exec_time += completed_time[k];
        if(k<= half){
            mean_time += completed_time[k];
        }
    }
    ////
    /*
        -compute mean using arithmetic mean for execution times 
        - F: arithemtic operations ie 3*iterations/ execution time?
        - B: input size of vectors / execution time 
        - <T>: execution time 
    */
    mean_time /= half;
    mean_time *=0.000001; //for microseconds 
    exec_time *= 0.000001;
    // harmonic mean appropriate as stated in notes
    // don't use mean time for calculations
    //float b = 8/exec_time; //8.0*(measurements*vec_size)/exec_time;//2*sizeof(float)*(measurements*vec_size);
    float b = (2*sizeof(float)*(measurements*vec_size))/exec_time;
    //sizeof(float)*(measurements*vec_size)/exec_time;
    // GB/s 
    //float F = 2.0/exec_time;
    float F = (2.0*measurements*vec_size)/exec_time;
    b *= 1.0E-09;
    F *= 1.0E-09;
    // N = vec_size
    // (instructions*N*measurements)/exec_time;  
    // use actual exectime instead of mean time for Bandwidth and throughput
    printf("N: %d, <T>: %f sec, B: %f GB/s, F: %f GFLOP/sec \n", vec_size,mean_time,b,F);
    return 0;
   }
   else {
      printf("Insufficent amount of arguments supplied expecting 3.\n");
    return 1;
   }   
}





/*
q1-> caching and etc is ingnored in system performance for dot product benchmark 
*/