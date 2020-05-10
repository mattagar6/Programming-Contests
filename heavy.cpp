#include <bits/stdc++.h>
using namespace std;

template<class T> struct rge { T b, e; };
template<class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
struct debug {
#ifdef LOCAL
    ~debug(){cerr<<endl;}
    template<class T> debug& operator<<(T x){cerr<<boolalpha<<x; return *this;}
    template<class B, class C> debug& operator<<(pair<B, C> x){return *this<<"("<<x.first<<", "<<x.second<<")";}
    template<class T> debug& operator<<(rge<T> x){*this<<"[";for(auto it=x.b;it!=x.e;it++){*this<<", "+2*(it==x.b)<<*it;}return *this<<"]";}
    template<class T> debug& operator<<(vector<T> x){ return *this<<range(x.begin(),x.end());}
#else
    template<class T> debug& operator <<(const T&){return *this;}
#endif
};
#define nav(...) << "[ " << #__VA_ARGS__ ": " << (__VA_ARGS__) << " ] "
using ll = long long;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = n-1; i >= 0; i--) 

template<typename T> 
void min_self(T& a, T b) { 
    a = min(a, b); 
}
template<typename T>
void max_self(T& a, T b) { 
    a = max(a, b); 
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);


}













// Those who say they can, and those who say they can't - are both usually right.

// Read statement carefully
// Solve on paper first!
// Overflows (long long)

// Author: blondie
