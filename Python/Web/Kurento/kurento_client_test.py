import os.path

import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web

from tornado.options import define, options
define("port", default=8000, help="run on the given port", type=int)

class IndexHandler(tornado.web.RequestHandler):
    def get(self):
        self.render('kurento_client_test.html')

if __name__ == '__main__':
    tornado.options.parse_command_line()
    app = tornado.web.Application(
        handlers=[(r'/', IndexHandler)],
        template_path=os.path.join(os.path.dirname(__file__), "")
    )
    '''
    SSL_OPTIONS = {
       "certfile": "../keys/server.crt",
       "keyfile": "../keys/server.key", } 
    https_server = tornado.httpserver.HTTPServer(app, ssl_options=SSL_OPTIONS)
    https_server.listen(options.port)
    '''
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
