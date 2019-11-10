# Results
Solved 4/4 questions, ranked [294/6058](https://leetcode.com/contest/weekly-contest-162/ranking/). 
All 4 problems were pretty straightforward and I was able to come up with working solutions at a good pace. 
However, I wasted a fair amount of time handling edge cases in the 2nd question, during which I made 2 incorrect submissions.

# Analysis
### [Cells with Odd Values in a Matrix](https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/)
To solve this quetions, I iterated over the "indices" array and incremented the corresponding cells in the matrix.
After that, count the number of odd cells and return the answer.

```C++
class Solution {
public:
    int oddCells(int n, int m, vector<vector<int>>& indices) {
        
        vector<vector<int>> A(n, vector<int>(m));
        
        for(auto& p : indices) {
            int r = p[0], c = p[1];
            for(int j = 0; j < m; j++) {
                ++A[r][j];
            }
            
            for(int i = 0; i < n; i++) {
                ++A[i][c];
            }
        }
        
        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ans += A[i][j] % 2;
            }
        }
        
        return ans;
        
    }
};
```
Time Complexity: O(mn).<br>
Space Complexity: O(mn).

### [Reconstruct a 2-Row Binary Matrix](https://leetcode.com/problems/reconstruct-a-2-row-binary-matrix/)
I solved this question using a greedy method. First, if **colsum[i] = 2**, then both the top and bottom cells must be 1.
Second, if **colsum[i] = 1** it doesn't matter if we place the 1 in the top or bottom cell, as long as we have available 1's to place.
If at any point we run out of 1's to place and **colsum[i] = 1**, we know it is impossible to reconstruct the matrix. 
Also, if we satisfy all the conditions of **colsum** and still have 1's left over, we know it is impossible to reconstruct the matrix.
I tested for these cases and greedily tried to reconstuct the matrix.
```C++
class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
        
        int n = colsum.size();
        vector<vector<int>> ans(2, vector<int>(n));
        
        // handle all 2s
        for(int i = 0; i < n; i++) {
            if(colsum[i] == 2 && lower && upper) {
                ans[0][i] = ans[1][i] = 1;
                --upper, --lower;
            }
        }
        
        for(int i = 0; i < n; i++) {
            if(upper && ans[0][i] == 0 && colsum[i] == 1) {
                ans[0][i] = 1;
                upper--;
            } else if(lower && ans[1][i] == 0 && colsum[i] == 1) {
                ans[1][i] = 1;
                --lower;
            }
            
        }
        
        bool possible = upper == 0 && lower == 0;
        for(i = 0; i < n; i++) {
            if(colsum[i] != ans[0][i] + ans[1][i]) possible = false;
        }
        
        
        if(possible) {
            return ans;
        } else {
            return vector<vector<int>>();
        }
        
    }
};
```
Time Complexity: O(n).<br>
Space Complexity: O(n).

### [Number of Closed Islands](https://leetcode.com/problems/number-of-closed-islands/)
This problem calls for DFS/BFS. Each cell in **grid** is a node in our graph, 
and is connected to its 4-directional neighbours with edges. I iterated over the cells in **grid** and from each unseen **0**,
begin a depth-first search. We know that this **0** will belong to a closed island if and only if it is bordered by 1's; 
so if for any reason we traverse off the **grid**, we know that this **0** cannot belong to a closed island. Personally, 
I belive that DFS and BFS are faster to implement in Python than C++, so I used Python to solve this question.

```Python
class Solution(object):
    def closedIsland(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        
        n = len(grid)
        m = len(grid[0])
        seen = set()
        
        def dfs(i, j):

            seen.add((i, j))
            
            if i < 0 or i == n or j < 0 or j == m:
                return 0
            
            if grid[i][j] == 1:
                return 1
            
            ans = 1
            for (x, y) in {(i-1, j), (i, j+1), (i+1, j), (i, j-1)}:
                if (x, y) not in seen:
                    ans = ans & dfs(x, y)
            
            return ans
        
        ans = 0
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 0 and (i, j) not in seen:
                    ans += dfs(i, j)
                    
        return ans
```
Time Complexity: O(mn), each **grid[i][j]** is traversed at most by **dfs(i, j)**.<br>
Space Complexity: O(mn), the space required for the set **seen** to keep track of visited nodes.

### [Maximum Score Words Formed by Letters](https://leetcode.com/problems/maximum-score-words-formed-by-letters/)
Since the maximum number of strings in **words** is at most 14, a brute force algorithm is acceptable for this problem. 
I recursed through all subsets of **words** and calculated their respective scores. I took the maximum of these scores to be the answer.

```C++
class Solution {
public:
    
    int ans = 0;

    vector<int> score;
    vector<string> words;
    
    void subsets(map<char, int>& cnts, int i, int cur) {
        int n = words.size();
        if(i == n) {
            ans = max(ans, cur);
        } else {
            // try to take the ith word
            map<char, int> tmp = cnts;
            int next = cur;
            bool possible = true;
            for(char c : words[i]) {
                if(tmp[c] == 0) {
                    possible = false;
                } else {
                    --tmp[c];
                    next += score[c - 'a'];
                }
            }
            if(possible) {
                subsets(tmp, i+1, next);
            }
            // don't take the ith word
            subsets(cnts, i+1, cur);
        }
    }
    
    
    int maxScoreWords(vector<string>& words_, vector<char>& letters, vector<int>& scores) {
        score = scores;
        words = words_;
        
        map<char, int> cnts;
        for(char c : letters) {
            ++cnts[c];
        }

        subsets(cnts, 0, 0);
        return ans;
    }
};
```
Time Complexity: O(W*2^n), where **W** is the length of the longest string in **words** and **n** is the size of words.

