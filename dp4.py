import sys
import numpy as np
import time 
#print(f"Update N to be received from command line")
#N = 1000
#A = np.ones(N,dtype=np.float32)
#B = np.ones(N,dtype=np.float32)
# for a simple loop
def dp(N,A,B):
    R = 0.0
    for j in range(0,N):
        R += A[j]*B[j]
    return R

if __name__ == "__main__":
    N = int(sys.argv[1])
    iterations = int(sys.argv[2])
    A = np.ones(N,dtype=np.float32)
    B = np.ones(N,dtype=np.float32)
    times = list()
    for i in range(0,iterations):
        start = time.monotonic() #+ time.monotonic_ns()
        dp(N,A,B) 
        end = time.monotonic() #+ time.monotonic_ns()
        #print(f"exec time: {end-start}")
        times.append(end-start)
    total = 0
    half = iterations//2
    for k in range(0,iterations):
        if (k<= half):
            total += times[k]
    exec_time = total/half
    b = 8*(iterations*N)/(exec_time)#3float()
    F = 2.0/exec_time

    print(f"N: {N}, <T>: {exec_time} sec, B: {b} GB/S, F: {F} FLOP/sec")
    '''
    exec_time /= half;
    exec_time *=0.000001; //for microseconds 
    float b = 8.0/(100000000*exec_time);//sizeof(float)*(measurements*vec_k size);
    float F = 2.0/exec_time;
    printf("N: %d, <T>: %f sec, B: %f GB/s, F: %f FLOP/sec \n", vec_size,exec_time,b,F);
    return 0;
    '''