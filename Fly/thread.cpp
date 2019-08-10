#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>


//std::atomic_long total(0);
//std::atomic<long> total(0);
long total = 0;


void thread_task() 
{
	for (int i = 0; i < 100; i++) {
		total +=1;
		sleep(0.3);
	}
}

int main()
{
	std::thread t[100];

	for (int i = 0 ; i < 100; i++) {
		t[i] = std::thread(thread_task);
	}

	for (int j = 0; j < 100; j++) {
		t[j].join();
	}
	std::cout << "total:" << total <<'\n';

	return 0;
}
