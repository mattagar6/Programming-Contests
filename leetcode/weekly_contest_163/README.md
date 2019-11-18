# Results
Solved 3/4 questions, ranked [532/5873](https://leetcode.com/contest/weekly-contest-163/ranking/). 
Not my best contest. I had multiple incorrect submissions on the first and third questions, 
and I completely blanked on the fourth problem during the contest.

# Analysis
### [Shift 2D Grid](https://leetcode.com/problems/shift-2d-grid/)
I dumped the 2D grid int a 1D array, rotated the array, and then dumped it back into the grid.
```C++
class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        
        k %= m*n;
        
        vector<int> A;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                A.push_back(grid[i][j]);
            }
        }
        
        reverse(A.begin(), A.end());
        reverse(A.begin(), A.begin()+k);
        reverse(A.begin()+k, A.end());
        
        for(int i = 0; i < n*m; i++) {
            grid[i/m][i%m] = A[i];
        }
        
        return grid;
    }
};
```
Time Complexity: O(nm)<br>
Space Complexity: O(nm)<br>
### [Find Elements in a Contaminated Binary Tree](https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/)
I rebuilt the Tree according to the the rule in the problem statement using DFS. I used a set of node values to help with the **find()** operation. 
I also saw some clever solutions that used an inorder traversal and binary search to implement the **find()** operation.
```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class FindElements {
public:
    
    TreeNode* root;
    set<int> nodes;
    void dfs(TreeNode* u, int val) {
        u->val = val;
        nodes.insert(val);
        if(u->left) dfs(u->left, 2*val + 1);
        if(u->right) dfs(u->right, 2*val + 2);
    }
    
    FindElements(TreeNode* r) {
        root = r;
        dfs(root, 0);
    }
    
    bool find(int target) {
        return nodes.find(target) != nodes.end();   
    }
};
```
Time Complexity: O(n) for **FindElements()**, O(lg(n)) for **find()**<br>
Space Complexity: O(n)<br>
### [Greatest Sum Divisible by Three](https://leetcode.com/problems/greatest-sum-divisible-by-three/)
I used a greedy algorithm. Take the sum of the entire array and consider it modulo 3.
If the sum has a remainder, greedily remove the smallest elements that will make the sum 0 modulo 3.
```C++
class Solution {
public:
    int maxSumDivThree(vector<int>& A) {
        
        int n = A.size();
        sort(A.begin(), A.end());
        vector<vector<int>> rem(3);
     
        for(int i = 0; i < n; i++) {
            rem[A[i]%3].push_back(A[i]);
        }
        
        int ans = 0;
        for(int x : A) {
            ans += x;
        }
        
        if(ans % 3 == 1) {
            int x = INT_MAX;
            int y = INT_MAX;
            if ((int) rem[2].size() >= 2) {
                x = rem[2][0] + rem[2][1];
            }
            if((int) rem[1].size() >= 1) {
                y = rem[1][0];
            }
            
            ans -= min(x, y);
        } else if(ans % 3 == 2) {
            int x = INT_MAX;
            int y = INT_MAX;
            if ((int) rem[1].size() >= 2) {
                x = rem[1][0] + rem[1][1];
            }
            if((int) rem[2].size() >= 1) {
                y = rem[2][0];
            }
            ans -= min(x, y);
        }
        
        return ans;
    }
};
```
Time Complexity: O(nlg(n)), because of the sort. This solution can be easily optimized to O(n); I didn't really care about the difference in complexities during the contest.<br>
Space Complexity: O(n)<br>
### [Minimum Moves to Move a Box to Their Target Location](https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/)
I solved this problem using Dijkstra's shortest path algorithm. The implementation was easier in Python, so that's what I went with.
I kept track of the target, box, and player's coordinates, and looked for the shortest path for the box to get to the target (shortest means the minimum number of pushes).
Even using Python, the implementation was a bit tricky; the nodes in the graph kept track of both the box and the player's coordinates. 
Additional checks were needed to determine wheter or not the player could push the box when the two were adjacent.
```Python
class Solution(object):
    def minPushBox(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        
        # add "padding" to the exterior of the grid
        m = len(grid[0])
        grid = [['#']*(m+2)] + grid + [['#']*(m+2)]
        m += 2
        n = len(grid)
        for i in range(1, n-1):
            grid[i] = ['#'] + grid[i] + ['#']
        
        sr = sc = br = bc = tr = tc = None
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 'S':
                    sr = i
                    sc = j
                if grid[i][j] == 'B':
                    br = i
                    bc = j
                if grid[i][j] == 'T':
                    tr = i
                    tc = j

        q = [(0, br, bc, sr, sc)]
        seen = set()
        seen.add((br, bc, sr, sc))
        while q:
            d, br, bc, sr, sc = heapq.heappop(q)
            
            if (br, bc) == (tr, tc):
                return d
            
            for dx, dy in {(-1, 0), (0, 1), (1, 0), (0, -1)}:
                if (br+dx, bc+dy, sr + dx, sc + dy) not in seen and 
                    (sr + dx, sc + dy) == (br, bc) and grid[br+dx][bc+dy] != '#':
                    # player and box are adjacent
                    seen.add((br + dx, bc + dy, sr + dx, sc + dy))
                    heapq.heappush(q, (d+1, br + dx, bc + dy, sr + dx, sc + dy))
                elif (br, bc, sr + dx, sc + dy) not in seen and grid[sr+dx][sc+dy] != '#':
                    seen.add((br, bc, sr + dx, sc + dy))
                    heapq.heappush(q, (d, br, bc, sr + dx, sc + dy))
        
        
        return -1       
```


