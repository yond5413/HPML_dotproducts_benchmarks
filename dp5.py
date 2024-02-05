import numpy as np
import time 
import sys 
def dp(N,A,B):
    R = 0.0
    R = np.dot(A,B)
    for j in range(0,N):
        R += A[j]*B[j]  #### change to np.dot
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
        #print(f"total: {total}, curr_time: {times[k]}, k: {k}")
        if (k<= half):
            #print(f"total: {total}, curr_time: {times[k]}")
            total += times[k]
    exec_time = total/half
    print(exec_time)
    b = (8*N*iterations)/(exec_time)#8*(iterations*N)/(exec_time)#3float()
    F = (2.0*N*iterations)/exec_time
    ### convert to giga 
    b = b*10**-9
    F = F*10**-9
    print(f"N: {N}, <T>: {exec_time} sec, B: {b} GB/S, F: {F} GFLOP/sec")