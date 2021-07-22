#include <stdio.h>
#include <thread>

thread_local int s = 0;

void addThreadLocal(int s1){

  s += s1;
  printf("*** %d", s);

}

int main(){

  std::thread t1(addThreadLocal, 1); 
  std::thread t2(addThreadLocal, 2); 
  std::thread t3(addThreadLocal, 3); 
  std::thread t4(addThreadLocal, 4); 

  t1.join();
  t2.join();
  t3.join();
  t4.join();

}
