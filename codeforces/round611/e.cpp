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
int house[MAXN];

void solve(void) {

	int n;
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++)
		scanf("%d", &house[i]);
	
	sort(house, house + n);

	set<int> used;
	for(int i = 0; i < n; i++) {
		int p = house[i];
		if(used.find(p-1) == used.end()) {
			used.insert(p-1);
		} else if(used.find(p) == used.end()) {
			used.insert(p);
		} else if(used.find(p+1) == used.end()) {
			used.insert(p+1);
		}
	}
	int mx = used.size();
	used.clear();
	for(int i = 0; i < n; i++) {
		int p = house[i];
		if(used.count(p-1) + used.count(p) + used.count(p+1)) {
			continue;
		} else {
			used.insert(p+1);
		}
	}
	int mn = used.size();
	printf("%d %d\n", mn, mx);
}

int main(void) {

	solve();
	return 0;
}
