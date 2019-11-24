# Results
Solved 4/4 questions, ranked [255/5907](https://leetcode.com/contest/weekly-contest-164/ranking/). 
This contest went better than last week. My original solution to question 4 was too slow, causing an incorrect submission.
However, I was happy that I was able to quickly realize where I could improve my solution.

# Analysis
### [Minimum Time Visiting All Points](https://leetcode.com/problems/minimum-time-visiting-all-points/)
I solved this question using a greedy method. The time required to move from one position to another is exactly equal to
the maximum of the delta x and delta y positions between the two points.
```C++
class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int ans = 0;
        int n = points.size();
        
        for(int i = 1; i < n; i++) {
            ans += max(abs(points[i][0] - points[i-1][0]),
                      abs(points[i][1] - points[i-1][1]));
        }
                
        return ans;
    }
};
```
Time Complexity: O(n)<br>
Space Complexity: O(1)<br>
### [Count Servers that Communicate](https://leetcode.com/problems/count-servers-that-communicate/)
Get ready for some ugly code. My midset during coding contests is to pump out working solutions as fast as possible, so I don't spare
much effort towards making the code look clean. With that aside, my strategy was to count servers in each row and column, and add those servers
to the answer. Afterwards, we may have double counted some servers, so I used another array to keep track of that.
```C++
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int ans = 0;
        
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> A(n, vector<int>(m));
        for(int i = 0; i < n; i++) {
            int cnt = 0;
            for(int j = 0; j < m; j++) {
                cnt += grid[i][j];
            }
            if(cnt > 1) {
                ans += cnt;
                for(int j = 0; j < m; j++) {
                    if(grid[i][j]) {
                        ++A[i][j];
                    }
                }
            }
        }
        
        for(int j = 0; j < m; j++) {
            int cnt = 0;
            for(int i = 0; i < n; i++) {
                cnt += grid[i][j];
            }
            if(cnt > 1) {
                ans += cnt;
                for(int i = 0; i < n; i++) {
                    if(grid[i][j]) {
                        ++A[i][j];
                    }
                }
            }
        }
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(A[i][j] == 2) { // if we double counted
                    --ans;
                }
            }
        }

        
        return ans;
    }
};
```
Time Complexity: O(nm)<br>
Space Complexity: O(nm)<br>
### [Search Suggestions System](https://leetcode.com/problems/search-suggestions-system/)
As the constraints of this problem were quite small, I used the naive algorithm and implemented it in Python. If the time to implement a solution was not a concern,
I would have used a Trie and done a DFS to find strings in **products** that match each prefix of **word**. 
```Python
class Solution(object):
    def suggestedProducts(self, products, word):
        """
        :type products: List[str]
        :type word: str
        :rtype: List[List[str]]
        """
        products.sort()
        ans = []
        n = len(word)
        
        for i in range(n):
            cur = []
            for w in products:
                if w.startswith(word[:i+1]):
                    cur.append(w)
                if len(cur) == 3:
                    break
        
            ans.append(cur)
        
        return ans
```
Time Complexity: O(max(nm, mlog(m))), where m is the size of the array **products**. This runtime is either dominated by the sort,
or by the length of the string **word**.
### [Number of Ways to Stay in the Same Place After Some Steps](https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/)
This problem can be solved quite easily using Dynamic Programming. The relevant states are the pointer's current position, and the number of moves we have used so far.
I initially impemented a DP solution that ran in O(n*steps) time, but this was too slow as n can be as large as 10^6. I improved this initial DP
by noticing the constraints on **steps** (steps <= 500). These small contstraints mean that it is impossible for the pointer to move further right
than index **500**; so there is no need for the DP array to be as large as 10^6. With this observation, I capped the size of the DP array to be
approximately 10^5 (which is still way bigger than it needs to be).
```C++
class Solution {
public:
    int mod = 1e9 + 7;
    const int N = 10123;
    
    int numWays(int steps, int n) {
        
        vector<int> dp(N);
        dp[0] = 1;
        
        for(int k = 1; k <= steps; k++) {
            vector<int> new_dp = dp;
            for(int i = 0; i < N; i++) {
                if(i > 0) {
                    new_dp[i] += dp[i-1];
                    new_dp[i] %= mod;
                }
                if(i < min(n - 1, N - 1)) {
                    new_dp[i] += dp[i+1];
                    new_dp[i] %= mod;
                }
            }
            dp = new_dp;
        }
        
        
        return dp[0];
    }
};  
```
Time Complexity: O(steps). The inner loop excuecutes a fairly large, but constant number of times.<br>
Space Complexity: O(1). The two DP arrays use a constany ammount of space. I optimized the 2D DP solution to use only one array.

