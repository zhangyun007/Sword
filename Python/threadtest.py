import threading

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

for t in l:
    t.start()

for t in l:
    t.join() 

print(cnt)
