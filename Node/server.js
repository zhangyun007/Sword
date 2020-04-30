/**
 * 发送和获取
 */

/* 引入net模块 */
var net = require("net");

/* 创建TCP服务器 */
var server = net.createServer(function(socket){
    /* 获取地址信息 */
    var address = server.address();
    var message = "the server address is"+JSON.stringify(address);

	//获得远程IP和prot
	console.log(socket.remoteAddress);
	console.log(socket.remotePort);

    /* 发送数据 */
    socket.write(message,function(){
        var writeSize = socket.bytesWritten;
        console.log(message + "has send");
        console.log("the size of message is"+writeSize);
    })

    /* 监听data事件 */
    socket.on('data',function(data){
        console.log(data.toString());
        var readSize = socket.bytesRead;
        console.log("the size of data is"+readSize);
    })
})

// 这里的IP地址是外网IP，实际上，应该在无线路由器上运行改程序。这里运行会失败，不能在公网IP上listen
server.listen(8000, "0.0.0.0", function(){
    console.log("Creat server on http://127.0.0.1:8000/");
})