struct ST {
	int l, r, m;
	ST *left, *right;
   
	ST(const vector<int>& a, int L, int R) : l(L), r(R), m((L+R)/2) {
		if(L == R) {
			
		}
		else {
			left = new ST(a, L, m);
			right = new ST(a, m+1, R);
			
		}
	}
	
	~ST() {
		if(l != r) {
			delete left;
			delete right;
		}
	}
	
	
};
