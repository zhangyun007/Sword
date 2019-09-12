# 作者：Coldwings
# 链接：https://www.zhihu.com/question/62185153/answer/196193958

#!/usr/bin/env python3

import time


from numba import jit

#开启jit后，运行时间从18秒降到0，34秒，提升了将近50倍。
@jit
def calc(n, i=0, cols=0, diags=0, trans=0):
    if i == n:
        return 1
    else:
        rt = 0
        for j in range(n):
            col = 1 << j
            diag = 1 << (i - j + n - 1)
            tran = 1 << (i + j)

            if (col & cols) == 0 and (diag & diags) == 0 and (tran & trans) == 0:
                rt += calc(n, i+1, cols | col, diags | diag, trans | tran)
        return rt



if __name__ == '__main__':
    t = time.time()
    print(calc(13))
    print(time.time() - t)