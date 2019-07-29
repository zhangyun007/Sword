#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	vector<string> v;
	string tmp;

	while (getline(cin, tmp))
		v.push_back(tmp);

	sort(v.begin(), v.end(), greater<string>());
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));
}