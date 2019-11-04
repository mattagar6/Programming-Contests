#include <bits/stdc++.h>

#define ALL(x) x.begin(), x.end()

using namespace std;

typedef long long ll;
typedef vector<int> vi;

void solve(void) {

	int n, m, d;
	cin >> n >> m >> d;
	--d;
	vi A(m);
	int s = 0;
	for(int& x : A) {
		cin >> x;
		s += x;
	}

	vi ans;

	int b = 1;
	for(int x : A) {
		for(int i = 0; i < d; i++) {
			ans.push_back(0);
		}
		for(int i = 0; i < x; i++) {
			ans.push_back(b);
		}
		b++;
	}

	for(int i = 0; i < d; i++) {
		ans.push_back(0);
	}

	if(ans.size() >= n) {
		cout << "YES\n";
		// spaces we have to remove
		int diff = ans.size() - n;

		for(int x : ans) {
			if(diff > 0 && x == 0) {
				--diff;
				continue;
			} else {
				cout << x << ' ';
			}
		}
		cout << '\n';
	} else {
		cout << "NO\n";
	}
}

int main(void) {

	solve();

	return 0;
}
