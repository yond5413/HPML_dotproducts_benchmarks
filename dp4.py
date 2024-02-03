import numpy as np
import time 
print(f"Update N to be received from command line")
N = 1000
A = np.ones(N,dtype=np.float32)
B = np.ones(N,dtype=np.float32)
# for a simple loop
def dp(N,A,B):
    R = 0.0
    for j in range(0,N):
        R += A[j]*B[j]
    return R