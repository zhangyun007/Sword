/*
 * http://en.cppreference.com/w/cpp/container/vector/erase
 */

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

/*多处malloc失败的代码，这部分是否可以优化一下？*/

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
	}
};

template <class T, class U> 
class TPair: TObject {
public:
	TPair(T t, U u) {
		first = t;
		second = u;
	}
private:
	T first;
	U second;
};

//智能指针，自动释放ptr指向的对象
template <class T> 
class TAutoPtr {
public:
	//传入对象指针
	TAutoPtr(T *t) {
		ptr = t;
	} 
	~ TAutoPtr() {
		delete ptr;
	}
	/*
	void * operator =(const T *t) const{
		ptr = t;
	}*/
	T * GetObjectPtr() {
		return ptr;
	}
	void show() {
	}
private:
	T *ptr;
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


//长字符串。用len储存字符串长度，这样避免了读者的程序中多次用strlen计算长度
//大致上，字符串越长，需要用strlen的地方越多，TString的好处越明显。

class TString : TObject {
public:
	void show() {
		if (str) {
			cout << str << "\n";
		}
	}
	TString() {
		str = NULL;
		len = 0;
	}
	TString(char *p) {
		len = strlen(p);
		str = (char *)malloc(len + 1);
		if (str == NULL) {
			cout << "malloc fail, cause TString fail.\n";
		}
		strcpy(str, p);
		str[len] = '\0';
	}
	//注意：复制构造函数参数前要加上“&"
	TString(TString& s) {
		str = (char *)malloc(s.GetLen() + 1);
		if (str == NULL) {
			cout << "malloc fail, cause TString fail.\n";
		}
		strcpy(str, s.GetStr());
		str[len] = '\0';
	}
	TString & operator =(TString &s) {
		if (this != &s) {
			str = (char *)malloc(s.GetLen() + 1);
			len = s.GetLen();
			strcpy(str, s.GetStr());
			str[len] = '\0';
		}
		return *this;
	}
	virtual ~TString() {
		free(str);
	}
	char *GetStr() {
		return str;
	}
	int GetLen() {
		return len;
	}
	void StrCat(char *p) {
		char * tmp = (char *)malloc(strlen(str) + strlen(p));
		strcpy(tmp, str);		strcat(tmp, p);

		free(str);
		str = tmp;
	}
private:
	char *str; //以\0结尾，中文字符用两个字节保存
	int len;	//字符串长度，不包括\0，
};


/*
stl容器中end()总是返回最后一项的下一项。
*/

/*
基本按照stl vector实现。Vector分配内存成倍增长。
*/
template <class T>
class TVector: TObject {
public:
	typedef T * Iterator;
	void show() {
		cout << "TVector Capacity = " << capacity() << " size = "  << size() << "...\n";
	}
	TVector() {
		// 新C++中new失败会抛出一个异常对象，但是C++也提供了老式的通过返回值是否为NULL来判断内存是否申请成功。
		//这个内存申请操作符函数为：new(std::nothrow)，我还是喜欢传统的空指针判断方式，不喜欢抛出异常对象处理方式。
		finish = start =  new(std::nothrow) T;
		//分配内存失败,这里需要改正，new失败不是返回NULL，而是抛出异常。
		if (start == NULL) {
			//这里最好打印到log文件，因为有可能没有console
			cout << "new(std::nothrow) T fail, cause TVector constructor fail.\n";
			return;
		}
		end_of_storage = start + 1;
	}
	virtual ~TVector() {
		delete [] start;
	}
	void push_back(T t) {
		if (finish < end_of_storage) {
			//还有空余空间，下面语句要求class T实现了operator =
			*finish = t;
			finish++;
		} else {
			//此时，finish == end_of_storage, 表示空间已满，capacity和size一样大。
			 int c = capacity();
			 
			//重新分配原来2倍大小的内存
			T * nstart = new(std::nothrow) T[2 * c];
			//分配内存失败
			if (nstart == NULL) {
				//这里最好打印到log文件，因为有可能没有console
				cout << "new(std::nothrow) T[2*c] fail, cause push_back fail.\n";
				return;
			}
			
			//复制旧内存到新内存, 可能需要拷贝构造
			//todo
			memcpy(nstart, start, c * sizeof(T));
			delete [] start;
			
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
		return finish;
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
	Iterator start;		//使用空间头指针
	Iterator finish;		//使用空间尾指针
	Iterator end_of_storage;		//总空间尾指针
};


template <class T>
struct _list_node {
	T t;
	struct _list_node<T> *prev;
	struct _list_node<T> *next;
};

//双向链表，能很快在任意位置插入节点。
template <class T>
class TList: TObject {
public:
	struct	Iterator {
		struct _list_node<T> *node; //node指向节点
		Iterator(struct _list_node<T> *x):node(x) {};
		//接下里实现迭代器的各种operator
		T operator *() {
			return node->t;
		}
		struct _list_node<T> * operator ++() {
			return (node = node->next);
		}
		bool operator !=(struct Iterator right) {
			return (node != right.node);
		}
	};
	void show() {
		struct _list_node<T> *tmp = node;
		cout << "TList.\n";
		while (1) {
			tmp = tmp->next;
			if (tmp != node) 
				cout << tmp->t << " ";
			else 
				break;
		}
	}
	TList() {
		//node为空节点，prev和next都指向自己
		node = create_node(0);
		node->next = node;
		node->prev = node;
	}
	virtual ~TList() {
		//tmp指向当前链表的最后一个节点，node为最后一个节点的下一个空节点。
		struct _list_node<T> *tmp;
		while (1) {
			tmp = node->prev;	
			
			if (tmp == node) break;
			
			//将tmp从链表中断开
			tmp->prev->next = node;
			node->prev = tmp->prev;
			
			free(tmp);
		}
		free(node);
	}
	//在curr迭代器指向的节点前插入新节点
	Iterator insert(Iterator curr, T t) {
		struct _list_node<T> * tmp =  create_node(t);
		//设置tmp的next和prev域
		tmp->next = curr.node;
		tmp->prev = curr.node->prev;
		
		//tmp前一个节点的next域设为tmp
		curr.node->prev->next = tmp;
		
		//curr节点的prev域设为tmp
		curr.node->prev = tmp;
		
		//返回新插入的节点，将调用Iterator的构造函数。
		return tmp;
	}
	Iterator begin() {
		//TList呈环状，首尾相连，尾指针node的next域即为首指针。
		return node->next; 
	}
	Iterator end() {
		return node;
	}
private:
	struct _list_node<T> * create_node(T t) {
		struct _list_node<T> *tmp = new(std::nothrow) (struct _list_node<T>);
		if (tmp == NULL) {
			cout << "create_node fail, because new(std::nothrow) fail.\n";
		}
		tmp->t = t;
		tmp->next = tmp->prev = NULL;
		
		return tmp;
	}
	struct _list_node<T> * node; //node指向最后一个节点的下一个节点
};


template <class T>
class TDeque: TObject {
	void show() {
		cout << "TDeque.\n";
	}
};

template <class T>
class TBSTMap: TObject {
};

template <class T>
class TBSTSet: TObject {
};

template <class T>
class TAVLMap: TObject {
};

template <class T>
class TAVLSet: TObject {
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



/*全局函数，包括各种STL算法函数*/

void TLog(char *info) {
	TString ts(_pgmptr);
	ts.StrCat(".log");
	cout << ts.GetStr() << "\n"; 
}
	
/*返回指定值的迭代器，如果没有查到，返回end
如下代码说明迭代器必须实现operator ++，operator *和operator ！=
而C指针指针++，*和！=，可以当做迭代器传入,Tvector中的迭代器即为普通指针。
*/
template<class Iter, class T>
Iter TFind(Iter begin, Iter end, const T &value) {
	while (begin != end && *begin != value)
		++begin;
	return begin;
}


