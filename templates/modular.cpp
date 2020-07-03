namespace modular {
   const int mod = 1e9+7;
   // const int mod = 998244353;

   inline int add(int a, int b) {
      a += b;
      while(a >= mod) a -= mod;
      while(a < 0) a += mod;
      return a;
   }
   inline void add_self(int& a, int b) {
      a = add(a, b);
   }
   inline int mul(int a, int b) {
      return 1LL * a * b % mod;
   }
   inline void mul_self(int& a, int b) {
      a = mul(a, b);
   }
   inline int mpow(int a, int n) {
      int res = 1;
      while(n > 0) {
        if(n & 1) {
           res = mul(res, a);
        }
        a = mul(a, a);
        n >>= 1;
      }
      return res;
   }
   inline int divide(int a, int b) {
      assert(b != 0);
      return mul(a, mpow(b, mod-2));
   }

   const int mxN = 200*1000+5;
   int fact[mxN], finv[mxN];

   inline int binomial(int n, int k) {
      return mul(fact[n], mul(finv[n-k], finv[k]));
   }
   
   inline void init_fact() {
      fact[0] = finv[0] = 1;
      for(int i = 1; i < mxN; i++) {
         fact[i] = mul(i, fact[i-1]);
         finv[i] = mpow(fact[i], mod-2);
      }
   }
}
