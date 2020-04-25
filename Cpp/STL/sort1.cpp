#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	vector<string> v = {"sort", "test", "command", "java"};
	
	string tmp;
	
	//ctrl + Z结束输入
	while (getline(cin, tmp)) {
		v.push_back(tmp);
	}

/*
	greater<string> test;
	sort(v.begin(), v.end(), test);
*/

	//这里，greater<string>()是一个对象，()是构造函数。
	sort(v.begin(), v.end(), greater<string>());
	
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));
	
	auto p = find(v.begin(), v.end(), "test");
	cout << *p << "\n";
}