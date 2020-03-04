

template<typename flow_t>
struct MaxFlow {
	
	const flow_t FLOW_INF = numeric_limits<flow_t>::max() / 2;
	vector<vector<int>> g;
	vector<vector<flow_t>> flow;
	int n, source, sink;

	MaxFlow(int _n, int _source, int _sink) : n(_n), source(_source), sink(_sink) {
		g.resize(n);
		flow.resize(n, vector<flow_t>(n));
	}

	void add_edge(int from, int to, flow_t cap) {
		g[from].push_back(to);
		g[to].push_back(from);
		flow[from][to] += cap;
	}

	flow_t get_flow() {
		flow_t mf = 0;

		vector<int> par(n), q;

		while(true) {
			par.assign(n, -1);
			q.clear();
			q.push_back(source);

			for(int i = 0; i < (int) q.size(); i++) {
				int u = q[i];
				if(u == sink) break;
				for(int v : g[u]) {
					if(par[v] == -1 && flow[u][v] > 0) {
						par[v] = u;
						q.push_back(v);
					}
				}
			}

			if(par[sink] == -1) break;
			flow_t f = FLOW_MAX;
			int cur = sink;
			while(cur != source) {
				f = min(f, flow[par[cur]][cur]);
				cur = par[cur];
			}

			mf += f;
			cur = sink;
			while(cur != source) {
				flow[par[cur]][cur] -= f;
				flow[cur][par[cur]] += f;
				cur = par[cur];
			}
		}

		return mf;
	}
};
