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

	vector<class Desk> dv;

	d.desk();
	m.desk();

	dv.push_back(d);
	dv.push_back(m);

	for (unsigned int i=0; i < dv.size(); ++i) {
		cout << "This is my first cpp " << dv[i].GetLen() << endl;
	}

	return 0;
}
