import time

# 计算某个函数的运行时间，缺点是传入参数（是一个函数）不能有参数。
def timeit(func):
	start = time.time()
	func()
	end = time.time()
	print('used:', end - start)
  
def debug(func):
  def wrapper(*args, **kwargs):  # 指定宇宙无敌参数
    print("[DEBUG]: enter {}()".format(func.__name__))
    print('Prepare and say...')
    return func(*args, **kwargs)
  return wrapper  # 返回

@debug  
def foo(x):
  print(x)

foo("Test!")
