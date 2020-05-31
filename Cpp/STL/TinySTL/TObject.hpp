/*
 * http://en.cppreference.com/w/cpp/container/vector/erase
 */

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

/*�ദmallocʧ�ܵĴ��룬�Ƿ���ԶԴ�����һ�£�*/

/*Python�����б��ֵ䡢���ϣ����������ݽṹ�����Դ���������͵Ķ��󣬶�STL����ֻ�ܴ��һ���ض����͵Ķ������ϣ���洢��ͬ���͵Ķ��󣬿��Դ洢void *ָ��������ͣ��ַ��������ο�vector5.cpp��

�������ƻ�ʵ��STL�еĶ��������ͳ����㷨����������ʽ����vector��list��deque�Լ�����ʽ����map��set��unordered_map��unordered_set��

���ǽ�Ҫʵ�ֵ��������̳���TObject��TObjectΪ������ĸ��࣬���TObjectָ�����������ָ�����е�����������ַ������ڶ�����������У�����Java���Լ�Delphi��VCL�⡣

*/


//����ָ�룬�Զ��ͷ�ptrָ��Ķ���
template <class T> 
class AutoPtr {
public:
	//�������ָ��
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


class TObject {
public:
	//�㺯����ʾ�ú����ڵ�ǰ����û�ж��壬ͬʱ��ζ�Ÿ��಻��ʵ������
	//�麯��virtual��ζ�Ÿú����������п����в�ͬ��ʵ�֣�
	virtual void show() = 0;
	//��һ����������ʱ����������������������麯���������������ɾ��ʱ������������������ᱻ���á�
	//���������������������������ʱ���ȵ�������������������ٵ��ø��������������
  
	//���������������ͼ�һ��virtual���϶�û��
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
		cout << i << "�� TInt destruct.\n";
	}
private:
	int i;
};

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
		str = (char *)malloc(len + 1);
		if (str == NULL) {
			cout << "malloc fail, cause TString fail.\n";
		}
		strcpy(str, p);
		str[len] = '\0';
		len = strlen(p);
	}
	//ע�⣺���ƹ��캯������ǰҪ���ϡ�&"
	TString(TString& s) {
		str = (char *)malloc(s.GetLen() + 1);
		if (str == NULL) {
			cout << "malloc fail, cause TString fail.\n";
		}
		strcpy(str, s.GetStr());
		str[len] = '\0';
		len = s.GetLen();
	}
	TString & operator =(TString &s) {
		if (this != &s) {
			str = (char *)malloc(s.GetLen() + 1);
			strcpy(str, s.GetStr());
			str[len] = '\0';
			len = s.GetLen();
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
		strcpy(tmp, str);		
		strcat(tmp, p);
		free(str);
		
		str = tmp;
		len = strlen(tmp);
	}
private:
	char *str;  //��\0��β�������ַ��������ֽڱ���
	int len;	//�ַ������ȣ�������\0��
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
STL��ʵ�����ڴ�أ�ͨ���ڴ���������ͷ��ڴ棬��˼����һ���������ڴ棬���û����������һ����ڴ棬��������Ҫ�ڴ�ʱ�����û����������ڴ�������룬����Ҫ���ڴ��ͷŵ��ڴ���﹩�´�ʹ�ã�����û�й黹������ϵͳ��Ҳ����˵��������ò����������Ѿ��ͷŵ��ڴ棬���Ǳ����̽������ڴ�ع黹������ϵͳ��
*/
template <class T>
class TVector: TObject {
public:
	typedef T * Iterator;
	void show() {
		cout << "TVector Capacity = " << capacity() << " size = "  << size() << "...\n";
	}
	TVector() {
		//C++��newʧ�ܻ��׳�һ���쳣���󣬵���Ҳ�ṩ����ʽ�ķ���������ֵ�Ƿ�ΪNULL��
		//����ڴ��������������Ϊ��new(std::nothrow)
		finish = start =  new(std::nothrow) T;
		if (start == NULL) {
			//������ô�ӡ��log�ļ�����Ϊ�п���û��console
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
			//���п���ռ䣬�������Ҫ��class Tʵ����operator = �� operator ++
			*finish = t;
			finish++;
		} else {
			//��ʱ��finish == end_of_storage, ��ʾ�ռ�������capacity��sizeһ����
			 int c = capacity();
			 
			//���·���ԭ��2����С���ڴ�
			T * nstart = new(std::nothrow) T[2 * c];
			//�����ڴ�ʧ��
			if (nstart == NULL) {
				//������ô�ӡ��log�ļ�����Ϊ�п���û��console
				cout << "new(std::nothrow) T[2*c] fail, cause push_back fail.\n";
				return;
			}
			
			//���ƾ��ڴ浽���ڴ�, ������Ҫ��������
			//todo
			memcpy(nstart, start, size() * sizeof(T));
			delete [] start;
			
			//���ø���ָ��ֵ
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
	//stl������end()���Ƿ������һ��Ԫ�ص���һ���ʵ�Ǹ���Чָ�롣
	T * end() {
		return finish;
	}
	/*�ɷ���ռ�������*/
	int capacity() {
		return end_of_storage - start;
	}
	/**��ռ�ÿռ��С*/
	int size () {
		return finish - start;
	}
private:
	Iterator start;			//�ռ�ͷָ��
	Iterator finish;		//�ռ�βָ��
	Iterator end_of_storage;	//��finish����end_of_storageʱ���ռ���ȫռ����
};


template <class T>
struct _list_node {
	T t;
	struct _list_node<T> *prev;
	struct _list_node<T> *next;
};

//˫�������ܺܿ�������λ�ò���ڵ㡣
template <class T>
class TList: TObject {
public:
	struct	Iterator {
		struct _list_node<T> *node; //nodeָ��ڵ�
		Iterator(struct _list_node<T> *x):node(x) {};
		//ʵ�ֵ������ĸ���operator
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
		//nodeΪ�սڵ㣬prev��next��ָ���Լ�
		node = create_node(0);
		node->next = node;
		node->prev = node;
	}
	virtual ~TList() {
		//tmpָ��ǰ��������һ���ڵ㣬nodeΪ���һ���ڵ����һ���սڵ㡣
		struct _list_node<T> *tmp;
		while (1) {
			tmp = node->prev;	
			
			if (tmp == node) break;
			
			//��tmp�������жϿ�
			tmp->prev->next = node;
			node->prev = tmp->prev;
			
			free(tmp);
		}
		free(node);
	}
	//��curr������ָ��Ľڵ�ǰ�����½ڵ�
	Iterator insert(Iterator curr, T t) {
		struct _list_node<T> * tmp =  create_node(t);
		//����tmp��next��prev��
		tmp->next = curr.node;
		tmp->prev = curr.node->prev;
		
		//tmpǰһ���ڵ��next����Ϊtmp
		curr.node->prev->next = tmp;
		
		//curr�ڵ��prev����Ϊtmp
		curr.node->prev = tmp;
		
		//�����²���Ľڵ㣬������Iterator�Ĺ��캯����
		return tmp;
	}
	Iterator begin() {
		//TList�ʻ�״����β������βָ��node��next��Ϊ��ָ�롣
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
	struct _list_node<T> * node; //nodeָ�����һ���ڵ����һ���ڵ�
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
    T   kv;		//key��value��ͬ
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
	
	//�ѽڵ�д��BSPMapNodeToDisk�ṹ��
    virtual void Write() = 0;
	
	virtual ~TSet() {
		cout << "TSet \n";
	}
};

/*δ�����map��set*/
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

/*
 *234��ÿһ���ڵ������2��3��4���ӽڵ㣬�ڵ������3�����ݽṹ��ʾ
 */
template <class T, class U>
class T234treeMap: TMap<T, U> {
	void show() {
		cout << "TBtreeMap.\n";
	}
};

template <class T>
class T234treeSet: TSet<T> {
	void show() {
		cout << "TBtreeSet.\n";
	}
};


//B-Tree��Ϊ���̵���洢�豸��Ƶ�һ��ƽ���������
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


/*ȫ�ֺ������������ַ����㷨����*/
void TLog(char *info) {
	TString ts(_pgmptr);
	ts.StrCat(".log");
	cout << ts.GetStr() << "\n"; 
}
	
/*����ָ��ֵ�ĵ����������û�в鵽������end

Iter����ʵ��operator ++��operator *��operator ��=

Cָ�������++��*�ͣ�=���㣬���Կ��Ե�������������,TVector�еĵ�������Ϊ��ָͨ�롣

TFind����ֻ����������ʽ����
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