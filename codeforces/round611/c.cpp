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

int f[MAXN];

void solve(void) {

	int n;
	scanf("%d", &n);
	
	set<int> needs;
	vi give;
	for(int i = 1; i <= n; i++) {
		needs.insert(i);
	}
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &f[i]);
		if(f[i]) needs.erase(f[i]);
		else give.pb(i);
	}
	
	for(int x : give) {
		if(needs.find(x) != needs.end()) {
			auto it = needs.begin();
			while(*it == x) it++;
			f[x] = *it;
			needs.erase(*it);
		}
	}
	for(int i = 1; i <= n; i++) {
		if(f[i] == 0) {
			f[i] = *needs.begin();
			needs.erase(*needs.begin());
		}
		cout << " " + (i==1) << f[i];
	}


	puts("");

}

int main(void) {

	solve();
	return 0;
}
