import tornado.ioloop
import tornado.web

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        if not self.get_cookie("mycookie"):
            self.set_cookie("mycookie", "myvalue")
            self.write("Your cookie was not set yet!")
            self.write('<html>'
                   '<head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"></head>'
                   ' <body><form action="/" method="post">'
                   '<input type="text" name="message">'
                   '<br>'
                   '<input type="file" name="files">'
                   '<br>'
                   '<input type="submit" value="Submit">'
                   '</form></body></html>') 
        else:
            self.write("Your cookie was set!")

    def post(self):
        self.write('<html><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"></head><body> You wrote ' + self.get_argument("message") + '<br>' + self.get_argument("files") + '<br>' + self.get_cookie("mycookie") + '</body></html>')

class StoryHandler(tornado.web.RequestHandler):
    def get(self, story_id):
        self.write("You requested the story " + story_id)

application = tornado.web.Application(
    handlers = [(r"/", MainHandler),(r"/story/([0-9]+)", StoryHandler)],
    debug = True
  )

if __name__ == "__main__":
    application.listen(8888,address="0.0.0.0")
    tornado.ioloop.IOLoop.instance().start()
