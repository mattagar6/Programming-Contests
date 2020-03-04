class SegTree {
public:
	struct Node {
		
		void merge(Node a, Node b) {
			
		};
	};
	
	SegTree(int n_) {
		n = n_;
		tree.resize(4*n);
		lazy.resize(4*n);
	}
	
	void build(int i, int L, int R) {
		if(L == R) {
			
		} else {
			int mid = L + (R - L)/2;
			build(2*i, L, mid);
			build(2*i+1, mid+1, R);
			tree[i].merge(tree[2*i], tree[2*i+1]);
		}
		
	}
	
	void push(int i) {
		
	}
	
	Node get(int i, int L, int R, int tl, int tr) {
		if(tl > tr) return Node();
		if(L == tl && tr == R) {
			return tree[i];
		} else {
			push(i);
			int mid = L + (R-L)/2;
			Node ans;
			ans.merge(get(2*i, L, mid, tl, min(tr, mid)), get(2*i+1, mid+1, R, max(tl, mid+1), tr));
			return ans;
		}
	}
	
	void upd(int i, int L, int R, int tl, int tr, int val) {
		if(tl > tr) return;
		if(L == tl && tr == R) {
			
		} else {
			push(i);
			int mid = L + (R-L)/2;
			upd(2*i, L, mid, tl, min(tr, mid), val);
			upd(2*i+1, mid+1, R, max(tl, mid+1), tr, val);
			tree[i].merge(tree[2*i], tree[2*i+1]);
		}
	}
	
	int get(int tl, int tr) { 
		Node ans = get(1, 1, n, tl, tr); 
		
	}
	
	void upd(int tl, int tr, int val) { upd(1, 1, n, tl, tr, val); }
private:
	int n;
	vector<Node> tree;
	vector<int> lazy;
};