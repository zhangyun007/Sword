<?php

/**
 *简单工厂模式（静态工厂方法模式）
 */
/**
 * Interface people 人类
 */
interface  people
{
    public function  say();
}
/**
 * Class man 继承people的男人类
 */
class man implements people
{
    // 具体实现people的say方法
    public function say()
    {
        echo '我是男人<br>';
    }
}
/**
 * Class women 继承people的女人类
 */
class women implements people
{
    // 具体实现people的say方法
    public function say()
    {
        echo '我是女人<br>';
    }
}
/**
 * Class SimpleFactoty 工厂类
 */
class SimpleFactoty
{
    // 简单工厂里的静态方法-用于创建男人对象
    static function createMan()
    {
        return new man();
    }
    // 简单工厂里的静态方法-用于创建女人对象
    static function createWomen()
    {
        return new women();
    }
}
/**
 * 直接new一个对象就好，何必多写几行代码多此一举？
 */
$man = SimpleFactoty::createMan();
$man->say();
$woman = SimpleFactoty::createWomen();
$woman->say();

?>