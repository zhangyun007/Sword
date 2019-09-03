# 比arg[0]小的放左边，大的放右边。
def qsort(arg):
    if(arg==[]): return []
    return qsort([i for i in arg[1:] if i<=arg[0]]) \
    + [arg[0]] + qsort([i for i in arg[1:] if i>arg[0]])

a = [12,14,25,23,2,17,13,25,34,777]
b =list(range(500))[::-1]

print(qsort(a))
print(qsort(b))

