from multiprocessing import Pool

def long_time_task(name):
    f  = open("test.l", "w")
    f.write("This is in fun\n")
    print('Run task %s (%s)...' % (name, os.getpid()))
    f.close()
    exit(0)
    
# 同时最多10个进程
p = Pool(10)

# 产生500个进程
for i in range(5):
    p.apply_async(long_time_task, args=(i,))
    
p.close()