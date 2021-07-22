#include <stdio.h>

struct checker {
   
    const char* name;
    checker(const char* name) : name(name) { printf("%s :ctor\n", name); }
    ~checker() { printf("%s : dtor\n", name); } 
};

thread_local checker t1("t1");

int main() {

	printf("test %s\n", t1.name);  
}
