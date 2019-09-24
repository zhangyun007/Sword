var os = require("os");
 
//查看操作系统平台
var result = os.platform(); 
console.log(result);

//os.release(); 查看操作系统版本
//os.type();  查看操作系统名称
//os.arch();  查看操作系统CPU架构
console.log(os.release());
console.log(os.type());
console.log(os.arch());

a = [1, 2, 3, 4, 5, 6];
for (var i = 0; i < a.length; i++)
	console.log(a[i]);

//从a[2]开始删除，删除1个元素
a.splice(2, 1);
console.log(a);

//添加元素10到a[2]
a.splice(2, 0, 10);
console.log(a);

b = {"1":[1, 2, 3], "2":[2, 3, 4]};
b["3"] = [3, 4, 5];
console.log(b);

delete b["1"];
console.log(b);

console.log(Object.keys(b));
