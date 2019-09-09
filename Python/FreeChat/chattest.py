import websocket
import threading
import time
import uuid

def on_message(ws, message):
    print("message: %s ###" % message)

def on_error(ws, error):
    print("error: %s ###" % error)

def on_close(ws):
    print("### closed ###")

def on_open(ws):
    for i in range(100):
        ws.send("all Hello %d" % i)
    time.sleep(1)
    ws.close()
    print("### open ###")


def worker():
    ws = websocket.WebSocketApp(
        "ws://192.168.42.128:8000/websocket?room=test&nick=" + str(uuid.uuid1()),
        on_message=on_message,
        on_error=on_error,
        on_close=on_close,
        on_open=on_open
    )
    ws.run_forever()
  
if __name__ == "__main__":

     l = []
     for i in range(10):
         l.append(threading.Thread(target=worker))
  
     for t in l:
         t.start()
  
     for t in l:
         t.join() 
