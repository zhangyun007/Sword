from time import clock

# 给numpy其一个别名叫np
import numpy as np
from math import sin

# 列表中保存的是对象指针
t = [i * 0.0001 for i in range(10000000)]
start_time = clock()
for i, item in enumerate(t):
    t[i] = sin(item)
print('用时为:', clock() - start_time)

# np.array保存对象本身，所以快。
t = [i * 0.0001 for i in range(10000000)]
start_time = clock()
t = np.array(t)
np.sin(t, t)
print('numpy用时为:', clock() - start_time)