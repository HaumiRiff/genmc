
struct Av {
	virtual void hello(){}
};

struct Bv: Av{
	virtual void hello(){}
};


int main(){

	Bv* obj = new Bv();
	
	Av* b = obj;
	b->hello();
	
	return 0;
}
