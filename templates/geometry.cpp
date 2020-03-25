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
	ld mag() const { return sqrt(x*x + y*y); }
};


using P = Point<ll>;
using V = Vec<ll>;

bool angleCmp(P a, P b) {
	V va(a.x, a.y), vb(b.x, b.y);
	if(va.cross(vb) == 0) {
		return va.mag() < vb.mag();
	} else {
		return atan2(va.y, va.x) < atan2(vb.y, vb.x);
	}
}

ld dist(P a, P b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

ld angle(V u, V v) {
	return acos(u.dot(v) / (u.mag() * v.mag()));
}

// get convex hull of a set of points => O(nlogn)
// check for collinear points!
vector<P> get_hull(vector<P> arr) {
	vector<P> hull;
	sort(arr.begin(), arr.end());
	arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
	int n = arr.size();
	
	if(n <= 3) {
		return arr;
	}
	
	int pos = 0;
	for(int i = 1; i < n; i++) {
		if(arr[i].y < arr[pos].y || (arr[i].y == arr[i].y && arr[i].x > arr[pos].x)) {
			pos = i;
		}
	}
	
	swap(arr[0], arr[pos]);
	P pivot = arr[0];
	sort(arr.begin()+1, arr.end(), [&](P a, P b) {
		return angleCmp(a - pivot, b - pivot);
	});
	
	hull = {arr[n-1], arr[0], arr[1]};
	int i = 2;
	while(i < n) {
		int j = (int) hull.size() - 1;
		V a(hull[j], arr[i]), b(hull[j], hull[j-1]);
		if(a.cross(b) > 0) {
			hull.push_back(arr[i++]);
		} else if(a.cross(b) == 0) {
			// handle collinear points
			hull.push_back(arr[i++]);
		} else {
			hull.pop_back();
		}
	}
	
	return hull;
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
