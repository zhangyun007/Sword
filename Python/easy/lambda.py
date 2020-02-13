x, y =12, 23 
x, y = y, x
print(x)
print(y)


def fibana(n):
	if n == 1 or n == 2:
		return 1
	else:
		return fibana(n-1) + fibana(n-2);
		
print(fibana(1))
print(fibana(2))
print(fibana(3))
print(fibana(4))
print(fibana(5))
print(fibana(6))


fiba = lambda n : 1 if n ==1 or n == 2  else fiba(n-1) + fiba(n-2)

print(fiba(1))
print(fiba(2))
print(fiba(3))
print(fiba(4))
print(fiba(5))
print(fiba(6))