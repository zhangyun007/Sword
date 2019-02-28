#include <iostream>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    map<int, string> m;
    m[9] = "zhangfei";
    m[10] = "liubei";
    m.insert(make_pair(12, "guanyu"));
    m.insert(make_pair(11, "zhaoyun"));

    map<int, string>::iterator it;

    it = m.find(10);
    if (it != m.end()) {
        cout << it->second << '\n';
        m.erase(it);
    } else {
        cout << "No key 10.";
    }

    for (it = m.begin(); it != m.end(); it++) {
        cout << it->first << ' ' << it->second << '\n';
    }

    cout << m[11] << '\n';


    map <string, int> n;
    n.insert(make_pair("test", 9));
    n["zhangfei"] = 11;
    n["liubei"] = 10;

    map<string, int>::iterator it2;

    it2 = n.find("zhangfei");
    if (it2 != n.end()) {
        cout << it2->second << '\n';
        n.erase(it2);
    } else {
        cout << "No key zhangfei.";
    }

    for (it2 = n.begin(); it2 != n.end(); it2++) {
        cout << it2->first << ' ' << it2->second << '\n';
    }

    cout << n["test"] << '\n' ;


    return 0;
}