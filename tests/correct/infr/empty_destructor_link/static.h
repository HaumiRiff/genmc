struct checker {
~checker();
};

checker::~checker() {
//blablabla still empty
}

checker lul() {
	static checker test;
	return test;
}

