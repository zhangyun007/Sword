import tornado.ioloop  
import tornado.web  
import os, sys, io
import mysql.connector
from tornado.options import define, options   

sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')

define("port", default=8000, help="run on the given port", type=int)

config = {
    'user':'root',
    'password':'root',
    'host':'localhost',
    'database':'test'}

curr_user = 'guest'
BaseDir = 'static/' + curr_user

class MainHandler(tornado.web.RequestHandler):  
    def get(self):                  
        self.set_secure_cookie("user", 'guest');
        self.render("cloudstorage.html",user=curr_user,items=os.listdir(BaseDir))

class DeleteHandler(tornado.web.RequestHandler):  
    def get(self):
        curr_user = self.get_argument("name").split('/')[1]
        BaseDir = 'static/' + curr_user
        os.remove(self.get_argument("name"))
        self.render("cloudstorage.html",user=curr_user,items=os.listdir(BaseDir))

class UploadHandler(tornado.web.RequestHandler):  
    def post(self):         
        if self.request.files:          
            # decode()将b'zhangfei'转成'zhangfei'
            curr_user=self.get_secure_cookie("user").decode()
            BaseDir = 'static/' + curr_user + '/'
            if os.path.exists(BaseDir) == False:
                if os.path.exists("static/") == False:
                    os.mkdir("static/")
                os.mkdir(BaseDir)
            myfile = self.request.files['myfile'][0]
            fin = open(BaseDir + myfile["filename"],"wb")
            fin.write(myfile["body"])
            fin.close()

            print(self.request.arguments)
            # print(self.request.files)
            print(self.request.path)
            print(self.request.headers)

            self.render("cloudstorage.html",user=curr_user,items=os.listdir(BaseDir))

class RegisterHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("register.html")
    def post(self):
        print(self.request.arguments)
        user = self.get_argument('user')
        passwd = self.get_argument('password')
        if  user_exist(user) == True:
            self.write("用户已存在，请更换用户名，重新<a href=\"register\">注册</a>。")
        else:
            user_add(user, passwd)
            self.write("用户已注册成功，请<a href=\"login\">登录</a>。")

def user_exist(user):

    cnx = mysql.connector.connect(**config)
    cursor=cnx.cursor()

    cursor.execute('show tables;')
    for (table) in cursor:
        if table[0]=='test_user':
            cursor.execute('select * from test_user where name="' + user +'";')
            for (name,passwd) in cursor:
                if name==user:
                    cnx.close()
                    return True
            cnx.close()
            return False
    cnx.close
    return False

def user_add(user , password):
    cnx = mysql.connector.connect(**config)
    cursor=cnx.cursor()

    cursor.execute('show tables;')
    for (table) in cursor:
        print(table)
        if table[0]=='test_user':
            add_user = ("insert into test_user (name, passwd) values (%s, %s);")
            data = (user, password)
            cursor.execute(add_user, data)
            cnx.commit()
            cnx.close
            return
    cursor.execute('create table test_user (name char(20), passwd char(20));')
    add_user = ("insert into test_user (name, passwd) values (%s, %s);")
    data = (user, password)
    cursor.execute(add_user, data)
    # 注意，commmit不可少，否则插入数据失败。
    cnx.commit()
    cnx.close
    return

class LoginHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("login.html")
    def post(self):
        r = verify_user(self.get_argument("user"), self.get_argument("password"))
        if r == 0:
            curr_user=self.get_argument("user")
            BaseDir = 'static/' + curr_user
            if os.path.exists(BaseDir) == False:
                os.mkdir(BaseDir)           
            self.set_secure_cookie("user", curr_user);
            self.render("cloudstorage.html",user=curr_user,items=os.listdir(BaseDir))
        elif r == 1:
            self.write("密码不正确")
        elif r == 2:
            self.write("用户不存在")

def verify_user(user, password):
    cnx = mysql.connector.connect(**config)
    cursor=cnx.cursor()

    cursor.execute('select * from test_user;')
    for (name,passwd) in cursor:
        if name==user and passwd==password:
            cnx.close
            return 0
        elif name==user and passwd!=password:
            cnx.close
            return 1
    cnx.close
    return 2

if __name__=='__main__':
    tornado.options.parse_command_line()
    application = tornado.web.Application(
        handlers = [(r'/',MainHandler),
        (r'/delete', DeleteHandler),
        (r'/upload', UploadHandler),
        (r'/register', RegisterHandler),
        (r'/login', LoginHandler)],
        debug = True,
        cookie_secret="61oETzKXQAGaYdkL5gEmGeJJFuYh7EQnp2XdTP1o/Vo=",
        template_path = os.path.join(os.path.dirname(__file__), "templates"),
        static_path = os.path.join(os.path.dirname(__file__), "static") 
        )
    if os.path.exists(BaseDir) == False:
        os.mkdir(BaseDir)
    application.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
