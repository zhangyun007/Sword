#include <iostream>
#include <vector>

using namespace std;

#define BLUE 0
#define RED 1

class Desk {
private:
	int len;
	int width;
public:
	void desk() {
		len = 10;
		width = 11;
	};
	int GetLen() {
		return len;
	}
};

class MyDesk : public Desk {
private:
	int color;
public:
	void desk() {
		Desk::desk();
		color = BLUE;
	};
};

int main()
{
	class Desk d;
	class MyDesk m;

	//容器里存放对象指针比存放对象更好，对象可能很大，指针只占四个字节。
	vector<class Desk *> dv;

	d.desk();
	m.desk();

	dv.push_back(&d);
	dv.push_back(&m);

	for (unsigned int i=0; i < dv.size(); ++i) {
		cout << "This is my first cpp " << dv[i]->GetLen() << endl;
	}

	return 0;
}
