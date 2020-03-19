#define eps 1e-12
#define PI acos(-1)

using ld = long double;

////////////////////////////////// Must Have's //////////////////////////////////

template<typename p_type>
struct Point {
	p_type x, y;
	Point(p_type _x = -1, p_type _y = -1) : x(_x), y(_y) {}
};

template<typename v_type>
struct Vec {
	v_type x, y;
	
	Vec(v_type _x = -1, v_type _y = -1) : x(_x), y(_y) {}
	Vec(Point<v_type> a, Point<v_type> b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}
	
	Vec operator +(const Vec& rhs) const { return Vec(x + rhs.x, y + rhs.y); }
	Vec operator -(const Vec& rhs) const { return Vec(x - rhs.x, y - rhs.y); }
	
	Vec& scale(v_type s) { return *this = Vec(x * s, y * s); }
	Vec& rot(ld theta) {
		v_type new_x = x * cos(theta) - y * sin(theta);
		v_type new_y = x * sin(theta) + y * cos(theta);
		return *this = Vec(new_x, new_y);
	}
	
	v_type dot(const Vec& rhs) const { return x * rhs.x + y * rhs.y; }
	v_type cross(const Vec& rhs) const { return x * rhs.y - y * rhs.x; }
	ld mag() const { return sqrt(x*x + y*y); }
};


using P = Point<ld>;
using V = Vec<ld>;

ld dist(P a, P b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

ld angle(V u, V v) {
	return acos(u.dot(v) / (u.mag() * v.mag()));
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
