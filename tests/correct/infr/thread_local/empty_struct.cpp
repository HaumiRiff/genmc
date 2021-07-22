#include <stdio.h>

struct checker {
    checker()  { printf(":ctor\n"); }
    ~checker() { printf(": dtor\n"); } 
};

thread_local checker t1;

int main() {

	printf("test \n");  
}
