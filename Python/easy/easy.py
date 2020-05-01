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
			bigmuls.append((a, b))
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

funb = lambda *x: x[-1]
print(funb(12))


# 列表转成字典
a = dict([('sape', 4139), ('guido', 4127), ('jack', 4098)])
print(a)
print(a['sape'])
print(a['jack'])


dict1 = {'Name': 'Zara', 'Age': 7}
dict2 = {'Sex': 'female' }

dict1.update(dict2)
print("Value : %s" %  dict1)