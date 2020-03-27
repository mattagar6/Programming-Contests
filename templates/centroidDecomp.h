struct CentroidDecomp {
	vector<int> par, sz;
	vector<bool> removed;
	
	CentroidDecomp(int _n) {
		par.resize(_n, -1);
		sz.resize(_n);
		removed.resize(_n);
		ans.resize(_n, inf);
	}
	
	int get_sz(int u, int p = -1) {
		sz[u] = 1;
		for(int v : g[u]) {
			if(v != p && !removed[v]) {
				sz[u] += get_sz(v, u);
			}
		}
		
		return sz[u];
	}
	
	int get_centroid(int u, int n, int p = -1) {
		for(int v : g[u]) {
			if(v != p && !removed[v] && sz[v] > n/2) {
				return get_centroid(v, n, u);
			}
		}
		return u;
	}
	
	void build(int root, int p = -1) {
		int n = get_sz(root);
		int centroid = get_centroid(root, n);
		par[centroid] = p;
		removed[centroid] = true;
		for(int v : g[centroid]) {
			if(v != p && !removed[v]) {
				build(v, centroid);
			}
		}
	}
	

};
