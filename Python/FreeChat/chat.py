import tornado.web
import tornado.ioloop
import tornado.websocket
import time
import os, sys, io

# Linux上print中文有问题，必须加上该句
# https://segmentfault.com/q/1010000003932742
# sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')


# room是形如 {'TestRoom':{'张飞':[1, Obj1, Obj2], '刘备':[0, Obj1, Obj2]}, 
#	       'NewRoom':{'曹操':[0, Obj1, Obj2], '曹植':[1, Obj1, Obj2]} }
# 的一个字典对象。
#
# 其中 第一项表示该用户发送消息的次数，Obj1是一个EchoWebSocket对象, Obj2是一个ImageSoscket对象。


room = {}


class ImageSocket(tornado.websocket.WebSocketHandler):

	rname = ''
	nick = ''
   	
	# tornado 4.0版本以后需要加上这个函数，否则会返回403错误。
	def check_origin(self, origin):
        	return True

	def open(self):

		self.rname = self.get_argument("room")
		self.nick = self.get_argument("nick")

		# 浏览器端程序保证了ImageSocket对象在EchoWebSocket对象之后生成，此时room[self.rname][self.nick]必然存在
		room[self.rname][self.nick][2] = self

	def on_message(self, message):

		t2 = time.time()
		if room[self.rname][self.nick][0]/(t2 - t1) > 1:
			room[self.rname][self.nick][1].write_message('发送信息太快，请歇会儿。')
			return
		room[self.rname][self.nick][0] += 1			

		a = message.split()
		b = ''
		for i in range(1, len(a)):
			b += a[i] + ' '
		if a[0] == "all":
			# 发送给所有人
			for x in room[self.rname].keys():
				room[self.rname][x][2].write_message(self.nick + ': ' + b)
		else:
			
			if a[0] == self.nick:	
				# 发送给自己
				room[self.rname][a[0]][2].write_message(self.nick + ': ' + b)
			else:
				if a[0] in room[self.rname].keys():
					# 发送给别人，自己也收到。
					room[self.rname][a[0]][2].write_message(self.nick + ': ' + b)
					room[self.rname][self.nick][2].write_message(self.nick + ': ' + b)
				else:
					# 发送的对象已经退出房间。
					room[self.rname][self.nick][2].write_message(a[0] + '已经退出房间。 ')
					

class EchoWebSocket(tornado.websocket.WebSocketHandler):

	global room

	def check_origin(self, origin):  
        	return True  

	rname = ''
	nick = ''

	def open(self):
		self.rname = self.get_argument("room")
		self.nick = self.get_argument("nick")
		if self.rname in room.keys():
			room[self.rname][self.nick] = [0, self, 0]
		else:
			room[self.rname] = {self.nick:[0, self, 0]}
		for x in room[self.rname].keys():
			room[self.rname][x][1].write_message(self.nick + '加入了聊天室')
			Nicklist = ''
			for i in room[self.rname].keys():
				Nicklist += i + ' '
			room[self.rname][x][1].write_message('NickList ' + Nicklist)

	def on_message(self, message):

		t2 = time.time()
		if room[self.rname][self.nick][0]/(t2 - t1) > 1:
			room[self.rname][self.nick][1].write_message('发送信息太快，请歇会儿。')
			return
		room[self.rname][self.nick][0] += 1			

		a = message.split()
		b = ''
		for i in range(1, len(a)):
			b += a[i] + ' '
		if a[0] == "all":
			# 发送给所有人
			for x in room[self.rname].keys():
				room[self.rname][x][1].write_message(self.nick + ': ' + b)
		else:
			# 发送给自己
			if a[0] == self.nick:
				room[self.rname][a[0]][1].write_message(self.nick + ': ' + b)
			else:
				if a[0] in room[self.rname].keys():
					# 发送给别人，也给自己发一份。
					room[self.rname][a[0]][1].write_message(self.nick + ': ' + b)
					room[self.rname][self.nick][1].write_message(self.nick + ': ' + b)
				else:
					# 发送的对象已经退出房间。
					room[self.rname][self.nick][1].write_message(a[0] + '已经退出房间。 ')

	def on_close(self):
		del room[self.rname][self.nick]
		for x in room[self.rname].keys():
			room[self.rname][x][1].write_message(self.nick + '离开了聊天室')
			Nicklist = ''
			for i in room[self.rname].keys():
				Nicklist += i + ' '
			room[self.rname][x][1].write_message('NickList ' + Nicklist)
		if room[self.rname] == {}:
			del room[self.rname]

class Index(tornado.web.RequestHandler):
	global room

	def get(self):
		self.render('templates/main.html')
	def post(self):
		if self.get_argument("room") in room.keys() and self.get_argument("nick") in room[self.get_argument("room")].keys():
			self.write('你的nick已经被使用，请更换nick，重新<a href="">登录</a>。')
		elif self.get_argument("nick")=="" or self.get_argument("room")=="":
			self.write('房间名和昵称不能为空')	
		elif len(self.get_argument("room")) > 20 or len(self.get_argument("nick")) > 20:
			self.write('房间名称和用户名不能超过过20个字符，请重新<a href="">登录</a>。')
		else:
			self.render('templates/chat.html', room=self.get_argument("room"),nick=self.get_argument("nick"))

if __name__ == '__main__':
	t1 = time.time()
	app = tornado.web.Application(
    		handlers=[('/', Index),('/websocket', EchoWebSocket), ('/imagesocket', ImageSocket)],
			static_path = os.path.join(os.path.dirname(__file__), "static")	,
        	debug=True
        )
	app.listen(8000, address="0.0.0.0")
	tornado.ioloop.IOLoop.instance().start()
