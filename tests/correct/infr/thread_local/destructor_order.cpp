#include <stdio.h>

int g_tab = 1;
class checker {
    int tab;
    public:
    const char* name;
    checker(const char* name) : name(name), tab(g_tab++) {
    	printf("\n%d	%s :ctor\n", tab, name);
    }
    ~checker() { printf("\n%d	%s : dtor\n", tab, name); } 
};

checker g1("global1");
thread_local checker t1("thread_local1");
thread_local checker t2("thread_local2");
checker g2("global2");

int main() {
  printf("\nstart!\n");
    static checker s1("static1");
    printf("test %s\n", t1.name);
    static checker s2("static2");
  printf("\nfinish\n");
}
