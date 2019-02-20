<?php

/* PHP数组，hash数组。*/

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
?>
