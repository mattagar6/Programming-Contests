#define eps 1e-9
#define PI acos(-1)

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
	Vec& rot(double theta) {
		v_type new_x = x * cos(theta) - y * sin(theta);
		v_type new_y = x * sin(theta) + y * cos(theta);
		return *this = Vec(new_x, new_y);
	}
	
	v_type dot(const Vec& rhs) const { return x * rhs.x + y * rhs.y; }
	v_type cross(const Vec& rhs) const { return x * rhs.y - y * rhs.x; }
	double mag() const { return sqrt(x*x + y*y); }
};

using P = Point<double>;
using V = Vec<double>;

double dist(P a, P b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

////////////////////////////////////////////////////////////////////

////////////////////////////////// Circles //////////////////////////////////

struct Circle {
	P center;
	double r;
	Circle(P _center, double _r) : center(_center), r(_r) {}
};

// Intersection of 2 circles:
// returns true if c1 and c2 intersect, their points of intersection stored in ans
bool intersect(Circle c1, Circle c2, vector<P>& ans) {
	P p = c1.center, q = c2.center;
	double r1 = c1.r, r2 = c2.r;
	double d = dist(p, q);
	if(d > r1 + r2 || d < fabs(r1 - r2)) return false;
	
	double a = (r1*r1 - r2*r2 + d*d) / (2*d);
	double h = sqrt(r1 * r1 - a * a);

	V u(p, q), v(p, q);
	u.scale(h/u.mag());
	u.rot(PI/2);
	v.scale(a/v.mag());

	ans.push_back(P(p.x + u.x + v.x, p.y + u.y + v.y));
	u.rot(PI);
	ans.push_back(P(p.x + u.x + v.x, p.y + u.y + v.y));
	return true;
};

////////////////////////////////////////////////////////////////////
