import time
 
def foo():
	print("in foo()")
 
# 计算某个函数的运行时间
def timeit(func):
	start = time.time()
	func()
	end = time.time()
	print('used:', end - start)
 
timeit(foo)
