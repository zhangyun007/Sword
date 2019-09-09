var app = require('express')();
app.listen(3000)

app.get('/', function(req, res) {
    res.sendFile(__dirname + '\\hello_world.html');
});
