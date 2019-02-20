/*
 * http://en.cppreference.com/w/cpp/utility/bitset/set
 */

#include <iostream>
#include <bitset>

int main()
{
    std::bitset<8> b;
    std::cout << b << '\n';
    std::cout<< b.size() << '\n';

    for (size_t i = 1; i < b.size(); i += 2) {
        b.set(i);
    }
    std::cout << b << '\n';

    b[1] = 0;
    b[3] = 0;
    std::cout << b << '\n';
}
