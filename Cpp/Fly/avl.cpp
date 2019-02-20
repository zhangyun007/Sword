#include <iostream>

using namespace std;

template <class T, class U>
struct Node {
    T   key;
    U   value;
    struct Node * left;
    struct Node * right;
    int height;
};

template <class T, class U>
struct  DNode{
    T   key;
    U   value;
    int left;
    int right;
    int height;
};

template <class T, class U>
class AVL {
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
        void RotateWithLeftChild(class Node<T, U> * &k2);
        void RotateWithRightChild(class Node<T, U> * &k2);
        void DoubleWithLeftChild(class Node<T, U> * &k);
        void DoubleWithRightChild(class Node<T, U> * &k);
    public:
        AVL():root(NULL){}
        ~AVL();
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
AVL<T, U>::~AVL()
{
    //看这里！！！！！！！ 这是同名覆盖原则, 使用域标志:: 。这种写法在MFC中尤其常见。
    //例如在mfc中调用库中没有封装的api就会这么写 ::SendMessage(...);
    ::DeleteNode(root);
}

template <class T, class U>
void AVL<T, U>::RotateWithLeftChild(class Node<T, U> *&k2)
{
     class Node<T, U> *k1 = k2->left;
     k2->left = k1->right;
     k1->right = k2;
     k2->height = max(height(k2->left), height(k2->right)) + 1;
     k1->height = max(height(k1->left), height(k2)) + 1;
     k2 = k1;
}

template <class T, class U>
void AVL<T, U>::RotateWithRightChild(class Node<T, U> *&k2)
{
    class Node<T, U> *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), height(k2)) + 1;
    k2 = k1;
}

template <class T, class U>
void AVL<T, U>::DoubleWithLeftChild(class Node<T, U> *&k)
{
    RotateWithRightChild(k->left);
    RotateWithLeftChild(k);
}

template <class T, class U>
void AVL<T, U>::DoubleWithRightChild(class Node<T, U> *&k)
{
    RotateWithLeftChild(k->right);
    RotateWithRightChild(k);
}

template <class T, class U>
int height(class Node<T, U> *node)
{
    return (node == NULL)?0:node->height;
}

template <class T, class U>
void AVL<T, U>::InsertNode(class Node<T, U> *&node, T t, U u)
{
    if (node == NULL) {
        //父节点指向新建子节点
        node = new Node<T, U>();
        node->key = t;
        node->value = u;
        node->height = 1;
        cout << "New Node: key is " << t << " value is " << u << '\n';
        return;
    }
    if (node->key == t) {
        cout << t << " == " << node->key << '\n';
        node->value = u;
        cout << "key " << t << " modified to " << u << '\n';
    } else if (node->key > t) {
        cout << t << " < " << node->key << '\n';
        InsertNode(node->left, t, u);
        //左子树更深
        if (height(node->left) - height(node->right) == 2) {
           if (t < node->left->key) {
               RotateWithLeftChild(node);
           } else {
               DoubleWithLeftChild(node);
           }
        }
    } else if (node->key < t) {
        cout << t << " > " << node->key << '\n';
        InsertNode(node->right, t, u);
        //右子树更深
        if (height(node->right) - height(node->left) == 2) {
           if (t > node->right->key) {
               RotateWithRightChild(node);
           } else {
               DoubleWithRightChild(node);
           }
        }
    }
    node->height = max(height(node->left), height(node->right)) + 1;
}

template <class T, class U>
void AVL<T, U>::Insert(T t, U u) {
    InsertNode(root, t, u);
}

template <class T, class U>
class Node<T, U> * AVL<T, U>::FindKey(class Node<T, U> *node, T t)
{
    if (node == NULL) {
        return NULL;
    } else {
        if (t < node->key) {
            cout << t << " < " << node->key <<'\n';
            FindKey(node->left, t);
        } else if (t > node->key) {
            cout << t << " > " << node->key <<'\n';
            FindKey(node->right, t);
        } else if (t == node->key) {
            cout << t << " == " << node->key <<'\n';
            cout << node << '\n';
            return node;
        }
        return NULL;
    }
}

template <class T, class U>
void AVL<T, U>::Find(T t)
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
int AVL<T, U>::TraverTree(class Node<T, U> *node)
{
    if (node == NULL) {
        return 0;
    }
    int m = TraverTree(node->left);
    cout << "key is " << node->key << " value is " << node->value << " height " << node->height << '\n';
    int n = TraverTree(node->right);
    return m + n + 1;
}

template <class T, class U>
int AVL<T, U>::Traver()
{
    return TraverTree(root);
}

template <class T, class U>
void AVL<T, U>::DeleteNode(class Node<T, U> *&node, T t)
{
    if (node == NULL) {
        return;
    }

    if (node->key > t) {
        DeleteNode(node->left, t);
        if (height(node->right) - height(node->left) == 2) {
            if (node->right->left != NULL && node->right->right != NULL) {
                DoubleWithRightChild(node);
            } else {
                if (node->right->left != NULL) {
                    DoubleWithRightChild(node);
                }
                if (node->right->right != NULL) {
                    RotateWithRightChild(node);
                }
            }
        }
    } else if (node->key < t ) {
        DeleteNode(node->right, t);
        if (height(node->left) - height(node->right) == 2) {
            if (node->left->left != NULL && node->left->right != NULL) {
                DoubleWithLeftChild(node);
            } else {
                if (node->left->left != NULL) {
                    RotateWithLeftChild(node);
                }
                if (node->left->right != NULL) {
                    DoubleWithLeftChild(node);
                }
            }
        }
    } else if (node->key == t) {
        if (node->left && node->right) {
            class Node<T, U> * temp = node->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            node->key = temp->key;
            node->value = temp->value;
            DeleteNode(node->right, temp->key);
            if (height(node->left) - height(node->right) == 2) {
                if (node->left->left != NULL && node->left->right != NULL) {
                    DoubleWithLeftChild(node);
                } else {
                    if (node->left->left != NULL) {
                        RotateWithLeftChild(node);
                    }
                    if (node->left->right != NULL) {
                        DoubleWithLeftChild(node);
                    }
                }
            }
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
void AVL<T, U>::Delete(T t)
{
    DeleteNode(root, t);
}

/*
 * 返回值表示右子树有n个节点
 */
template <class T, class U>
int AVL<T, U>::WriteNode(class Node<T, U> *node)
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
void AVL<T, U>::Write()
{
    WriteNode(root);
}

int main(int argc, char *argv[])
{

    class AVL<int, int> avl;

    avl.Insert(20, 21);
    avl.Insert(13, 32);
    avl.Insert(16, 12);
    avl.Insert(12, 2);
    avl.Insert(14, 12);
    avl.Insert(16, 13);
    avl.Insert(15, 15);
    avl.Insert(11, 15);
    avl.Insert(9, 15);
    avl.Insert(10, 5);
    avl.Insert(17, 6);
    avl.Insert(21, 9);

    avl.Find(12);
    avl.Find(123);

    //avl.Write();

    avl.Traver();
    avl.Delete(15);
    cout << "Hello World!" << endl;
    avl.Traver();
    avl.Delete(13);
    cout<< " ------- \n";
    avl.Traver();
    avl.Delete(11);
    cout<< " ------- \n";
    avl.Traver();

    /*
    class AVL<string, int> AVL;
    AVL.Insert("hello", 12);
    AVL.Insert("zhangfei", 14);
    AVL.Insert("liubei", 14);
    AVL.Traver(); */

    return 0;
}
