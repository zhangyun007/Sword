<!DOCTYPE html> 
<html> 
<body> 

<?php 
   class MyDB extends SQLite3
   {
      function __construct()
      {
         $this->open('test.db');
      }
   }
   $db = new MyDB();
   if(!$db){
      echo $db->lastErrorMsg();
   } else {
      echo "Opened database successfully<br>";
   }
   
	$sql = "select * from user where name = \"".$_POST["user"]."\";";
	echo $sql."<br>";
	
	$ret = $db->query($sql);
	$row = $ret->fetchArray(SQLITE3_ASSOC);
	
	if ($row) {
		//用户存在，检验密码是否正确
		if ($row["password"] == $_POST["password"])
			//登录成功，获得用户数据。
			echo "user ".$_POST["user"]." login successfully <br>";
		else	
			echo "密码不正确<br>";
	} else {
		//用户不存在，则注册用户。
		echo "用户".$_POST["user"]."不存在";
	}
	$db->close();
?> 

</body> 
</html>