const int MAXN = 100*1000+5;
const int mod = 1000*1000*1000+7;

int mul(int a, int b) { return 1LL * a * b % mod; }
void fix(int& a) { while(a < 0) a += mod; while(a >= mod) a -= mod; }
int add(int a, int b) { fix(a), fix(b), a += b; fix(a); return a; }
int mpow(int a, int n) {
    if(n == 0) return 1;
    int x = mpow(a, n/2); x = mul(x, x); if(n&1) x = mul(x, a);
    return x;
}

// assumes LOWERCASE latin letters
template<int p1, int p2>
class StringHash {
public:
    StringHash() { init(); }
    StringHash(string _s) {
        s = deque<char>(_s.begin(), _s.end());
        int n = s.size();
        init();
        for(int i = 0; i < 2; i++) for(int j = 0; j < n; j++) { h[i] = add(h[i], mul(_s[j]-'a'+1, ppow[i][j])); } }

    void init() {
        memset(h, 0, sizeof h);
        for(int i = 0; i < 2; i++) { ppow[i].resize(MAXN), pinv[i].resize(MAXN); } 
        ppow[0][0] = ppow[1][0] = pinv[0][0] = pinv[1][0] = 1;
        pinv[0][1] = mpow(p[0], mod-2), pinv[1][1] = mpow(p[1], mod-2);
        for(int i = 0; i < 2; i++) { for(int j = 1; j < MAXN; j++) {
            ppow[i][j] = mul(ppow[i][j/2], ppow[i][j/2]);
            if(j&1) ppow[i][j] = mul(ppow[i][j], p[i]);
            if(j==1) continue;
            pinv[i][j] = mul(pinv[i][j/2], pinv[i][j/2]);
            if(j&1) pinv[i][j] = mul(pinv[i][j], pinv[i][1]); } } }

    bool operator ==(const StringHash& rhs) const { for(int i = 0; i < 2; i++) { if(h[i] != rhs.h[i]) return false; } return true; }
    bool operator !=(const StringHash& rhs) const { return !(*this == rhs); }
    size_t size() const { return s.size(); }
    
    void push_back(char c) {
        int n = s.size();
        for(int i = 0; i < 2; i++) { h[i] = add(h[i], mul(c-'a'+1, ppow[i][n])); }
        s.push_back(c); }
        
    void pop_back() {
        assert(!s.empty());
        int n = s.size()-1;
        char c = s.back();
        for(int i = 0; i < 2; i++) { h[i] = add(h[i], -mul(c-'a'+1, ppow[i][n])); }
        s.pop_back(); }
        
    void push_front(char c) {
        for(int i = 0; i < 2; i++) { h[i] = mul(h[i], ppow[i][1]), h[i] = add(h[i], c-'a'+1); }
        s.push_front(c); }
    
    void pop_front() {
        assert(!s.empty());
        char c = s.front();
        for(int i = 0; i < 2; i++) { h[i] = add(h[i], -(c-'a'+1)), h[i] = mul(h[i], pinv[i][1]); }
        s.pop_front(); }

private:
    deque<char> s;
    int p[2] = {p1, p2}, h[2];
    vector<int> ppow[2], pinv[2];
};

using Hash = StringHash<29, 31>;
