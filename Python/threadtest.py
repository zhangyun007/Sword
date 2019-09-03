import threading

# 线程数量
cnt = 0
mutex = threading.Lock()

def worker():
    for i in range(0, 100):
        global cnt
        mutex.acquire()
        cnt += 1
        mutex.release()

l = []
for i in range(100):
    l.append(threading.Thread(target=worker))

print(cnt)

for t in l:
    t.start()

print(cnt)

for t in l:
    t.join() 


