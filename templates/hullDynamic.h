// major inspiration from: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
// template for convex hull trick, dp optimization
// add -> O(log(n)), get_max -> O(log(n))

using ll = long long;

struct Line {
    mutable ll m, b, p; // p = point this line intersects next line on hull with > slope
    bool operator <(const Line& rhs) const { return m < rhs.m; }
    bool operator <(ll x) const { return p < x; }
    ll eval(ll x) const { return m * x + b; }
};

struct HullDynamic : multiset<Line, less<>> {
    const ll inf = numeric_limits<ll>::max()/2;
    
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
    
    bool isect(iterator x, iterator y) {
        if(y == end()) { x->p = inf; return false; }
        if(x->m == y->m) x->p = x->b > y->b ? inf : -inf;
        else x->p = div(x->b - y->b, y->m - x->m);
        return y->p <= x->p;
    }
    
    void add(Line l) {
        auto z = insert(l), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if(x != begin() && isect(--x, y)) isect(x, y = erase(y)); // don't insert l
        while((y = x) != begin() && (--x)->p >= y->p) {
            isect(x, erase(y));
        }
    }
    
    ll get_max(ll x) {
        assert(!empty());
        return lower_bound(x)->eval(x);
    }
};
