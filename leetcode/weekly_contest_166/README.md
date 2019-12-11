# Results
Solved 4/4 questions, ranked [316/5586](https://leetcode.com/contest/weekly-contest-166/ranking/). 
This was the easiest contest I've ever participated in. I had my fastest finish time ever, at just over 28 minutes. 
Integer overflow on the second question cost me three incorrect submissions, adding 15 minutes of penalty time; this really hurt
my placement. Without these silly mistakes, I could have finished in the top 100.

# Analysis
### [Subtract the Product and Sum of Digits of an Integer](https://leetcode.com/problems/subtract-the-product-and-sum-of-digits-of-an-integer/)
Do what the title asks.
```Python
class Solution(object):
    def subtractProductAndSum(self, n):
        """
        :type n: int
        :rtype: int
        """
        prod = 1
        s = 0
        for d in str(n):
            prod *= int(d)
            s += int(d)
        return prod - s
```
Time Complexity: O(log(n))<br>
Space Complexity: O(1)<br>
### [Group the People Given the Group Size They Belong To](https://leetcode.com/problems/count-servers-that-communicate/)
Since the problem statement ensures that a solution will always be possible, 
I sorted all of the people and greedily grouped them together.
```Python
class Solution(object):
    def groupThePeople(self, groupSizes):
        """
        :type groupSizes: List[int]
        :rtype: List[List[int]]
        """
        
        n = len(groupSizes)
        A = zip(groupSizes, range(n))
        
        A.sort()
        ans = []
        i = 0
        while i < n:
            sz = A[i][0]
            cur = []
            j = i
            while j < n and j - i < sz:
                    cur.append(A[j][1])
                    j += 1
            ans.append(cur)
            i = j
        
        return ans
```
Time Complexity: O(nlog(n))<br>
Space Complexity: O(n)<br>
### [1283. Find the Smallest Divisor Given a Threshold](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/)
This problem is easily solvable using the "binary search for the answer" technique. We binary search for the **smallest** divisor that
will make the sum less than the given **threshold**. I used a naive upper bound of twice the sum of all elements in A for the answer.
The only issue was that sometimes the sum of all elements in A would overflow a 32 bit **int**, so I converted everything to 64 bit 
**long long**s to be safe.
```C++
class Solution {
public:
    typedef long long ll;
    int smallestDivisor(vector<int>& A, int threshold) {
 
        ll t = (ll) threshold;
        int n = A.size();
        ll s = 0;
        for(int x : A) s += (ll) x;
        ll lo = 1, hi = 2*s;
        ll ans = hi;
        while(lo <= hi) {
            ll mid = lo + (hi-lo)/2;
            ll s = 0;
            for(int x : A) {
                s += (ll) (x + mid - 1)/mid;
            }
            
            if(s <= t) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
            
        }
        
        
        return ans;
    }
};
```
Time Complexity: O(nlog(sum(A))), O(n) time is spent gatherng the sum inside the **while** loop. <br>
Space Complexity: O(1), outside of the space for **A**.
### [ Minimum Number of Flips to Convert Binary Matrix to Zero Matrix](https://leetcode.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/)
Since the input size is small (n, m <= 3), an exponential time algoithm is ok. 
Once you notice the fact that it never makes sense to flip the same tile twice, we can try all 2^nm possible sequnces of flips and choose the most optimal one.
I used some fancy bit techniques to easily iterate over subsets. There is also a clever solution that uses BFS, where each node in the graph is a board state.
```C++
class Solution {
public:
    const int INF = 123;
    int ans = INF;
    
    void flip(vector<vector<int>>& A, int r, int c, int n, int m) {
        vector<pair<int, int>> adj = {{r, c}, {r-1, c}, {r, c+1}, {r+1, c}, {r, c-1}};
        for(auto& p : adj) {
            int x = p.first, y = p.second;
            if(0 <= x && x < n && 0 <= y && y < m) {
                A[x][y] ^= 1;
            }
        }
    }
    
    int minFlips(vector<vector<int>>& A) {
        int n = A.size(), m = A[0].size();
        
        vector<vector<int>> done(n, vector<int>(m));
        
        int up = n*m;
        for(int s = 0; s < (1<<up); s++) {
            int ops = 0;
            auto tmp = A;
            for(int b = 0; b < up; b++) {
                if(s & (1<<b)) {
                    int r = b/m, c = b%m;
                    flip(tmp, r, c, n, m);
                    ops++;
                }
            }
            if(tmp == done) {
                ans = min(ans, ops);
            }
        }
        
        return ans == INF ? -1 : ans;
    }
};  
```
Time Complexity: O(2^(nm)).<br>
Space Complexity: O(nm). 
