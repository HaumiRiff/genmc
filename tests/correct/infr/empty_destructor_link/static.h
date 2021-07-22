#include <stdio.h>



struct simple_checker {
simple_checker( ) { printf("\nsimple_check CONtructor\n"); };
~simple_checker();
};
	
struct checker {
checker( ) { printf("\ncheck CONtructor\n"); };
~checker();
};


checker::~checker() { printf("\ncheck DEStructor\n"); }
simple_checker::~simple_checker() { printf("\nsimple_check DEStructor\n"); }

checker lul() {
	static checker test;
	simple_checker temp;
	return test;
}

