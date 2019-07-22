/*
 * http://en.cppreference.com/w/cpp/container/vector/erase
 */

#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>

using namespace std;
/*
本程序目的是为了实现类似Python里的列表、字典、集合，这三种数据结构中都可以存放各种类型的数据，而STL容器只能存放特定类型的对象。
TObject为所有类的父类，TObject *指针类型则可以指向所有的自定义类型对象。
结合vector和map，我们可以得到一个保存所有对象指针的vector和能保存任意类型key和value的map。
接下来，我们实现自己的vector和map，继承自TObject。

所有类继承自一个TObject类不是我原创，而是从Delphi的VCL库（一个优秀的面向对象库）中学到的。
*/

/*
本程序计划实现STL中的各种容器，包括序列式容器vector，list，deque以及关联式容器map，set，unordered_map，unordered_set，区别是这些容器都继承自TObject。
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

/*
基本按照stl vector实现。Vector分配内存成倍增长。
*/
template <class T>
class TVector: TObject {
public:
	void show() {
		cout << "TVector Capacity = " << capacity() << " size = "  << size() << "...\n";
	}
	TVector() {
		finish = start = (T *)malloc(1 * sizeof(T));
		end_of_storage = start + 1;
	}
	virtual ~TVector() {
		free(start);
	}
	void push_back(T t) {
		if (finish < end_of_storage) {
			//还有空间
			*finish = t;
			finish++;
		} else {
			//此时，finish == end_of_storage, 表示空间已满，capacity和size一样大。
			 int c = capacity();
			 
			//重新分配原来2倍大小的内存
			T * nstart = (T *)malloc(2 * c * sizeof(T));
			//复制旧内存到新内存
			memcpy(nstart, start, c * sizeof(T));
			//释放旧空间
			free(start);
			
			//重置各项指针值
			start = nstart;
			finish = start + c;
			*finish = t;
			finish++;
			end_of_storage = start + 2*c;
		}
	}
	T * begin() {
		return start;
	}
	T * end() {
		return end_of_storage;
	}
	/*可分配空间总容量*/
	int capacity() {
		return end_of_storage - start;
	}
	/**已占用空间大小*/
	int size () {
		return finish - start;
	}
private:
	T * start;		//使用空间头指针
	T * finish;		//使用空间尾指针
	T * end_of_storage;		//总空间尾指针
};

template <class T>
class TList: TObject {
	void show() {
		cout << "TList.\n";
	}
};

template <class T>
class TDeque: TObject {
	void show() {
		cout << "TDeque.\n";
	}
};

/*STL map用红黑树实现，太复杂，我们用Btree、BST或者AVLtree实现，排序的map和set*/
template <class T>
class TBtreeMap: TObject {
	void show() {
		cout << "TBtreeMap.\n";
	}
};

template <class T>
class TBtreeSet: TObject {
	void show() {
		cout << "TBtreeSet.\n";
	}
};

/*未排序的map和set*/
template <class T>
class THashMap: TObject {
	void show() {
		cout << "THashMap.\n";
	}
};

template <class T>
class THashSet: TObject {
	void show() {
		cout << "THashSet.\n";
	}
};

class Test {
public:
	int i;
	char ch;
};

int main()
{
	std::vector<TObject *> v;
	
	class TObject * label1 = (TObject *)new TLabel();
	class TObject * button1 = (TObject *)new TButton();
	class TObject * int1 = (TObject *)new TInt(3);
	
	class TObject * v1 = (TObject *)new TVector<int>;
	class TObject * v2 = (TObject *)new TVector<float>;
	
	v.push_back(label1);
	v.push_back(button1);
	v.push_back(int1);
	
	v.push_back(v1);
	v.push_back(v2);
	
	for (auto &iter: v) {
		iter->show();
	}
	
	std::unordered_map<TObject *, TObject *> m;
	m[label1] = label1;
	m[button1] = button1;
	m[int1] = label1;
	m[v1] = v2;
	m[v2] = v1;
	
	delete label1;
	delete button1;
	delete int1;
	
	delete v1;
	delete v2;
	
	TVector<int> Tv;
	Tv.show();
	Tv.push_back(1);
	Tv.show();
	Tv.push_back(3);
	Tv.show();
	Tv.push_back(5);
	Tv.show();
	Tv.push_back(7);
	Tv.show();
	
	for (auto &i : Tv) {
		cout << i << " ";
	}
	cout << "\n";

	TVector<Test> Tt;
	class Test t;
	t.i = 1; t.ch = 'a';
	Tt.push_back(t);
	t.i = 2; t.ch = 'b';
	Tt.push_back(t);
	t.i = 3; t.ch = 'c';
	Tt.push_back(t);
	
	Tt.show();	
	
	return 0;
}