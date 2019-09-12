from numba import jit
import time

#添加@jit，程序运行时间从5秒降低到0，07秒，降低了70倍。
@jit
def foo(x,y):	
	s = 0
	for i in range(x,y):
		s += i
	return s
	
tt = time.time()
print(foo(1,100000000))
print('Time used: {} sec'.format(time.time()-tt))