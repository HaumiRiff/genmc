#include <thread>

void func () {}

int main() {
	std::thread t (func);
	t.join();
return 0;
}
