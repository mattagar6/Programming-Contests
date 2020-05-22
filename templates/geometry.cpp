#define eps 1e-12
#define PI acos(-1)

using ll = long long;
using ld = long double;

////////////////////////////////// Must Have's //////////////////////////////////

template<typename p_type>
struct Point {
    p_type x, y;
    Point(p_type _x = 0, p_type _y = 0) : x(_x), y(_y) {}
    
    bool operator ==(Point rhs) const { return fabs(x - rhs.x) < eps && fabs(y - rhs.y) < eps; }
    bool operator <(Point rhs) const { return tie(x, y) < tie(rhs.x, rhs.y); }
    Point operator +(Point rhs) const { return Point(x + rhs.x, y + rhs.y); }
    Point operator -(Point rhs) const { return Point(x - rhs.x, y - rhs.y); }
};

template<typename p_type>
ostream& operator <<(ostream& out, Point<p_type> p) {
    return out << fixed << setprecision(3) << "(" << p.x << ", " << p.y << ")";
}

template<typename p_type>
istream& operator >>(istream& in, Point<p_type>& p) {
    return in >> p.x >> p.y;
}

template<typename v_type>
struct Vec {
    v_type x, y;
    
    Vec(v_type _x = 0, v_type _y = 0) : x(_x), y(_y) {}
    Vec(Point<v_type> a, Point<v_type> b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    
    Vec operator +(Vec rhs) const { return Vec(x + rhs.x, y + rhs.y); }
    Vec operator -(Vec rhs) const { return Vec(x - rhs.x, y - rhs.y); }
    
    Vec& scale(v_type s) { return *this = Vec(x * s, y * s); }
    Vec& rot(ld theta) {
        v_type new_x = x * cos(theta) - y * sin(theta);
        v_type new_y = x * sin(theta) + y * cos(theta);
        return *this = Vec(new_x, new_y);
    }
    
    v_type dot(Vec rhs) const { return x * rhs.x + y * rhs.y; }
    v_type cross(Vec rhs) const { return x * rhs.y - y * rhs.x; }
    ld mag() const { return sqrtl((ld)x*x + (ld)y*y); }
};

using P = Point<ll>;
using V = Vec<ll>;

bool angleCmp(P a, P b) {
    V va(a.x, a.y), vb(b.x, b.y);
    if(va.cross(vb) == 0) {
        return va.mag() < vb.mag();
    } else {
        return va.cross(vb) > 0;
    }
}

ld dist(P a, P b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

ld angle(V u, V v) {
    return acos(u.dot(v) / (u.mag() * v.mag()));
}

// assumes points[0] == points[n-1]
ld area(vector<P> points) {
    ld ans = 0;
    int n = points.size();
    for(int i = 0; i < n-1; i++) {
        ans += points[i].x * points[i+1].y - points[i].y * points[i+1].x;
    }
    return fabs(ans) / 2.0;
}

// get convex hull of a set of points => O(nlogn)
// check for collinear points!
vector<P> get_hull(vector<P> arr) {
    vector<P> hull;
    sort(arr.begin(), arr.end());
    arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
    int n = arr.size();
    
    P pivot = arr[0];
    sort(arr.begin()+1, arr.end(), [&](P a, P b) {
        return angleCmp(a - pivot, b - pivot);
    });

    for(int i = 0; i < n; i++) {
        while((int) hull.size() > 1) {
            int m = hull.size();
            V v(hull[m-2], arr[i]), u(hull[m-1], arr[i]);
            if(v.cross(u) <= 0) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(arr[i]);
    }
    
    return hull;
}

////////////////////////////////// Lines //////////////////////////////////

// line segments
struct Line {
    P p, q; // endpoints (p.x <= q.x)
    ll a, b, c; // ax + by + c = 0, a >= 0
    Line(P _p, P _q) : p(_p), q(_q) {
        if(p.x > q.x) swap(p, q);
        ll x0 = p.x, y0 = p.y, x1 = q.x, y1 = q.y;
        a = y1-y0, b = x0-x1;
        c = (y0-y1)*x0 + (x1-x0)*y0;
        ll GCD = gcd(gcd(llabs(a), llabs(b)), llabs(c));
        a /= GCD, b /= GCD, c /= GCD;
        if(a < 0) {
            a *= -1, b *= -1, c *= -1;
        } else if(a == 0 && b < 0) {
            b *= -1, c *= -1;
        }
    }
    
    bool operator ==(const Line& rhs) const { return tie(a, b, c) == tie(rhs.a, rhs.b, rhs.c); }
    bool operator !=(const Line& rhs) const { return !(*this == rhs); }
    
    bool contains(P rhs) const {
        return a*rhs.x + b*rhs.y + c == 0 && 
                p.x <= rhs.x && rhs.x <= q.x && 
                min(p.y, q.y) <= rhs.y && rhs.y <= max(p.y, q.y);
    }
};

bool areParallel(Line l1, Line l2) {
    return l1.a == l2.a && l1.b == l2.b;
}

// do two line segments intersect at integer coords?
bool intersect(Line l1, Line l2, P& p) {
    if(areParallel(l1, l2)) return false;
    if((-l1.b*l2.c + l2.b*l1.c) % (l2.a*l1.b - l1.a*l2.b)) return false;
    p.x = (-l1.b*l2.c + l2.b*l1.c) / (l2.a*l1.b - l1.a*l2.b);

    if(l1.b != 0) {
        if((l1.a * p.x + l1.c) % l1.b) return false;
        p.y = -(l1.a * p.x + l1.c) / l1.b;
    } else {
        if((l2.a * p.x + l2.c) % l2.b) return false;
        p.y = -(l2.a * p.x + l2.c) / l2.b;
    }
    if(!l1.contains(p) || !l2.contains(p)) return false;
    return true;
}

////////////////////////////////// Circles //////////////////////////////////

struct Circle {
    P center;
    ld r;
    Circle(P _center = P(), ld _r = -1) : center(_center), r(_r) {}
    
    ld area() const { return PI * r * r; }
    
    bool inside(const Circle& you) const {
        return dist(center, you.center) + r < you.r + eps;
    }
};

// Intersection of 2 circles:
// returns true if c1 and c2 intersect at 2 points, their points of intersection stored in ans
bool intersect(Circle c1, Circle c2, vector<P>& ans) {
    P p = c1.center, q = c2.center;
    ld r1 = c1.r, r2 = c2.r;
    ld d = dist(p, q);
    if(d + eps > r1 + r2 || d < fabs(r1 - r2) + eps) return false;
    
    ld a = (r1*r1 - r2*r2 + d*d) / (2*d);
    ld h = sqrt(r1 * r1 - a * a);

    V u(p, q), v(p, q);
    u.scale(h/u.mag());
    u.rot(PI/2);
    v.scale(a/v.mag());

    ans.push_back(P(p.x + u.x + v.x, p.y + u.y + v.y));
    u.rot(PI);
    ans.push_back(P(p.x + u.x + v.x, p.y + u.y + v.y));
    return true;
};

///////////////////////////////// Triangles ///////////////////////////////////

struct Triangle {
    P a, b, c;
    Triangle(P _a = P(), P _b = P(), P _c = P()) : a(_a), b(_b), c(_c) {}
    
    ld per() const {
        return dist(a, b) + dist(b, c) + dist(a, c);
    }
    
    ld area() const {
        ld s = per() / 2;
        ld x = dist(a, b), y = dist(b, c), z = dist(c, a);
        return sqrt(s * (s - x)) * sqrt((s - y) * (s - z));
    }
};

////////////////////////////////////////////////////////////////////////////////
