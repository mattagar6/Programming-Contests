#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define nav(...) "[ " << #__VA_ARGS__ ": " << (__VA_ARGS__) << " ] "
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;
template<class T> struct rge { T b, e; };
template<class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
struct debug {
	~debug() {cout<<endl;}
	template<class T> debug& operator<<(T x) {cout<<boolalpha<<x; return *this;}
	template<class B, class C> debug& operator<< (pair<B, C> x){return *this<<"("<<x.first<<", "<<x.second<<")";}
	template<class T> debug& operator<<(rge<T> x) {
		*this<<"[";for(auto it=x.b;it!=x.e;it++){*this<<", "+2*(it==x.b)<<*it;}return *this<<"]";}
	template<class T> debug& operator<<(vector<T> x){ return *this<<range(all(x));}
};

#define MAXN 200123

int tree[MAXN];

void solve(void) {

	int n, m;
	scanf("%d %d", &n, &m);
	
	queue<pii> pos;
	set<int> used;
	for(int i = 0; i < n; i++) {
		scanf("%d", &tree[i]);
		used.insert(tree[i]);
	}

	for(int i = 0; i < n; i++) {
		int l = tree[i] - 1, r = tree[i] + 1;
		if(used.find(l) == used.end()) {
			used.insert(l);
			pos.push(mp(1, l));
		}
		if(used.find(r) == used.end()) {
			used.insert(r);
			pos.push(mp(1, r));
		}
	}
	
	vi ans;
	ll res = 0;
	while(m > 0) {
		pii closest = pos.front(); pos.pop();
		int d = closest.first, p = closest.second;
		res += (ll) closest.first;
		ans.pb(p);
		int l = p - 1, r = p + 1;
		if(used.find(l) == used.end()) {
			used.insert(l);
			pos.push(mp(d + 1, l));
		}
		if(used.find(r) == used.end()) {
			used.insert(r);
			pos.push(mp(d + 1, r));
		}
	
		m--;
	}
	
	printf("%lld\n", res);
	for(int i = 0; i < (int) ans.size(); i++) {
		cout << " " + (i==0) << ans[i];
	}
	puts("");
}

int main(void) {

	solve();

	return 0;
}
