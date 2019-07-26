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
	TAutoPtr<TObject> p = (TObject *)(new TInt(39));
	TAutoPtr<TObject> *q = &p;
	
	//可以在TVector中添加TAutoPtr<TObject> *类型变量，避免使用二维指针。
	

	std::vector <TObject *> v;
	
	TObject * int1 = (TObject *)new TInt(3);
	TObject * str1 = (TObject *)new TString("test\n");
	
	TObject * v1 = (TObject *)new TVector<int>;
	TObject * v2 = (TObject *)new TVector<float>;
	
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
	Tv.push_back(1);
	Tv.push_back(3);
	Tv.push_back(5);
	Tv.push_back(7);
	Tv.show();
	
	for (auto &i : Tv) {
		cout << i << " ";
	}
	cout << "\n";
	
	cout << *TFind(Tv.begin(), Tv.end(), 3);
	cout << "\n";

	TString Ts("你好abc");
	cout << Ts.GetStr() << "\n";
	cout << Ts.GetLen() << "\n";

/*
	//可能需要修改TString的operator =
	TVector<TString> Tv1;
	Tv1.push_back(TString("hello"));
	Tv1.push_back(TString("C++"));
	Tv1.show();		

	for (auto &iter: Tv1) {
		//下句导致程序段错误。
		//iter.show();
		//cout << iter.GetStr() << " ";
	}
*/
	TLog("info");

	
	return 0;
}