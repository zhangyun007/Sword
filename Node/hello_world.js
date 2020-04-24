const express = require("express");
const app = express();
const router = express.Router();		

const path = require("path");

app .set("views", path.join(__dirname, "views"))
    .set("view engine", "ejs")
    .use("/",router)
    .listen(666, "127.0.0.1");
	
router.get("/", function(req, res){
    res.render("hello_world",{
        name: "zhang",
        id: 12
    });
})