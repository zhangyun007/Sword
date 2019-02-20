//在nodejs中，类型定义就像定义函数一样，其实该函数就是Student类的构造函数
var Student=function(){
    //如果需要定义该类对象的字段、方法等，需加上this关键字，否则就认为是该函数中的临时变量
    this.Name="张三";
    this.Age=21;
    
    //定义对象方法
    this.show=function(){
        console.log(this.Name+' '+this.Age);
    };
};

//类的成员方法也可以在构造方法外定义，需加上prototype关键字，否则就认为是定义类方法（静态方法）
Student.prototype.showName=function(){
  console.log(this.Name);
};

Student.prototype.showAge=function(){
    console.log(this.Age);
};

//定义类方法(类的静态方法，可直接通过类名访问)
Student.showAll=function(name,age){
    console.log("showAll "+name+' '+age);
};

//定义类的静态字段
Student.TName="李四";

//导出Student类，使其他js文件可以通过require方法类加载该Student模块
module.exports=Student;
