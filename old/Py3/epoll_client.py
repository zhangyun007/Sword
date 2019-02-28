from multiprocessing import Pool
import os, time, socket

def long_time_task(name):

    print('Run task %s (%s)...' % (name, os.getpid()))
    start = time.time()

    # 创建 socket 对象
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

    # 连接服务，指定主机和端口
    s.connect(("deque.me", 6666))

    # 接收小于 1024 字节的数据
    msg = s.send(b"-------------------Stings ---------------------\n")

    s.close()

    end = time.time()
    print('Task %s runs %0.2f seconds.' % (name, (end - start)))

if __name__=='__main__':
    print('Parent process %s.' % os.getpid())
    # 同时最多10个进程
    p = Pool(100)
    # 产生500个进程
    for i in range(10000):
        p.apply_async(long_time_task, args=(i,))
    print('Waiting for all subprocesses done...')
    p.close()
    p.join()
    print('All subprocesses done.')
