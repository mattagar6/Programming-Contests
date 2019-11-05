# Results
Solved 3/6 questions, ranked [1973/12995](https://codeforces.com/contest/1256/standings/participant/29666016#p29666016). 
My first attempts to each of the three solved questions were incorrect, which was a bit unusual. However, I was happy that I was able to debug efficiently and fix my solutions.
Had I not made mistakes on the first three questions, I would have been able to submit the 4th problem in time.

# Analysis
### [A. Payment Without Change](https://codeforces.com/contest/1256/problem/A)
I was able to solve this problem by breaking it down into two cases:

1. **n > S** => we have no choice but to pay using the **b** coins of value 1.
2. Otherwise, use as many of the **a** coins of value **n** as possible, then use the **b** coins of value 1.
```C++
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
```
Time Complexity: O(1).<br>
Space Complexity: O(1).

### [B. Minimize the Permutation](https://codeforces.com/contest/1256/problem/B)
I solved this problem using a greedy method. It is always in our best interest to move the **1** all the way to the left.
After that, Try moving the **2** all the way to the left, then **3** and so on. The only catch is that we can only make each swap between 
indices **i** and **i+1** once. To deal with this, I kept track of the rightmost index that we have swapped with a pointer **r**.

```C++
void solve(void) {
 
	int n;
	cin >> n;
	vector<int> A(n);
 
	for(int& x : A) {
		cin >> x;
	}
 
	vector<int> pos(n+1);
 
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
```
Time Complexity: O(n). Dispite the nested loops, We make at most **n - 1** swaps at constant time per swap.<br>
Space Complexity: O(n).

### [C. Platforms Jumping](https://codeforces.com/contest/1256/problem/C)
Again, I solved this problem using a greedy method. I first created an array that represents the maximum distance we can jump.
If the size of this array is at least **n**, it is possible to make the jumps. Otherwise it is impossible.
```C++
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
```
### [D. Binary String Minimizing](https://codeforces.com/contest/1256/problem/D)
Another greedy algorithm. Since we only have **k** swaps (between adjacent elements) to utilize, 
it is always in our best interest to move the **leftmost** zero all the way to the beginning of the string,
since it requires the least amount of swaps. Then we will do the same with the next zero and so on. Eventually, we will either move all the zeros to the beginning,
or we will run out of swaps before then. I handled these two cases sepeartely. In the latter case, it is still in our best interest to move our "current" zero as far left as possible.
```C++
void solve(void) {
 
	long long n, k;
	cin >> n >> k;
 
	string s;
	cin >> s;
 
	vector<int> zeros;
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
	} else {
		while (ones--) {
			cout << '1';
		}
	}
 
	cout << '\n';
}
```
Time Complexity: O(n).<br>
Space Complexity: O(n).

