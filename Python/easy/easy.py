import sys

a = [12, 23, 34, 345, 345, 234 , 234, 435, 345];
# 半开半闭区间。包括左边，不包括右边。
print(a[2:4])
del(a[2:4]);
a.remove(234)

bigmuls=[]
x = (1, 2, 3, 4)
y = (10, 15, 3, 22)
for a in x:
	for b in y:
		if a * b > 25:
			bigmuls = bigmuls + [(a, b)]	
print(bigmuls)

# 不推荐，过于复杂。
print([(x,y) for x in (1,2,3,4) for y in (10,15,3,22) if x*y > 25]) 


def f(x): return x % 2 != 0 and x % 3 != 0
a = filter(f, range(2, 100))
print(list(a))

def cube(x): return x*x*x;
a = map(cube, range(1,11))
print(list(a))

funa = lambda x: x + 1
print(funa(3))

L = [lambda x: x+2, lambda x: x*2, lambda x: x**2]
print("L=", L[0](1), L[1](2), L[2](3))

#返回最后一个参数
funb = lambda *x: x[-1] 
print(funb(12, 23, 34))

# 列表转成字典
a = dict([('sape', 4139), ('guido', 4127), ('jack', 4098)])
print(a)
print(a['sape'])
print(a['jack'])

a = ['a', 'b', 'c']
for i in range(len(a)):
		a[i] = (a[i], a[i])

dict1 = {'Name': 'Zara', 'Age': 7}
dict2 = {'Sex': 'female' }

dict1.update(dict2)
print("Value : %s" %  dict1)

def change(x):
    x["test"] = "new!"


# dict1多了一项，说明参数传list或者dict指针。
change(dict1)
print(dict1)

class MyDict(object):
    def __init__(self, a):
        self.d = a
        self.d["test"] = 'old'
        print("self.d =", self.d)
    
dict3 = MyDict(dict1)
print(dict1)

def get_cur_info():
    print(sys._getframe().f_code.co_filename)  # 当前文件名
    print(sys._getframe().f_code.co_name)  # 当前函数名
    print(sys._getframe().f_lineno) # 当前行号
    print(sys._getframe().f_back.f_lineno) # 调用者的帧

def fn(self,name="world"):
    print("Hello,%s"%name)
    get_cur_info()
    
# 使用type定义类
Hello = type('Hello',(object,),dict(hello=fn))
h = Hello()
h.hello()

