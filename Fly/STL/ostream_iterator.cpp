#include <iostream>     
#include <iterator>     
#include <vector>       
#include <algorithm>    

int main () {
  std::vector<int> myvector;
  for (int i = 1; i < 10; ++i)
	  myvector.push_back(i*10);

  // ostream_iterator是STL预定义的输出迭代器
  std::ostream_iterator<int> out_it(std::cout,", ");
  std::copy (myvector.begin(), myvector.end(), out_it);
  return 0;
}