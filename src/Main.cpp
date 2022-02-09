#include <iostream>
#include <thread>
#include "SafeQueue.h"

// https://medium.com/swlh/c-mutex-write-your-first-concurrent-code-69ac8b332288

int main()
{
	SafeQueue<int> sque;

	std::thread tA(&SafeQueue<int>::push, std::ref(sque), 1);
	std::thread tB(&SafeQueue<int>::push, std::ref(sque), 2);
	std::thread tC(&SafeQueue<int>::push, std::ref(sque), 3);
	std::thread tD(&SafeQueue<int>::push, std::ref(sque), 4);
	std::thread tE(&SafeQueue<int>::push, std::ref(sque), 5);
	std::thread tF(&SafeQueue<int>::push, std::ref(sque), 6);
	tA.join();
	tB.join();
	tC.join();
	tD.join();
	tE.join();
	tF.join();

//	std::cout << "q: " << sque << std::endl;

	std::thread tAx(&SafeQueue<int>::pop, std::ref(sque));
	std::thread tBx(&SafeQueue<int>::pop, std::ref(sque));
	std::thread tCx(&SafeQueue<int>::pop, std::ref(sque));
	std::thread tDx(&SafeQueue<int>::pop, std::ref(sque));
	std::thread tEx(&SafeQueue<int>::pop, std::ref(sque));
	std::thread tFx(&SafeQueue<int>::pop, std::ref(sque));
	tAx.join();
	tBx.join();
	tCx.join();
	tDx.join();
	tEx.join();
	tFx.join();

	std::cout << "Done." << std::endl;
	return 0;
}
