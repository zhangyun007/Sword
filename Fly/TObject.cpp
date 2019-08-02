#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>

#include "TObject.hpp"

using namespace std;

//该文件的主要作用是测试TObject.hpp中的各种类被正确的实现了

int main()
{
	//中文占两个字符
	TString Ts("你好abc");
	cout << Ts.GetStr() << "\n";
	cout << Ts.GetLen() << "\n";
	
	
	AutoPtr<TObject> p = (TObject *)(new TInt(39));
	AutoPtr<TObject> *q = &p;	
	//可以在TVector中添加TAutoPtr<TObject> *类型变量，避免使用二维指针。


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

	
	//使用TObject *可以让vector和map实现Python中列表和字典的功能
	
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


	TList<int> list1;
	list1.insert(list1.begin(), 1);
	list1.insert(list1.begin(), 4);
	list1.insert(list1.begin(), 6);
	list1.show();
	cout << *TFind(list1.begin(), list1.end(), 4);
	cout << "\n";
	
	TLog("info");

	//可能需要修改TString的operator =
	TVector<TString> Tv1;
	//Tv1.push_back(TString("hello"));
	//Tv1.push_back(TString("C++"));
	Tv1.show();		

	for (auto &iter: Tv1) {
		//下句导致程序段错误。
		//iter.show();
		//cout << iter.GetStr() << " ";
	}


	/*
	class TBSTMap<int, float> bst;

    bst.Insert(20, 21.1);
    bst.Insert(13, 32.1);
    bst.Insert(16, 12.1);
    bst.Insert(12, 2.1);
    bst.Insert(14, 12.1);
    bst.Insert(16, 13.1);
    bst.Insert(15, 15.1);
    bst.Insert(11, 15.1);
    bst.Insert(9, 15.1);
    bst.Insert(10, 5.1);
	bst.Insert(17, 6.1);

    cout << bst.Find(12);
    cout << bst.Find(123);

    bst.Write();

    cout << "------------" << endl;
    bst.Traver();
    bst.Delete(16);
    cout << "++++++++++++" << endl;
    bst.Traver();
*/
  
  /*
    class TBSTMap<string, int> bst;
    bst.Insert("hello", 12);
    bst.Insert("zhangfei", 14);
    bst.Insert("liubei", 14);
    bst.Traver(); 
	*/

	
	return 0;
}