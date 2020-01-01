# Results
Solved 5/6 questions, ranked [105](https://codeforces.com/contest/1283/standings). 
My best result in a contest to date! I had a slow start to the contest, mainly due to the implementation of problem C. 
However, I turned things around at the end and was able to solve D and E in 10 minutes.

# Analysis
### [A. Minutes Before the New Year](https://codeforces.com/contest/1283/problem/A)
Simple math problem, print the answer.

```C++
void solve(void) {
 
	int h, m;
	scanf("%d %d", &h, &m);
	
	int ans = 0;
	ans += 60 - m;
	ans += 60*(23-h);
	printf("%d\n", ans);
 
}
```
Time Complexity: O(1).<br>
Space Complexity: O(1).

### [B. Candies Division](https://codeforces.com/contest/1283/problem/B)
Another math problem, this one a little bit more difficult than the last. It is always optimal to give out **floor(n/k)** candies, 
ans have **n % k** candies left over. If **n % k** is greater than **floor(k/2)**, fix it.

```C++
void solve(void) {
 
	int n, k;
	scanf("%d %d", &n, &k);
	
	int ans = n;
	int extra = n % k;
	if(extra > k/2) {
		extra -= k/2;
		ans -= extra;
	}
	printf("%d\n", ans);
 
}
```
Time Complexity: O(1).<br>
Space Complexity: O(1).

### [C. Friends and Gifts](https://codeforces.com/contest/1286/problem/C)
I solved this problem using a greedy method. I maintained a set **needs** of all the people who need a gift, and an array **f**
that maps a person to whom they are gifting. First, I dealt with all the cases in which person **i** needs a gift and has to give a gift also; 
I did this to avoid constructing the case where **f[i] = i**, as part of the problem statement. After that, it doesn't matter how you distribute the gifts,
as long as each person gives and recieves exactly one gift.<br><br>
Note: There is a clever randomized algorithm that randomly permutes people until a **Derangement** is found (f[i] != i for all i). A derangement is found
with probablity approximately **1/e**, so that algorithm is O(n).
```C++
#define MAXN 200123
 
int f[MAXN];
 
void solve(void) {
 
	int n;
	scanf("%d", &n);
	
	set<int> needs;
	vi give;
	for(int i = 1; i <= n; i++) {
		needs.insert(i);
	}
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &f[i]);
		if(f[i]) needs.erase(f[i]);
		else give.pb(i);
	}
	
	for(int x : give) {
		if(needs.find(x) != needs.end()) {
			auto it = needs.begin();
			while(*it == x) it++;
			f[x] = *it;
			needs.erase(*it);
		}
	}
	for(int i = 1; i <= n; i++) {
		if(f[i] == 0) {
			f[i] = *needs.begin();
			needs.erase(*needs.begin());
		}
		cout << " " + (i==1) << f[i];
	}
 
 
	puts("");
 
}
```
Time Complexity: O(nlog(n)), since I used std::set in my implementation.<br>
Space Complexity: O(n).
### [D. Christmas Trees](https://codeforces.com/contest/1286/problem/D)
This problem is efficiently solved using multi-source BFS. Each tree is a starting node with neighbours to its left and right.
After that, use BFS to find the closest **m** neighbours to all the trees.
```C++
#define MAXN 200123
int tree[MAXN];
 
void solve(void) {
 
	int n, m;
	scanf("%d %d", &n, &m);
	
	queue<pii> pos;
	set<int> used;
	for(int i = 0; i < n; i++) {
		scanf("%d", &tree[i]);
		used.insert(tree[i]);
	}
 
	for(int i = 0; i < n; i++) {
		int l = tree[i] - 1, r = tree[i] + 1;
		if(used.find(l) == used.end()) {
			used.insert(l);
			pos.push(mp(1, l));
		}
		if(used.find(r) == used.end()) {
			used.insert(r);
			pos.push(mp(1, r));
		}
	}
	
	vi ans;
	ll res = 0;
	while(m > 0) {
		pii closest = pos.front(); pos.pop();
		int d = closest.first, p = closest.second;
		res += (ll) closest.first;
		ans.pb(p);
		int l = p - 1, r = p + 1;
		if(used.find(l) == used.end()) {
			used.insert(l);
			pos.push(mp(d + 1, l));
		}
		if(used.find(r) == used.end()) {
			used.insert(r);
			pos.push(mp(d + 1, r));
		}
	
		m--;
	}
	
	printf("%lld\n", res);
	for(int i = 0; i < (int) ans.size(); i++) {
		cout << " " + (i==0) << ans[i];
	}
	puts("");
}
```
Time Complexity: O(m).<br>
Space Complexity: O(m).
### [E. New Year Parties](https://codeforces.com/contest/1286/problem/E)
A greedy problem. For the maximum number of houses, it is always optimal to move as far to the left as possible. Similarly,
for the minimum, move as far to the right.
```C++
#define MAXN 200123
int house[MAXN];
 
void solve(void) {
 
	int n;
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++)
		scanf("%d", &house[i]);
	
	sort(house, house + n);
 
	set<int> used;
	for(int i = 0; i < n; i++) {
		int p = house[i];
		if(used.find(p-1) == used.end()) {
			used.insert(p-1);
		} else if(used.find(p) == used.end()) {
			used.insert(p);
		} else if(used.find(p+1) == used.end()) {
			used.insert(p+1);
		}
	}
	int mx = used.size();
	used.clear();
	for(int i = 0; i < n; i++) {
		int p = house[i];
		if(used.count(p-1) + used.count(p) + used.count(p+1)) {
			continue;
		} else {
			used.insert(p+1);
		}
	}
	int mn = used.size();
	printf("%d %d\n", mn, mx);
}
```
Time Complexity: O(n).<br>
Space Complexity: O(n).
