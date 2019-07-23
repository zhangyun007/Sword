
#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>

#include "TObject.hpp"

using namespace std;

class Test {
public:
	int i;
	char ch;
};

int main()
{
	std::vector<TObject *> v;
	
	class TObject * int1 = (TObject *)new TInt(3);
	class TObject * str1 = (TObject *)new TString("test\n");
	
	class TObject * v1 = (TObject *)new TVector<int>;
	class TObject * v2 = (TObject *)new TVector<float>;
	
	v.push_back(int1);
	v.push_back(str1);
	
	v.push_back(v1);
	v.push_back(v2);
	
	for (auto &iter: v) {
		iter->show();
	}
	
	std::unordered_map<TObject *, TObject *> m;
	m[int1] = int1;
	m[str1] = str1;
	m[v1] = v2;
	m[v2] = v1;

	delete int1;
	delete str1;
	
	delete v1;
	delete v2;
	
	TVector<int> Tv;
	Tv.show();
	Tv.push_back(1);
	Tv.show();
	Tv.push_back(3);
	Tv.show();
	Tv.push_back(5);
	Tv.show();
	Tv.push_back(7);
	Tv.show();
	
	for (auto &i : Tv) {
		cout << i << " ";
	}
	cout << "\n";

	TVector<Test> Tt;
	class Test t;
	t.i = 1; t.ch = 'a';
	Tt.push_back(t);
	t.i = 2; t.ch = 'b';
	Tt.push_back(t);
	t.i = 3; t.ch = 'c';
	Tt.push_back(t);
	
	Tt.show();	
	
	TString Ts("C++ is good!\n");
	cout << Ts.GetStr();
	
	TLog log;
	log.Write_Log("This is debug!\n");
	
	return 0;
}