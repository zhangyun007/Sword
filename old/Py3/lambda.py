x, y =12, 23 
x, y = y, x
print(x)
print(y)

fiba = lambda n : 1 if n ==1 or n == 2 else fiba(n-1) + fiba(n-2)

print(fiba(1))
print(fiba(2))
print(fiba(3))
print(fiba(4))
print(fiba(5))
print(fiba(6))
