<?php
/*
$con = mysql_connect("localhost","root","root");
if (!$con)
  {
  die('Could not connect: ' . mysql_error());
  }

mysql_select_db("world", $con);

$result = mysql_query("SELECT * FROM countrylanguage;");

echo "<table border='1'>
<tr>
<th>Firstname</th>
<th>Lastname</th>
</tr>";

while($row = mysql_fetch_array($result))
  {
  echo "<tr>";
  echo "<td>" . $row['CountryCode'] . "</td>";
  echo "<td>" . $row['Language'] . "</td>";
  echo "<td>" . $row['IsOfficial'] . "</td>";
  echo "<td>" . $row['Percentage'] . "</td>";
  echo "</tr>";
  }
echo "</table>";

mysql_close($con);
*/

 $conn=mysqli_connect("localhost","root","root");
    if($conn){
        echo"ok";
    }else{
        echo"error";    
    }

?>