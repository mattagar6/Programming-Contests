#include <bits/stdc++.h>

#define ALL(x) x.begin(), x.end()

using namespace std;

typedef long long ll;
typedef vector<int> vi;

void solve(void) {

	ll n, k;
	cin >> n >> k;

	string s;
	cin >> s;

	vi zeros;

	for(int i = 0; i < n; i++) {
		if(s[i] == '0') {
			zeros.push_back(i);
		}
	}

	int ones = n - zeros.size();
	int i = 0;
	//put as many zeros at the front as you can
	for(; i < zeros.size() && k >= zeros[i] - i; i++) {
		cout << '0';
		k -= zeros[i] - i;
	}

	if (i < zeros.size()) {
		// still more zeros to place

		int j;

		for (j = i; j < zeros[i] - k; j++) {
			cout << '1';
		}
		cout << '0'; j++;
		while(j <= zeros[i]) {
			cout << '1';
			j++;
		}

		for(int p = zeros[i] + 1; p < n; p++){
			cout << s[p];
		}
		/* code */
	} else {
		while (ones--) {
			cout << '1';
		}
	}


	cout << '\n';
}

int main(void) {

	int q;
	cin >> q;
	for (size_t zzz = 0; zzz < q; zzz++) {
		solve();
	}

	return 0;
}
