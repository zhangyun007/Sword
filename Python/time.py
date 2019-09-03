import time
 
def foo():
	print("in foo()")
 
 
# 计算某个函数的运行时间
def timeit(func):
	start = time.clock()
	func()
	end = time.clock()
	print('used:', end - start)
 
timeit(foo)
