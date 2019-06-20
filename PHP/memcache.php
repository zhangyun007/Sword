<?php

$memcache = new Memcache;
#创建一个memcache对象

$memcache->connect('localhost', 11211) or die ("Could not connect"); 
#连接memcached服务器

$memcache->set('key', 'memcache-test');                              #设置1个变量到内存中，key=key, value=memcache-test

$get_value = $memcache->get('key');                                  
#从内存取出key的value

echo $get_value;                                                     
#回显

?> 