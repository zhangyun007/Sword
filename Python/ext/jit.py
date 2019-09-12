from numba import jit
import time

# 计算某个函数的运行时间
def timeit(func, *args):
	start = time.time()
	s = func(*args)
	end = time.time()
	print('Time used: {} sec', end - start)
	return s;

#添加@jit，程序运行时间从5秒降低到0，07秒，降低了70倍。
@jit
def foo(x,y):	
	s = 0
	for i in range(x,y):
		s += i
	return s
	
print(timeit(foo, 1, 100000000));