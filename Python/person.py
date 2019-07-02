class Person:
    population = 0

    def __init__(self, name):
        self.name = name
        print("Initlizing ",self.name)
        Person.population +=1

    def __del__(self):
        print(self.name, " says bye")
        Person.population -=1
        if Person.population == 0:
            print("I am the last one.")
        else:
            print("There are still", Person.population, " people left.")

    def sayHi(self):
        print("Hi, my name is ", self.name)

    def howMany(self):
        if Person.population == 1:
            print("I am the only person here")
        else:
            print ("We have ", Person.population, " person here.")
            

'''构造函数调用__init__'''
swaroop = Person('Swaroop')
swaroop.sayHi()
swaroop.howMany()

kalam = Person('Abdul Kalam')
kalam.sayHi()
kalam.howMany()

swaroop.sayHi()
swaroop.howMany()

'''脚本退出之前调用对象的__del__函数（析构函数）'''
