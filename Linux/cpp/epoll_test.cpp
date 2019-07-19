#include <iostream>
#include <sys/epoll.h>

using namespace std;

int main()
{
	cout << hex << EPOLLWAKEUP << ' ' 
	    	<< hex <<EPOLLONESHOT << ' '
		<< hex << EPOLLET << '\n';
	return 0;
}
