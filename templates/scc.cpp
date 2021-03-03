// strongly connected components: kosaraju's algorithm 

// status: stress tested on https://judge.yosupo.jp/problem/scc
vector<pii> g[MAXN];
vector<int> scc[MAXN];

int vis[MAXN], vec[MAXN], sz;
void dfs(int u) {
	vis[u] = 1;
	for(auto [v, rev] : g[u]) 
		if(!rev && !vis[v]) 
			dfs(v);
	vec[sz++] = u;
}

void dfs2(int u, int c) {
	vis[u] = 1;
	scc[c].push_back(u);
	for(auto [v, rev] : g[u])
		if(rev && !vis[v])
			dfs2(v, c);
}

/*

   Sample usage:

void solve() {
	cin >> n >> m;
	for(int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		g[a].emplace_back(b, 0);
		g[b].emplace_back(a, 1);
	}
	for(int i = 0; i < n; i++) 
		if(!vis[i]) 
			dfs(i);
	
	memset(vis, 0, sizeof(vis));
	int cnt = 0;
	for(int i = n-1; ~i; --i)
		if(!vis[vec[i]])
			dfs2(vec[i], cnt++);
	
	cout << cnt << "\n";
	for(int i = 0; i < cnt; i++) {
		cout << scc[i].size();
		for(int u : scc[i])
			cout << " " << u;
		cout << "\n";
	}
}
*/
