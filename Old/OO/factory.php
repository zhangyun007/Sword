<?php

/**
 *简单工厂模式（静态工厂方法模式）
 */
/**
 * Interface clothes 衣服
 */
interface  Clothes
{
    public function  say();
}
/**
 * Class Coat 继承people的男人类
 */
class Coat implements Clothes
{
    // 具体实现people的say方法
    public function say()
    {
        echo '我是Coat<br>';
    }
}
/**
 * Class women 继承people的女人类
 */
class Tshirt implements Clothes
{
    // 具体实现people的say方法
    public function say()
    {
        echo '我是Tshirt<br>';
    }
}
/**
 * Class SimpleFactoty 工厂类
 */
class SimpleFactoty
{
    // 简单工厂里的静态方法-用于创建男人对象
    static function createCoat()
    {
        return new Coat();
    }
    // 简单工厂里的静态方法-用于创建女人对象
    static function createTshirt()
    {
        return new Tshirt();
    }
}
/**
 * 直接new一个对象就好，何必多写几行代码多此一举？
 */
$coat = SimpleFactoty::createCoat();
$coat->say();
$shirt = SimpleFactoty::createTshirt();
$shirt->say();

?>