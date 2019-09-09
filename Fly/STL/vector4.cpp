/*
 * http://en.cppreference.com/w/cpp/container/vector/erase
 */

#include <vector>
#include <iostream>


int main( )
{
    std::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';

	//删除第一个元素，将后面所有的元素往前移动一位。
    c.erase(c.begin());

    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';

    c.erase(c.begin()+2, c.begin()+5);

    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
	
	// 在Heap内存里用vector
	std::vector<float> *v = new std::vector<float>;
	v->push_back(2.4);
	v->push_back(4.5);
	for (auto &i : *v) {
        std::cout << i << " ";
    }
    std::cout << '\n';
	delete v;
}