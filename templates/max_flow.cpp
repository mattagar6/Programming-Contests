// Dinic's algoritm for maximum flow O(E*V^2)
// tested on: https://www.spoj.com/problems/FASTFLOW/

template<typename flow_t>
class Dinic {
public:

    Dinic(int _n, int _source, int _sink) : n(_n), source(_source), sink(_sink) {
        g.resize(n);
        flow.resize(n, vector<flow_t>(n));
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int from, int to, flow_t cap) {
        g[from].push_back(to);
        g[to].push_back(from);
        flow[from][to] += cap;
    }

    bool bfs() {
        vector<int> q{source};
        for(int i = 0; i < (int) q.size(); i++) {
            int u = q[i];
            for(int v : g[u]) {
                if(level[v] == -1 && flow[u][v] > 0) {
                    level[v] = level[u] + 1;
                    q.push_back(v);
                }
            }
        }
        
        return level[sink] != -1;
    }
    
    flow_t dfs(int u, flow_t pushed) {
        if(pushed == 0) {
            return 0;
        }
        if(u == sink) {
            return pushed;
        }
        for(int& pos = ptr[u]; pos < (int) g[u].size(); pos++) {
            int v = g[u][pos];
            if(level[v] != level[u] + 1 || flow[u][v] == 0) {
                continue;
            }
            flow_t maybe_push = dfs(v, min(pushed, flow[u][v]));
            if(maybe_push == 0) {
                continue;
            }
            flow[u][v] -= maybe_push;
            flow[v][u] += maybe_push;
            return maybe_push;
        }
        return 0;
    }

    flow_t max_flow() {
        flow_t mf(0);
        while(true) {
            level.assign(n, -1);
            level[source] = 0;
            if(!bfs()) {
                break;
            }
            ptr.assign(n, 0);
            flow_t now;
            do {
                now = dfs(source, FLOW_MAX);
                mf += now;
            } while(now != 0);
        }
        
        return mf;
    }
private:
    const flow_t FLOW_MAX = numeric_limits<flow_t>::max() / 2;
    vector<vector<int>> g;
    vector<vector<flow_t>> flow;
    vector<int> level, ptr;
    int n, source, sink;
};
