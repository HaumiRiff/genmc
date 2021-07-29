struct Plain {
	int i1;
	double d;
	char c;
	int i2;
};

Plain g = {-12, -0.543, 'g', 123};
static Plain g_st = {0, 2.123, 'f', 5};

int main() {
	g.i1 += 1;
	g_st.c = 'h';
	
	//FIXME Fine with g and g_st but fails for p - Error detected: Attempt to access non-allocated memory!
	Plain p = {1, 1.54, 'a', 0};	
	
	return 0;
}
