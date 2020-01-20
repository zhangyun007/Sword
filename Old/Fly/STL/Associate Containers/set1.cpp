#include <iostream>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
    set<int, greater<int>> s;
    set<int>::iterator it;
    s.insert(4);
    s.insert(12);
    s.insert(2);
    s.insert(34);
    s.insert(5);
    s.insert(7);
    s.insert(16);
    s.insert(4);

    for (it = s.begin(); it != s.end(); ++it;) {
        if (*it == 16) {
        	// erase返回的迭代器指向被删除节点的下一个节点
            s.erase(it);
        }
    }

    for (auto i:s) {
        cout << i << ' ';
    }

    return 0;
}