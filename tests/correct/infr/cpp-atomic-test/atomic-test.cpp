#include <thread>
#include <atomic>

std::atomic<int> param(2);

void plusOne()
{
	param += 1;
}
void zero()
{
	param = 0;
}


int main(){
	
	std::thread t1(plusOne);
	std::thread t2(zero);
	t1.join();
	t2.join();
	return 0;
}
