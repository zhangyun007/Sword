/*
 * http://en.cppreference.com/w/cpp/container/vector/erase
 */

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//智能指针，自动释放ptr指向的对象
template <class T> 
class AutoPtr {
public:
	//传入对象指针
	AutoPtr(T *t) {
		ptr = t;
	} 
	~ AutoPtr() {
		delete ptr;
	}
	T * GetObjectPtr() {
		return ptr;
	}
	void show() {
	}
private:
	T *ptr;
};


/*多处malloc失败的代码，这部分是否可以优化一下？*/

/*
Python里的列表、字典、集合，这三种数据结构中都可以存放任意类型的对象，而STL容器只能存放一种特定类型的对象。
TObject为所有类的父类，TObject *指针类型则可以指向所有的子类对象。结合vector和map，我们可以得到一个保存TObject *的vector和能保存key和value都是TObject *的map。
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
	char * operator *(TString &s) {
		return str;
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

/*
STL里实现了内存池，通过内存池来申请释放内存，其思想是一次申请大块内存，由用户程序管理这一大块内存，当程序需要内存时，从用户程序管理的内存池中申请，不需要的内存释放到内存池里供下次使用，而并没有归还给操作系统，也就是说其他程序得不到本程序已经释放的内存，除非本进程结束，内存池归还给操作系统。
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
			//还有空余空间，下面语句要求class T实现了operator = 和 operator ++
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
			memcpy(nstart, start, size() * sizeof(T));
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
	//stl容器中end()总是返回最后一项元素的下一项，其实是个无效指针。
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
	Iterator start;			//空间头指针
	Iterator finish;		//空间尾指针
	Iterator end_of_storage;	//当finish等于end_of_storage时，空间完全占满。
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
		//实现迭代器的各种operator
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

template <class T, class U>
struct  MapNode {
    T   key;
    U   value;
    struct MapNode<T, U> * left;
    struct MapNode<T, U> * right;
};

template <class T, class U>
class TMap: TObject {
};

template <class T>
struct  SetNode{
    T   key;
    struct SetNode * left;
    struct SetNode * right;
};

template <class T>
class TSet: TObject {
	virtual void show() {
		cout << "TSet.\n";
	}
    virtual void Insert(T t) = 0;
    virtual void Find(T t) = 0;
    virtual int Traver() = 0;
    virtual void Delete(T t) = 0;
	
	//把节点写到BSPMapNodeToDisk结构中
    virtual void Write() = 0;
	
	virtual ~TSet() {
		cout << "TSet \n";
	}
};

template <class T, class U>
class TBSTMap: TMap<T, U> {
};

template <class T>
class TBSTSet: TSet<T> {
};

template <class T, class U>
class TAVLMap:TMap<T, U> {
};

template <class T>
class TAVLSet:TSet<T> {
};

template <class T, class U>
class TBtreeMap: TMap<T, U> {
	void show() {
		cout << "TBtreeMap.\n";
	}
};

template <class T>
class TBtreeSet: TSet<T> {
	void show() {
		cout << "TBtreeSet.\n";
	}
};

template <class T, class U>
class TRBtreeMap: TMap<T, U> {
	void show() {
		cout << "TBtreeMap.\n";
	}
};

template <class T>
class TRBtreeSet: TSet<T> {
	void show() {
		cout << "TBtreeSet.\n";
	}
};

/*未排序的map和set*/
template <class T, class U>
class THashMap: TMap<T, U> {
	void show() {
		cout << "THashMap.\n";
	}
};

template <class T>
class THashSet: TSet<T> {
	void show() {
		cout << "THashSet.\n";
	}
};


/*全局函数，包括各种泛型算法函数*/
void TLog(char *info) {
	TString ts(_pgmptr);
	ts.StrCat(".log");
	cout << ts.GetStr() << "\n"; 
}
	
/*返回指定值的迭代器，如果没有查到，返回end
如下代码说明迭代器必须实现operator ++，operator *和operator ！=
而C指针指针++，*和！=，可以当做迭代器传入,Tvector中的迭代器即为普通指针。
TFind函数只适用于序列式容器
*/
template<class Iter, class T>
Iter TFind(Iter begin, Iter end, const T &value) {
	while (begin != end && *begin != value)
		++begin;
	return begin;
}

template<class T>
bool TGreat(T &a, T &b) {
	return (a > b);
}

template<class Iter, class T>
void TSort(Iter first, Iter last) {
	return;
}