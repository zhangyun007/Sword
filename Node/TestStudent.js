//使用require方法加载Student模块
var student=require('./Student');
//调用类方法
student.showAll("张思",23);
//展现类静态字段
console.log(student.TName);
student.TName="王武";
console.log(student.TName);

//实例化类对象
var stu=new student();
stu.show();
stu.showName();
stu.showAge();
