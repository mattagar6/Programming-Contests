// Inspired from: http://e-maxx.ru/algo/assignment_hungary
// cost array, "a" and "matching" are 0 indexed
// matching -> what column is this row matched with, -1 if none
template<typename cost_t>
cost_t hungarian(vector<vector<cost_t>> a, vector<int>& matching) {
    const cost_t inf = numeric_limits<cost_t>::max() / 2;
    int n = a.size(), m = a[0].size();
    vector<cost_t> u(n+1), v(m+1);
    vector<int> p(m+1), way(m+1);
    for(int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<cost_t> minv(m+1, inf);
        vector<bool> used(m+1);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            cost_t delta = inf;
            for(int j = 1; j <= m; j++) {
                if(!used[j]) {
                    cost_t cur = a[i0-1][j-1] - u[i0] - v[j];
                    if(cur < minv[j]) {
                        minv[j] = cur, way[j] = j0;
                    }
                    if(minv[j] < delta) {
                        delta = minv[j], j1 = j;
                    }
                }
            }
            for(int j = 0; j <= m; j++) {
                if(used[j]) {
                    u[p[j]] += delta, v[j] -= delta;
                }
                else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while(p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while(j0 != 0);
    }
    matching.assign(n, -1);
    cost_t ans = -v[0];
    for(int j = 1; j <= m; j++) {
        matching[p[j]-1] = j-1;
    }

    return ans;
}

