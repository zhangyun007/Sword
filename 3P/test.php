<?php

define("GREETING","Hello world!\n");
echo constant("GREETING");

/* PHP数组，key-value数组*/	

$array = array(
    1    => "a",
    "1"  => "b",
    1.5  => "c",
    true => "d",
);
var_dump($array);
print_r($array);

echo "-------------------\n";

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

echo "-------------------\n";

$a = array(1 => 'one', 2 => 'two', 3 => 'three');
unset($a[2]);
/* will produce an array that would have been defined as
   $a = array(1 => 'one', 3 => 'three');
   and NOT
   $a = array(1 => 'one', 2 =>'three');
*/

$b = array_values($a);
// array_values取数组的值集合，类似，arrary_keys取键集合。
// Now $b is array(0 => 'one', 1 =>'three')

echo "-------------------\n";

// 创建一个简单的数组
$array = array(1, 2, 3, 4, 5);
print_r($array);

// 现在删除其中的所有元素，但保持数组本身不变:
foreach ($array as $key => $value) {
    unset($array[$key]);
}
print_r($array);

// 添加一个单元（注意新的键名是 5，而不是你可能以为的 0）
$array[] = 6;
print_r($array);

// 重新索引：
$array = array_values($array);
$array[] = 7;
print_r($array);

echo "-------------------\n";

/*二维数组*/
$cars = array
  (
  array("Volvo",22,18, 13),
  array("BMW",15),
  array("Saab",5,2),
  array("Land Rover",17,15,4)
  );

var_dump($cars);

echo "-------------------\n";

function getArray() {
    return array(1, 2, 3);
}

// on PHP 5.4
$secondElement = getArray()[1];
echo $secondElement; 
echo "\n";

// previously
$tmp = getArray();
$secondElement = $tmp[1];
echo $secondElement;
echo "\n";

// or
list(, $secondElement) = getArray();
echo $secondElement;
echo "\n";

echo "-------------------\n";

?>
