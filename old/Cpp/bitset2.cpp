#include <iostream>
#include <bitset>
 
int main()
{
    std::bitset<4> b1("0000");
    std::bitset<4> b2("0101");
    std::bitset<4> b3("1111");
 
    std::cout << "bitset\t" << "all\t" << "any\t" << "none\n";
    std::cout << b1 << '\t' << b1.all() << '\t' << b1.any() << '\t' << b1.none() << '\n';
    std::cout << b2 << '\t' << b2.all() << '\t' << b2.any() << '\t' << b2.none() << '\n';
    std::cout << b3 << '\t' << b3.all() << '\t' << b3.any() << '\t' << b3.none() << '\n';
}