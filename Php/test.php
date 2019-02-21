<?php

/* PHP数组，key-value数组*/

define("GREETING","Hello world!\n");
echo constant("GREETING");
	
$array = array(
    "foo" => "bar",
    42    => 24,
    "multi" => array(
         "dimensional" => array(
             "array" => "foo"
         )
    )
);

var_dump($array["foo"]);
var_dump($array[42]);
var_dump($array["multi"]["dimensional"]["array"]);

$arr = array( "A", "B", "C" );
unset( $arr[1] );
var_dump($arr);
print_r($arr);

$age=array("Bill"=>"63","Steve"=>"56","Elon"=>"47");

foreach($age as $key=>$value) {
   echo "Key=" . $key . ", Value=" . $value;
   echo "\n";
}

$cars = array
  (
  array("Volvo",22,18, 13),
  array("BMW",15),
  array("Saab",5,2),
  array("Land Rover",17,15,4)
  );

var_dump($cars)
?>
