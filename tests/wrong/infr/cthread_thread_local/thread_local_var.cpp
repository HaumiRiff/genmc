#include <stdio.h>
#include <stdlib.h> 	
#include <threads.h>


int g_tab = 1;
class checker {
    int tab;
    public:
    const char* name;
    checker(const char* name) : name(name), tab(g_tab++) {
    }
    ~checker() {} 
};

mtx_t mutex;
int x;
thread_local checker t1("thread_local1");

static void thread_1(void *unused)
{
	int r;

	mtx_lock(&mutex);
	printf("%s\n", t1.name);
	t1.name  = "thread_1";
	mtx_unlock(&mutex);
	return;
}

static void thread_2(void *unused)
{
	int r;

	mtx_lock(&mutex);
	printf("%s\n", t1.name);
	t1.name  = "thread_2";
	mtx_unlock(&mutex);
	return;
}


int main() {
  
  thrd_t th1, th2;
  
  int res = thrd_create(&th1, (thrd_start_t)&thread_1, NULL);
  res = thrd_create(&th1, (thrd_start_t)&thread_2, NULL);
}
