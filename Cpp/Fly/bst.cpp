#include <iostream>

using namespace std;

template <class T, class U>
struct  Node{
    T   key;
    U   value;
    struct Node * left;
    struct Node * right;
};

template <class T, class U>
struct  DNode{
    T   key;
    U   value;
    int left;
    int right;
};

template <class T, class U>
class BST {
    private:
        class Node<T, U> * root;
        // node前面的&不能少，否则程序错误。
        void InsertNode(class Node<T, U> *&node, T t, U u);
        class Node<T, U> * FindKey(class Node<T, U> *node, T t);
        int TraverTree(class Node<T, U> *node);
        void DeleteNode(class Node<T, U> *node);
        // node前面的&不能少，否则程序错误。
        void DeleteNode(class Node<T, U> *&node, T t);
        int WriteNode(class Node<T, U> *node);
    public:
        BST():root(NULL){}        
        ~BST();
        void Insert(T t, U u);
        void Find(T t);
        int Traver();
        void Delete(T t);
        void Write();
};

template <class T, class U>
void DeleteNode(class Node<T, U> *node)
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

template <class T, class U>
BST<T, U>::~BST()
{
    //看这里！！！！！！！ 这是同名覆盖原则, 使用域标志:: 。这种写法在MFC中尤其常见。
    //例如在mfc中调用库中没有封装的api就会这么写 ::SendMessage(...);
    ::DeleteNode(root);
}

template <class T, class U>
void BST<T, U>::InsertNode(class Node<T, U> *&node, T t, U u)
{
    if (node == NULL) {
        //父节点指向新建子节点
        node = new Node<T, U>();
        node->key = t;
        node->value = u;
        return;
    }

    if (node->key > t) {
        InsertNode(node->left, t, u);
    }

    if (node->key < t) {
        InsertNode(node->right, t, u);
    }

    if (node->key == t) {
        node->value = u;
        cout << "key " << t << " modified to " << u << '\n';
    }
}

template <class T, class U>
void BST<T, U>::Insert(T t, U u) {
    InsertNode(root, t, u);
}

template <class T, class U>
class Node<T, U> * BST<T, U>::FindKey(class Node<T, U> *node, T t)
{
    if (node == NULL) {
        return NULL;
    } else {
        if (t < node->key) {
            cout << t << " < " << node->key <<'\n';
            return FindKey(node->left, t);
        } else if (t > node->key) {
            cout << t << " > " << node->key <<'\n';
            return FindKey(node->right, t);
        } else if (t == node->key) {
            cout << t << " == " << node->key <<'\n';
            cout << node << '\n';
            return node;
        }
        return NULL;
    }
}

template <class T, class U>
void BST<T, U>::Find(T t)
{
    class Node<T, U> *temp;
    temp = FindKey(root, t);
    if (temp) {
        cout << "Find key " << t << " value is" << temp->value << '\n';
    } else {
        cout << "Not find key "  << t << '\n';
    }
}

template <class T, class U>
int BST<T, U>::TraverTree(class Node<T, U> *node)
{
    if (node == NULL) {
        return 0;
    }
    int m = TraverTree(node->left);
    cout << "key is " << node->key << " value is " << node->value << '\n';
    int n = TraverTree(node->right);
    return m + n + 1;
}

template <class T, class U>
int BST<T, U>::Traver()
{
    return TraverTree(root);
}

template <class T, class U>
void BST<T, U>::DeleteNode(class Node<T, U> *&node, T t)
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
            class Node<T, U> * temp = node->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            node->key = temp->key;
            node->value = temp->value;
            DeleteNode(node->right, temp->key);
        } else {
            class Node<T, U> * temp = node;
            if (node->left == NULL) {
                node = node->right;
            } else if (node->right == NULL) {
                node = node->left;
            }
            delete(temp);
        }
    }
}

template <class T, class U>
void BST<T, U>::Delete(T t)
{
    DeleteNode(root, t);
}

/*
 * 返回值表示右子树有n个节点
 */
template <class T, class U>
int BST<T, U>::WriteNode(class Node<T, U> *node)
{
    if (node == NULL)
        return 0;

    int m = WriteNode(node->left);

    class DNode<T, U> dnode;
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

    return TraverTree(node->right);
}

template <class T, class U>
void BST<T, U>::Write()
{
    WriteNode(root);
}

int main(int argc, char *argv[])
{

    class BST<int, int> bst;

    bst.Insert(20, 21);
    bst.Insert(13, 32);
    bst.Insert(16, 12);
    bst.Insert(12, 2);
    bst.Insert(14, 12);
    bst.Insert(16, 13);
    bst.Insert(15, 15);
    bst.Insert(11, 15);
    bst.Insert(9, 15);
    bst.Insert(10, 5);
    bst.Insert(17, 6);

    bst.Find(12);
    bst.Find(123);

    bst.Write();

    cout << "------------" << endl;
    bst.Traver();
    bst.Delete(16);
    cout << "++++++++++++" << endl;
    bst.Traver();

    /*
    class BST<string, int> bst;
    bst.Insert("hello", 12);
    bst.Insert("zhangfei", 14);
    bst.Insert("liubei", 14);
    bst.Traver(); */

    return 0;
}
