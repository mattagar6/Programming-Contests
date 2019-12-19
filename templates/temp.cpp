#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define For(i,a,b) for(int i = a; i < b; i++)
#define Ford(i,a,b) for(int i = a; i >= b; i--)
#define Fill(x,v) memset(x, v, sizeof(x))
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

void solve(void) {



}

int main(void) {


	return 0;
}
