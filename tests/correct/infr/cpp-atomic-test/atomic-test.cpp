#include <thread>
#include <atomic>
#include <stdio.h>

static std::atomic<int> param(2);

void plusOne()
{
	printf("\nplusOne*\n");
	param += 1;
}
void zero()
{
	printf("\nzero*\n");
	param = 0;
}


int main(){
	printf("\nprogram_start*\n");
	std::thread t1(plusOne);
	std::thread t2(zero);
	printf("\nstd::threads done*\n");
	t1.join();
	t2.join();
	return 0;
}
