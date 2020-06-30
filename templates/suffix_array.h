namespace suffix_array {

   // sort vector "p" based on the values in array "c"
   // O(n) time
   void count_sort(vector<int>& p, const vector<int>& c) {
      int n = p.size();
      assert(p.size() == c.size());
      vector<int> cnt(n);
      for(int x : p) {
         ++cnt[c[x]];
      }
      vector<int> pos(n);
      pos[0] = 0;
      for(int i = 1; i < n; i++) {
         pos[i] = pos[i-1] + cnt[i-1];
      }
      vector<int> new_p(n);
      for(int x : p) {
         new_p[pos[c[x]]] = x;
         ++pos[c[x]];
      }
      p.swap(new_p);
   }
   
   // returns suffix array of given string s 
   // appends a "$" to the end of s, LENGTH++
   // O(nlogn) time
   vector<int> build_sa(string& s) {
      s += "$";
      int n = s.length();
      vector<int> p(n), c(n);
      {
         vector<pair<char,int>> a(n);
         for(int i = 0; i < n; i++) {
            a[i] = make_pair(s[i], i);
         }
         sort(a.begin(), a.end());
         for(int i = 0; i < n; i++) {
            p[i] = a[i].second;
         }
         c[p[0]] = 0;
         for(int i = 1; i < n; i++) {
            if(a[i].first == a[i-1].first) {
               c[p[i]] = c[p[i-1]];
            } else {
               c[p[i]] = c[p[i-1]] + 1;
            }
         }
      }
      int k = 0;
      while((1<<k) < n) {
         for(int i = 0; i < n; i++) {
            p[i] = (p[i] - (1<<k) + n) % n;
         }
         count_sort(p, c);
         vector<int> new_c(n);
         new_c[p[0]] = 0;
         for(int i = 1; i < n; i++) {
            pair<int,int> prev = make_pair(c[p[i-1]], c[(p[i-1] + (1<<k))%n]);
            pair<int,int> now = make_pair(c[p[i]], c[(p[i] + (1<<k))%n]);
            if(now == prev) {
               new_c[p[i]] = new_c[p[i-1]];
            } else {
               new_c[p[i]] = new_c[p[i-1]] + 1;
            }
         }
         c.swap(new_c);
         ++k;
      }
      return p;
   }
   
   // returns lcp array from suffix array, stores suffix array in "p"
   // lcp[i] = length of longest common prefix between strings "i" and "i-1" in suffix array
   // indices are from [1, ..., n-1]
   // O(n) time for "lcp", O(nlogn) time for "p"
   vector<int> build_lcp(string& s, vector<int>& p) {
      p = build_sa(s);
      int n = s.length();
      vector<int> lcp(n);
      vector<int> c(n);
      for(int i = 0; i < n; i++) {
         c[p[i]] = i;
      }
      int k = 0;
      for(int i = 0; i < n-1; i++) {
         int pi = c[i];
         int j = p[pi - 1];
         while(s[i + k] == s[j + k]) ++k;
         lcp[pi] = k;
         k = max(k-1, 0);
      }
      return lcp;
   }
} // namespace suffix_array
