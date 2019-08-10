// ostream_iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy

int main () {
  std::vector<int> myvector;
  for (int i = 1; i < 10; ++i)
	  myvector.push_back(i*10);

  // ostream_iterator是STL预定义的输出迭代器
  std::ostream_iterator<int> out_it (std::cout,", ");
  std::copy (myvector.begin(), myvector.end(), out_it);
  return 0;
}