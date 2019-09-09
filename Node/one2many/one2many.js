// http://www.blogjava.net/linli/archive/2014/10/21/418910.html
// http://www.jianshu.com/p/853099ae2edd

var express = require('express');
var fs = require('fs');
var UUID = require('node-uuid');
app = express();

var options = {
  key: fs.readFileSync('../../keys/server.key'),
  cert: fs.readFileSync('../../keys/server.crt')
};

server = require('https').createServer(options, app);

server.listen(3000);

app.get('/', function(req, res) {
	if (!pws) {
    		res.sendFile(__dirname + '/Presenter.html');
    	} else {
    		res.sendFile(__dirname + '/Viewer.html');
	}
});

var WebSocketServer = require('ws').Server,
wss = new WebSocketServer({server: server});


//Presenter的WebScoket
var pws = null;

//Viwer的WebSocket
var wsl = {};

// 有socket连入
wss.on('connection', function(ws) {

	ws.id = UUID.v4();

	//将生成的websocket对应的socketid发送给给浏览器端，每个浏览器端都有其唯一的socketid。
	ws.send(JSON.stringify({
			"event": "_socket_id",
			"data": {
				"socketid": ws.id
			}
			}));

	if (!pws) {
		pws = ws;
	} else {
		wsl[ws.id] = ws;
	}

	// 转发收到的消息
	ws.on('message', function(message) {
		var json = JSON.parse(message);
		
		if (ws == pws) {
			console.log("To Viewer %s...", json.data.socketid);
			//来自Presenter的消息，发送给对应的Viwer
			wsl[json.data.socketid].send(message, function (error) {
				if (error) {
					console.log('Send message error: ', error);
				}
			});
		} else {
			console.log("%s To Presenter...", json.data.socketid);
			//来自Viwer的消息，发送给Presenter
			pws.send(message, function (error) {
				if (error) {
					console.log('Send message error: ', error);
				}
			});

		}
	});
	ws.on('close', function() {
		if (ws == pws) {		
			pws = null;

			console.log(wsl);
			//通知Viewer，Presenter退出。
			k = Object.keys(wsl);
			for (i = 0; i < k.length; i++ ) {
				wsl[k[i]].send(JSON.stringify({
					"event": "_exit",
					"data": {
						"socketid": ws.id
					}
				}));
			}
		} else {
			delete wsl[ws.id];
			console.log(wsl);
			//通知Presenter, Viewer退出。
			if (pws) {
				pws.send(JSON.stringify({
				    "event": "_exit",
				    "data": {
					"socketid": ws.id
				    }
				}));
			}
		}
	});
});
