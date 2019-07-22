/*
 * http://en.cppreference.com/w/cpp/container/vector/erase
 */

#include <vector>
#include <iostream>
#include <utility>

using namespace std;

class TObject {
public:
	//纯虚（空虚）函数，表示该类不能实例化；虚函数，表示该函数在当前类中不用实现，要在子类中实现。
	virtual void show() = 0;
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
	
	v.push_back(label1);
	v.push_back(button1);
	
	for (auto &iter: v) {
		iter->show();
	}
}