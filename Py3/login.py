import tornado.ioloop  
import tornado.web 

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        if not self.get_secure_cookie("user"):
            self.redirect("/login")
            return
        self.write(b'hello ' + self.get_secure_cookie("user"))

class LoginHandler(tornado.web.RequestHandler):
    def get(self):
        self.write('<html><body><form action="/login" method="post">'
                   'Name: <input type="text" name="name">'
                   '<input type="submit" value="Sign in">'
                   '</form></body></html>')

    def post(self):
        self.set_secure_cookie("user", self.get_argument("name"))
        self.redirect("/")

application = tornado.web.Application([
    (r"/", MainHandler),
    (r"/login", LoginHandler),
], cookie_secret="61oETzKXQAGaYdkL5gEmGeJJFuYh7EQnp2XdTP1o/Vo=",debug=True)

application.listen(8888)
tornado.ioloop.IOLoop.instance().start()