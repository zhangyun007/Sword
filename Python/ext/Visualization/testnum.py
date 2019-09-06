from time import clock
import numpy as np
from math import sin

t = [i * 0.0001 for i in range(10000000)]
start_time = clock()
for i, item in enumerate(t):
    t[i] = sin(item)
print('用时为:', clock() - start_time)

t = [i * 0.0001 for i in range(10000000)]
start_time = clock()
t = np.array(t)
np.sin(t, t)
print('numpy用时为:', clock() - start_time)