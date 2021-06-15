#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

typedef long long ll;

// Kosaraju's algorithm for strongly connected components, O(V + E)
struct SCC {
  int n;
  vector<vector<int>> adj[2], scc;
  vector<int> order, used, comp, id;
  
  SCC(int _n) : n(_n) {
    adj[0].resize(n); 
    adj[1].resize(n); 
    used.resize(n); 
    comp.resize(n);
    id.resize(n, -1);
  }
  
  void add_edge(int u, int v) {
    adj[0][u].push_back(v);
    adj[1][v].push_back(u);
  }
  
  void dfs(int t, int v) {
    used[v] = 1;
    if (t == 1) comp.push_back(v);
    for (auto u : adj[t][v])
      if (!used[u])
        dfs(t, u);
    if (t == 0) order.push_back(v);
  }
  
  // Returns "id[v] = which SCC is v in"
  vector<int> go() {
    used.assign(n, 0);
    for (int v = 0; v < n; v++)
      if (!used[v])
        dfs(0, v);
    used.assign(n, 0);
    reverse(order.begin(), order.end());
    for (auto v : order) {
      if (used[v]) continue;
      comp.clear();
      dfs(1, v);
      for (auto u : comp)
        id[u] = scc.size();
      scc.push_back(comp);
    }
    return id;
  }
  
  // Make sure to call "go" first!!
  // Returns a new graph such that all SCCs are 
  // compressed into one node and only edges connecting
  // two components are in the new graph.
  // DAG is already in topological order, all edges in DAG (u, v) have u < v!
  vector<vector<int>> compress_dag() {
    int N = scc.size(); assert(N > 0); // call scc.go() first!
    vector<vector<int>> dag(N);
    used.assign(N, -1);
    for (int cc = 0; cc < N; cc++) 
      for (auto v : scc[cc]) 
        for (auto u : adj[0][v])
          if (id[u] != cc && used[id[u]] != cc)
            dag[cc].push_back(id[u]), used[id[u]] = cc;
    return dag;
  }
};

int main() {
	// your code goes here
	
	return 0;
}
