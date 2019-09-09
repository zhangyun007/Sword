// http://www.blogjava.net/linli/archive/2014/10/21/418910.html
// http://www.jianshu.com/p/853099ae2edd

var express = require('express');
var fs = require('fs');
app = express();

var options = {
  key: fs.readFileSync('keys/server.key'),
  cert: fs.readFileSync('keys/server.crt')
};

server = require('https').createServer(options, app);

server.listen(3000);

app.get('/', function(req, res) {
    res.sendFile(__dirname + '/webrtc.html');
});

var WebSocketServer = require('ws').Server,
wss = new WebSocketServer({server: server});

// 存储socket的数组，这里只能有2个socket，每次测试需要重启，否则会出错
var wsc = [],
index = 1;

// 有socket连入
wss.on('connection', function(ws) {
    console.log('connection');

    // 将socket存入数组
    wsc.push(ws);

    // 记下对方socket在数组中的下标，因为这个测试程序只允许2个socket
    // 所以第一个连入的socket存入0，第二个连入的就是存入1
    // otherIndex就反着来，第一个socket的otherIndex下标为1，第二个socket的otherIndex下标为0
    var otherIndex = index--,
    desc = null;

    if (otherIndex == 1) {
        desc = 'first socket';
    } else {
        desc = 'second socket';
    }

    // 转发收到的消息
    ws.on('message', function(message) {
        var json = JSON.parse(message);
        console.log('received (' + desc + '): ', json);

        wsc[otherIndex].send(message, function (error) {
            if (error) {
                console.log('Send message error (' + desc + '): ', error);
            }
        });
    });
});
