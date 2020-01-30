# http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/001431927781401bb47ccf187b24c3b955157bb12c5882d000

from multiprocessing import Pool
import os, time, random, socket, sys

def long_time_task(name):
    print('Run task %s (%s)...' % (name, os.getpid()))
    start = time.time()
    # time.sleep(random.random() * 3)

    # 创建 socket 对象
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

    # 获取本地主机名
    host = socket.gethostname() 

    # 设置端口好
    port = 9999

    # 连接服务，指定主机和端口
    s.connect((host, port))

    # 接收小于 1024 字节的数据
    msg = s.recv(1024)

    s.close()

    print (msg.decode('utf-8'))

    end = time.time()
    print('Task %s runs %0.2f seconds.' % (name, (end - start)))

if __name__=='__main__':
    print('Parent process %s.' % os.getpid())
	
    # 同时最多10个进程
    p = Pool(10)
	
    # 产生500个进程
    for i in range(500):
        p.apply_async(long_time_task, args=(i,))
    print('Waiting for all subprocesses done...')
    p.close()
    p.join()
    print('All subprocesses done.')