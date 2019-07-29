#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
bool big(T &a, T &b) {
	return (a < b);
}

int main(int argc, char *argv[])
{
    int a[20] = {1, 23, 12, 23, 43, 4, 45, 52, 12, 123, 2, 23, 123, 123, 23, 1, 23, 56, 14, 67};
    int b[20];

    //reverse_copy(a, a+ 20, ostream_iterator<int>(cout, " "));

    reverse_copy(a, a+ 20, b);

    for (int i = 0; i < 20; i++)
        cout << b[i]<< ' ';

    cout << '\n';

	//直接传入函数作为排序规则
    sort(a, a + 20, big<int>);
	//sort(a, a + 20, greater<int>());
	
    for (int i = 0; i < 20; i++)
        cout << a[i]<< ' ' ;

    cout << '\n';

    return 0;
}