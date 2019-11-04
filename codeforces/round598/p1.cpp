#include <bits/stdc++.h>

#define ALL(x) x.begin(), x.end()

using namespace std;

typedef long long ll;
typedef vector<int> vi;

void solve(void) {

	int q;
	cin >> q;

	for(int zzz = 0; zzz < q; zzz++) {
		int a, b, n, s;
		cin >> a >> b >> n >> s;

		if(s < n) {
			cout << (s <= b ? "YES" : "NO") << '\n';
		} else {
			s -= n*min(s/n, a);
			cout << (s <= b ? "YES" : "NO") << '\n';
		}

	}


}

int main(void) {

	solve();
	return 0;
}
