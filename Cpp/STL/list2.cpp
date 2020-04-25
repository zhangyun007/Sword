#include <iostream>
#include <list>

using namespace std;

int main()
{
	// list container for character elements
	list<char> coll;      

	// append elements from 'a' to 'z'
	for (char c='a'; c<='z'; ++c) {
		coll.push_back(c);
	}

	list<char>::const_iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos) {
		cout << *pos << ' ';
	}
	cout << "\n";
	
	//用正向迭代器倒序输出。
	for (pos = --coll.end(); pos != --coll.begin(); --pos) {
		cout << *pos << ' ';
	}
	cout << endl;
}
