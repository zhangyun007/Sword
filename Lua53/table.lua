--[[

表最基础的作用就是当成字典来用。 它的键可以是除了 nil 之外的任何类型的值。

表 中的键最常见的两种类型就是整数型和字符串类型。 当键为字符串时，表 可以当成结构体来用。同时形如 t["field"] 这种形式的写法可以简写成 t.field 这种形式。

从结果中你还可以发现，使用 pairs 进行遍历时的顺序是随机的，事实上相同的语句执行多次得到的结果是不一样的。

]]--


t={} 
t[{}] = "table"                 -- key 可以是表 
t[1] = "int"                    -- key 可以是整数 
t[1.1] = "double"               -- key 可以是小数 
t[function () end] = "function" -- key 可以是函数 
t[true] = "Boolean"             -- key 可以是布尔值 
t["abc"] = "String"             -- key 可以是字符串 
t[io.stdout] = "userdata"       -- key 可以是userdata 
t[coroutine.create(function () end)] = "Thread" -- key可以是thread 

for k,v in pairs(t) do 
  print(k,"->",v) 
end 

print(#t) 