#include <iostream>
#include <vector>
using namespace std;

struct My {
    void * p;
    char type[8];
};


int main()
{
  int a = 12;
  float b =34.5;
  
  struct My m, n;
  
  m.p = &a;
  strcpy(m.type, "int");
  
  n.p = &b;
  strcpy(n.type, "float");
  
	vector<struct My*> coll; 

	coll.push_back(&m);
  coll.push_back(&n);

  for (auto &i : coll) {
    if (strcmp(i->type, "int") == 0) {
      cout << *(int *)i->p << '\n';
    }
    if (strcmp(i->type, "float") == 0) {
      cout << *(float *)i->p << '\n';
    }
	}
 
 	vector<struct My*> l;

  struct My c;
  c.p = &coll;
  strcpy(c.type, "vector");

  //向l中插入一个c和m
  l.push_back(&c);
  l.push_back(&m);
  for (auto &i : l) {
    if (strcmp(i->type, "vector") == 0 ){
        for (auto &i : coll) {
          if (strcmp(i->type, "int") == 0) {
            cout << *(int *)i->p << '\n';
          }
          if (strcmp(i->type, "float") == 0) {
            cout << *(float *)i->p << '\n';
          }
      }
    }
    if (strcmp(i->type, "int") == 0) {
      cout << *(int *)i->p << '\n';
    }
  }
	cout << endl;
}