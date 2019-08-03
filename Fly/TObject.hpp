/*
 * http://en.cppreference.com/w/cpp/container/vector/erase
 */

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

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


/*�ദmallocʧ�ܵĴ��룬�ⲿ���Ƿ�����Ż�һ�£�*/

/*
������Ŀ����Ϊ��ʵ������Python����б��ֵ䡢���ϣ����������ݽṹ�ж����Դ�Ÿ������͵����ݣ���STL����ֻ�ܴ���ض����͵Ķ���
TObjectΪ������ĸ��࣬TObject *ָ�����������ָ�����е��Զ������Ͷ���
���vector��map�����ǿ��Եõ�һ���������ж���ָ���vector���ܱ�����������key��value��map��
������������ʵ���Լ���vector��map���̳���TObject��

������̳���һ��TObject�಻����ԭ�������Ǵ�Delphi��VCL�⣨һ��������������⣩��ѧ���ġ�
*/

/*
������ƻ�ʵ��STL�еĸ�����������������ʽ����vector��list��deque�Լ�����ʽ����map��set��unordered_map��unordered_set����������Щ�������̳���TObject��
*/
class TObject {
public:
	//�㺯����ʾ�ú����ڵ�ǰ���в��ñ�ʵ�֣�ͬʱ��ζ�Ÿ��಻��ʵ�������麯����ζ�Ÿú����������п����в�ͬ��ʵ�֣�
	virtual void show() = 0;
	//��һ����������ʱ����������������������麯���������������ɾ��ʱ������������������ᱻ���á�
	//���������������������������ʱ���ȵ�������������������ٵ��ø��������������
	//����������������߶�ʮһ�����������������ͼ�һ��virtual���϶�û��
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

//���ַ�������len�����ַ������ȣ����������˶��ߵĳ����ж����strlen���㳤��
//�����ϣ��ַ���Խ������Ҫ��strlen�ĵط�Խ�࣬TString�ĺô�Խ���ԡ�

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
	//ע�⣺���ƹ��캯������ǰҪ���ϡ�&"
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
	char *str; //��\0��β�������ַ��������ֽڱ���
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
stl������end()���Ƿ������һ�����һ�
STL��ʵ�����ڴ�أ�ͨ���ڴ���������ͷ��ڴ棬��˼����һ���������ڴ棬���û����������һ����ڴ棬��������Ҫ�ڴ�ʱ�����û����������ڴ�������룬����Ҫ���ڴ��ͷŵ��ڴ���﹩�´�ʹ�ã�����û�й黹������ϵͳ��Ҳ����˵��������ò����������Ѿ��ͷŵ��ڴ棬���Ǳ����̽������ڴ�ع黹������ϵͳ��
*/

/*
��������stl vectorʵ�֡�Vector�����ڴ�ɱ�������
*/
template <class T>
class TVector: TObject {
public:
	typedef T * Iterator;
	void show() {
		cout << "TVector Capacity = " << capacity() << " size = "  << size() << "...\n";
	}
	TVector() {
		// ��C++��newʧ�ܻ��׳�һ���쳣���󣬵���C++Ҳ�ṩ����ʽ��ͨ������ֵ�Ƿ�ΪNULL���ж��ڴ��Ƿ�����ɹ���
		//����ڴ��������������Ϊ��new(std::nothrow)���һ���ϲ����ͳ�Ŀ�ָ���жϷ�ʽ����ϲ���׳��쳣������ʽ��
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
			//���п���ռ䣬�������Ҫ��class Tʵ����operator =
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
			
			//�������Ҫ��class Tʵ����operator =
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
	/*�ɷ���ռ�������*/
	int capacity() {
		return end_of_storage - start;
	}
	/**��ռ�ÿռ��С*/
	int size () {
		return finish - start;
	}
private:
	Iterator start;		//�ռ�ͷָ��
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
		//������ʵ�ֵ������ĸ���operator
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
    struct MapNode * left;
    struct MapNode * right;
};

/*STL map�ú����ʵ�֣�̫���ӣ�������Btree��BST����AVLtreeʵ�֣������map��set*/

template <class T, class U>
class TMap: TObject {
public:
	//TMap������������ָ��ĳ���ڵ��ָ�롣
	//˼��Ҫʵ����Щ������
	class ITerator {
	private:
		struct  MapNode<T, U>* node;
	public:
		//���������캯��
		ITerator(struct  MapNode<T, U> * p){node = p;}
		struct  MapNode<T, U> * operator *(class ITerator p) {
			return (p.node);
		}
	};
	
	virtual void show() {
		cout << "TMap.\n";
	}
	
	virtual U& operator [](T& t) = 0;
	
    virtual ITerator Insert(T t, U u) = 0;
	
	virtual U find(T& t);
    virtual int Traver() = 0;	
    virtual void Delete(T t) = 0;
	
	//�ѽڵ�д��BSPMapNodeToDisk�ṹ��
    virtual void Write() = 0;
	
	virtual ~TMap() {
		cout << "TMap \n";
	}
};


/* 
* DiskNode�ṹ��Ҫд�������ϵ�
* ����������ΪʲôҪд�������ļ����������ݿ������Ļ��������ݿ��������ǽ�����ƽ����д�����̱���Ϊ�����ļ���ͨ�����������ļ����ӿ�ı�Ĳ�ѯ��
* �����ݿ���е�ĳ���н�������������ֻ��Ҫkey������Ҫvalue��
*/
template <class T, class U>
struct  MapNodeToDisk{
    T   key;
    U   value;
    int left;
    int right;
	int	offset;	// ���¼ƫ������ָ���Ӧ�����ݿ���еļ�¼��
};

/* Binary Search Tree ����������*/
template <class T, class U>
class TBSTMap: TMap<T, U> {
public:
    TBSTMap():root(NULL){}        
    ~TBSTMap() {
		DeleteNode(root);
	}
	U& operator [](T& t) {
		return (*FindKey(root, t)).u;
	}
	ITerator Insert(T t, U u) {
		return InsertNode(root, t, u);
	}
	//����ʽ������Ҫ�Լ�ʵ��Find��������ȫ�ֵ�TFind
	U& Find(T& t) {
		return (*FindKey(root, t)).u;
	��

private:
    class MapNode<T, U> * root;
	
	ITerator FindKey(ITerator node, T t)
	{
		if (node == NULL) {
			return NULL;
		} else {
			if (t < (*node).key) 
				cout << t << " < " << (*node).key <<'\n';
				return FindKey((*node).left, t);
			} else if (t > (*node).key) {
				cout << t << " > " << (*node).key <<'\n';
				return FindKey((*node).right, t);
			} else if (t == (*node).key) {
				cout << t << " == " << (*node).key <<'\n';
				return node;
			}
				return NULL;
		}
	}

	//�ڵ����
	int Traver()
	{
		return TraverTree(root);
	}

	int TraverTree(class MapNode<T, U> *node)
	{
		if (node == NULL) {
			return 0;
		}
		int m = TraverTree(node->left);
		cout << "key is " << node->key << " value is " << node->value << '\n';
		int n = TraverTree(node->right);
		return m + n + 1;
	}
	
    // nodeǰ���&�����٣�����������
	class MapNode<T, U> * InsertNode(class MapNode<T, U> *&node, T t, U u)
	{
		if (node == NULL) {
			//���ڵ�ָ���½��ӽڵ�
			node = new MapNode<T, U>();
			node->key = t;
			node->value = u;
			return node;
		}
	
		if (node->key > t) {
			return InsertNode(node->left, t, u);
		}
	
		if (node->key < t) {
			return InsertNode(node->right, t, u);
		}
	
		if (node->key == t) {
			node->value = u;
			cout << "key " << t << " modified to " << u << '\n';
		}
	}

	//ɾ����node�ڵ�Ϊ���ڵ����
    void DeleteNode(class MapNode<T, U> *node)
	{
		if (node->left) {
			DeleteNode(node->left);
		}
		if (node->right) {
			DeleteNode(node->right);
		}
		if (node) {
			delete node;
		}
	}
	
	//��nodeΪ���ڵ�����У�ɾ��keyΪt�Ľڵ㡣
    // nodeǰ���&�����٣�����������
	void DeleteNode(class MapNode<T, U> *&node, T t)
	{
		if (node == NULL) {
			return;
		}
	
		if (node->key > t) {
			DeleteNode(node->left, t);
		}
	
		if (node->key < t ) {
			DeleteNode(node->right, t);
		}
	
		if (node->key == t) {
			if (node->left && node->right) {
				class MapNode<T, U> * temp = node->right;
				while (temp->left != NULL) {
					temp = temp->left;
				}
				node->key = temp->key;
				node->value = temp->value;
				DeleteNode(node->right, temp->key);
			} else {
				class MapNode<T, U> * temp = node;
				if (node->left == NULL) {
					node = node->right;
				} else if (node->right == NULL) {
					node = node->left;
				}
				delete(temp);
			}
		}
	}
	
	
	void Delete(T t)
	{
		DeleteNode(root, t);
	}
	/*
	* ����ֵ��ʾ��������n���ڵ�
	*/
	/*
	int WriteNode(class MapNode<T, U> *node)
	{
		if (node == NULL)
			return 0;
	
		int m = WriteNode(node->left);
	
		struct MapNodeToDisk<T, U> dnode;
		dnode.key = node->key;
		dnode.value = node->value;
		if (node->left == NULL)
			dnode.left = 0;
		else
			dnode.left = -m - 1;
		if (node->right ==NULL)
			dnode.right = 0;
		else
			dnode.right = TraverTree(node->right->left) + 1;
	
		cout << "key " << dnode.key << " value " << dnode.value << " left " << dnode.left << " right " << dnode.right << '\n';
	
		WriteNode(node->right);
	
		// ����������ӵ�еĽڵ���Ŀ
		return TraverTree(node->right);
	}
	void Write()
	{
		WriteNode(root);
	}
	*/
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


template <class T, class U>
struct  SetNode{
    T   key;
    struct SetNode * left;
    struct SetNode * right;
};

template <class T>
class TBSTSet: TSet<T> {
};


/*

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

*/

/*δ�����map��set*/
/*
template <class T, class U>
class THashMap: TMap {
	void show() {
		cout << "THashMap.\n";
	}
};

template <class T>
class THashSet: TSet {
	void show() {
		cout << "THashSet.\n";
	}
};
*/

/*ȫ�ֺ������������ַ����㷨����*/

void TLog(char *info) {
	TString ts(_pgmptr);
	ts.StrCat(".log");
	cout << ts.GetStr() << "\n"; 
}
	
/*����ָ��ֵ�ĵ����������û�в鵽������end
���´���˵������������ʵ��operator ++��operator *��operator ��=
��Cָ��ָ��++��*�ͣ�=�����Ե�������������,Tvector�еĵ�������Ϊ��ָͨ�롣
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
