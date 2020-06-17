// strongly connected components: (tarjan's algorithm, O(n + m))
// able to find sccs, and compress them into a dag

// status: stress tested on https://judge.yosupo.jp/problem/scc
namespace SCC {
   const int mxN = 500*1000+5;
   vector<int> g[mxN], scc[mxN], stk;
   int component[mxN], low[mxN], num[mxN], visited[mxN], n, scc_count = 0;

   void read() {
      
   }

   void tarjan(int u) {
      static int T = 0;
      low[u] = num[u] = T++;
      stk.push_back(u);
      visited[u] = 1;
      for(int v : g[u]) {
         if(num[v] == -1) {
            tarjan(v);
         }
         if(visited[v]) {
            low[u] = min(low[u], low[v]);
         }
      }
      if(low[u] == num[u]) {
         vector<int> comp;
         while(1) {
            int v = stk.back();
            stk.pop_back();
            visited[v] = 0;
            comp.push_back(v);
            component[v] = scc_count;
            if(v == u) {
               break;
            }
         }
         scc[scc_count++].swap(comp);
      }
   }
   
   // run tarjan's scc
   // scc[i] = all nodes in the same scc
   // component[i] = which scc is node i in
   void decompose() {
      memset(num, -1, sizeof num);
      for(int i = 0; i < n; i++) {
         if(num[i] == -1) {
            tarjan(i);
         }
      }
   }
   
   // contracts sccs and returns the resulting dag as an adjacency list
   // MUST call SCC::decompose() to build sccs first
   vector<vector<int>> make_dag() {
      assert(scc_count > 0);
      vector<vector<int>> adj(scc_count);
      for(int i = 0; i < n; i++) {
         for(int v : g[i]) {
            if(component[v] != component[i]) {
               adj[component[i]].push_back(component[v]);
            }
         }
      }
      for(int i = 0; i < scc_count; i++) {
         sort(adj[i].begin(), adj[i].end());
         adj[i].resize(unique(adj[i].begin(), adj[i].end())-adj[i].begin());
      }
      return adj;
   }
}
