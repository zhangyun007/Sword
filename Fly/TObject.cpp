/*
 * http://en.cppreference.com/w/cpp/container/vector/erase
 */

#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>

using namespace std;
/*
本程序目的是为了实现类似Python里的字典数据结构，key和value都可以是任意数据结构。
我们的程序里用TObject为所有类的父类，TObject *指针类型则可以指向所有的自定义类型对象。
结合vector和map，我们可以得到一个保存所有对象指针的vector和能保存任意类型的key和value的map。
接下来，我们实现自己的vector和map，继承自TObject。
*/
class TObject {
public:
	//零函数表示该函数在当前类中不用被实现，同时意味着该类不能实例化；虚函数意味着该函数在子类中可以有不同的实现；
	virtual void show() = 0;
	//当一个类有子类时，该类的析构函数必须是虚函数，否则子类对象被删除时，子类的析构函数不会被调用。
	//有了虚析构函数，子类对象析构时，先调用子类的析构函数，再调用父类的析构函数。
	//保险起见，不管三七二十一，见到析构函数，就加一个virtual，肯定没错。
	virtual ~TObject() { 
		cout << "TObject destruct!\n";
		cout << "\n";
	}
};

class TInt : TObject {
public:
	void show() {
		cout << i << '\n';
	}
	TInt(int a) {
		i = a;
	}
	virtual ~TInt(){
		cout << i << "， TInt destruct.\n";
	}
private:
	int i;
};

class TButton : TObject {
public:
	void show() {
		cout << "TButton!\n";
	}
};

class TLabel : TObject {
public:
	void show() {
		cout << "TLabel!\n";
	}
};


template <class T>
class TVector: TObject {
};


/*Triangle类模板继承了Shape类模板，但是这个例子只是说明了类模板能像类一样继承，本身的设计确不太好，将来要重新设计一个好的例子。*/
template <class type>
class Shape: TObject {
protected:
    type x, y, z, width, height;
private:

public:
    virtual ~Shape(){
		cout << "TShape destruct.\n";
    } //一定要用{}实现！！
    virtual void show() {
        cout  << "yes" << endl;
    }
};

template <class T>
class Triangle:public Shape<T> {
private:
public:
    Triangle();
    Triangle(T, T, T);
    virtual ~Triangle(){
		cout << "Triangle destruct.\n";
	}; //一定要用{}实现！！
    void show();
};

template <class T>
void Triangle<T>::show() {
    cout << "test"<< endl;
}

template <class T>
Triangle<T>::Triangle(T a, T b, T c) {
    this->x = a;
    this->y = b;
    this->z = c;
}

int main()
{
	std::vector<TObject *> v;
	
	class TObject * label1 = (TObject *)new TLabel();
	class TObject * button1 = (TObject *)new TButton();
	class TObject * int1 = (TObject *)new TInt(3);
	
	v.push_back(label1);
	v.push_back(button1);
	v.push_back(int1);
	
	for (auto &iter: v) {
		iter->show();
	}
	
	std::unordered_map<TObject *, TObject *> m;
	m[label1] = label1;
	m[button1] = button1;
	m[int1] = label1;

	Shape<int> a;
	Triangle<int> b(5,6,7);
	
	delete label1;
	delete button1;
	delete int1;
	
	return 0;
}