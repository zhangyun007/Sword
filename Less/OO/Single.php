<?php

class Single {
    private static $instance;
	public $mix;
	
    public static function getInstance()
    {
		// instanceof 用于确定一个 PHP 变量是否属于某一类 class 的实例：  https://www.php.net/manual/zh/language.operators.type.php
        if (! (self::$instance instanceof self)) {
            self::$instance = new self();
        }
        return self::$instance;
    }
}

// @test
$firstMysql = Single::getInstance();
$secondMysql = Single::getInstance();

$firstMysql->mix = 'ityangs_one';
$secondMysql->mix = 'ityangs_two';

print_r($firstMysql->mix);
// 输出： ityangs_two
print_r($secondMysql->mix);
// 输出： ityangs_two

?>