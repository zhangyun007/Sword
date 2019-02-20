var express = require('express');
var fs = require('fs');
app = express();

var options = {
  key: fs.readFileSync('../keys/server.key'),
  cert: fs.readFileSync('../keys/server.crt')
};

server = require('https').createServer(options, app);

server.listen(3000);

app.get('/', function(req, res) {
    res.sendFile(__dirname + '/hello_world.html');
});
