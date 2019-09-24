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
		//用处已经存在，
		echo "user ".$_POST["user"]." exists <br>";
	} else {
		//用户不存在，则注册用户。
		$sql = "INSERT INTO user(name, password) VALUES(\"".$_POST["user"]."\",\"".$_POST["password"]."\");";
		echo $sql."<br>";
		
		$re = $db->exec($sql);
		if(!$re){
			echo $db->lastErrorMsg();
		} else {
			echo $_POST["user"]." register successfully <br>";
		}
	}
	$db->close();
?> 

</body> 
</html>