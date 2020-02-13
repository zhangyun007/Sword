# 半开半闭区间。包括左边，不包括右边。

bigmuls=[]
x = (1, 2, 3, 4)
y = (10, 15, 3, 22)
for a in x:
	for b in y:
		if a * b > 25:
			bigmuls.append((a, b))
print(bigmuls)

print([(x,y) for x in (1,2,3,4) for y in (10,15,3,22) if x*y > 25]) 


a = [12, 23, 34, 345, 345, 234 , 234, 435, 345];
print(a[2:4])
del(a[2:4]);
a.remove(234)


# 列表转成字典
a = dict([('sape', 4139), ('guido', 4127), ('jack', 4098)])
print(a)
print(a['sape'])
print(a['jack'])


def f(x): return x % 2 != 0 and x % 3 != 0
a = filter(f, range(2, 100))
print(list(a))


def cube(x): return x*x*x;
a = map(cube, range(1,11))
print(list(a))