template<typename flow_t, typename cost_t>
class MinCostFlow {
public:

	MinCostFlow(int _n, int _source, int _sink) : n(_n), source(_source), sink(_sink) {
		g.resize(n);
		cost.resize(n, vector<cost_t>(n));
		cap.resize(n, vector<flow_t>(n));
	}

	void add_edge(int from, int to, cost_t weight, flow_t c) {
		g[from].push_back(to);
		g[to].push_back(from);
		cost[to][from] = -weight;
		cost[from][to] = weight;
		cap[from][to] = c;
	}

	struct State {
		cost_t dist;
		int node;
		bool operator < (const State& rhs) const {
			return dist > rhs.dist;
		}
	};

	void shortest_paths(vector<cost_t>& dist, vector<int>& par) {
		dist.assign(n, COST_INF);
		par.assign(n, -1);
		dist[source] = 0;
		priority_queue<State> pq;
		pq.push({0LL, source});
		while(!pq.empty()) {
			State u = pq.top(); pq.pop();
			if(u.dist > dist[u.node]) continue;

			for(int v : g[u.node]) {
				if(dist[v] > u.dist + cost[u.node][v] && cap[u.node][v] > 0) {
					dist[v] = u.dist + cost[u.node][v];
					par[v] = u.node;
					pq.push({dist[v], v});
				}
			}
		}
	}

	cost_t min_cost_flow() {
		flow_t mf = 0;
		cost_t total_cost = 0;
		vector<cost_t> dist(n);
		vector<int> par(n);
		while(true) {
			shortest_paths(dist, par);
			if(dist[sink] == COST_INF) {
				break;
			}
			
			// augment path
			flow_t f = FLOW_INF;
			int cur = sink;
			while(cur != source) {
				f = min(f, cap[par[cur]][cur]);
				cur = par[cur];
			}

			mf += f;
			total_cost += dist[sink];

			// update flows
			cur = sink;
			while(cur != source) {
				cap[par[cur]][cur] -= f;
				cap[cur][par[cur]] += f;
				cur = par[cur];
			}
		}

		return total_cost;
	}	
private:
	const flow_t FLOW_INF = numeric_limits<flow_t>::max() / 2;
	const cost_t COST_INF = numeric_limits<cost_t>::max() / 2;

	vector<vector<int>> g;
	vector<vector<flow_t>> cap;
	vector<vector<cost_t>> cost;
	int n, source, sink;
};
