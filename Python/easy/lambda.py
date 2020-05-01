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

L = [lambda x: x+2, lambda x: x*2, lambda x: x**2]
print("L=", L[0](1), L[1](2), L[2](3))
