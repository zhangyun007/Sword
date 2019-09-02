﻿#include <list>
#include <iostream>
 
int main()
{
    std::list<int> l = { 1,100,2,3,10,1,11,-1,12 };

    // List和forward_list用remove删除特定值，vector和deque没有删除特定值的成员函数；
    // set,mutiset,map,mutimap用erase删除特定key.
    
    l.remove(1); // remove both elements equal to 1
    l.remove_if([](int n){ return n > 10; }); // remove all elements greater than 10
 
    for (int n : l) {
        std::cout << n << ' '; 
    }
    std::cout << '\n';
}