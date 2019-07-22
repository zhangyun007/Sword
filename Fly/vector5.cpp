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
*/
class TObject {
public:
	//纯虚（空虚）函数，表示该类不能实例化；虚函数，表示该函数在当前类中不用实现，要在子类中实现。
	virtual void show() = 0;
};

class TInt : TObject {
public:
	void show() {
		cout << i << '\n';
	}
	TInt(int a) {
		i = a;
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

int main( )
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
}