#include <bits/stdc++.h>

#define ALL(x) x.begin(), x.end()

using namespace std;

typedef long long ll;
typedef vector<int> vi;

void solve(void) {

	int n;
	cin >> n;
	vi A(n);

	for(int& x : A) {
		cin >> x;
	}

	vi pos(n+1);

	for(int i = 0; i < n; i++) {
		pos[A[i]] = i;
	}

	int r = -1;

	for(int x = 1; x <= n; x++) {
		if(pos[x] > r) {
			for(int i = pos[x]; i > max(r, x-1) && A[i] < A[i-1]; --i) {
				swap(A[i], A[i-1]);
			}

			r = pos[x];
		}
	}

	for(int x : A) {
		cout << x << ' ';
	}

	cout << '\n';
}

int main(void) {

	int q;
	cin >> q;

	for(int zzz = 0; zzz < q; zzz++) {
		solve();
	}

	return 0;
}
