#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MOD 1000000007

#define optimize() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define fraction() cout.unsetf(ios::floatfield); cout.precision(10); cout.setf(ios::fixed, ios::floatfield);
#define file() freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);

inline void normal(ll &a) { a %= MOD; (a < 0) && (a += MOD); }
inline ll modMul(ll a, ll b) { a %= MOD; b %= MOD; normal(a); normal(b); return (a * b) % MOD; }
inline ll modAdd(ll a, ll b) { a %= MOD; b %= MOD; normal(a); normal(b); return (a + b) % MOD; }
inline ll modSub(ll a, ll b) { a %= MOD; b %= MOD; normal(a); normal(b); a -= b; normal(a); return a; }
inline ll modPow(ll b, ll p) { ll r = 1LL; while (p) { if (p & 1) r = modMul(r, b); b = modMul(b, b); p >>= 1; } return r; }
inline ll modInverse(ll a) { return modPow(a, MOD - 2); }
inline ll modDiv(ll a, ll b) { return modMul(a, modInverse(b)); }

const int mxN = 1e6 + 123;

int N, Q;
map<int, int> Map[mxN];
bool mark[mxN];
vector< pair<int, int> > vec[mxN];
vector<int> st[mxN], en[mxN];
vector<ll> arr;

void sieve() {
    for (int i = 2; i < mxN; ++i) {
        if (mark[i]) continue;
        for (int j = i; j < mxN; j += i) {
            mark[j] = 1;
            int tmp = j, cnt = 0;
            while (tmp % i == 0) {
                tmp /= i;
                cnt++;
            }
            vec[j].push_back({i, cnt});
        }
    }
}

int main() {
    optimize();
    sieve();
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        arr.clear();
        cin >> N >> Q;
        for (int i = 0; i < Q; ++i) {
            int L, R;
            ll X;
            cin >> L >> R >> X;
            st[L].push_back(X);
            en[R].push_back(X);
        }
        ll ans = 1LL;
        for (int i = 1; i <= N; ++i) {
            for (int x : st[i]) {
                for (pair<int, int> v : vec[x]) {
                    int p = v.first;
                    int now = v.second;
                    int prev = 0;
                    if (!Map[p].empty()) {
                        auto it = Map[p].rbegin();
                        if (it->first < now) {
                            prev = it->first;
                            ans = modMul(ans, modPow(ll(p), ll(now - prev)));
                        }
                    }
                    else {
                        ans = modMul(ans, modPow(ll(p), ll(now)));
                    }
                    ++Map[p][now];
                }
            }
            arr.push_back(ans);
            for (int x : en[i]) {
                for (pair<int, int> v : vec[x]) {
                    int p = v.first;
                    int now = v.second;
                    bool ok = 0;
                    if (!Map[p].empty()) {
                        auto it = Map[p].rbegin();
                        if (it->first == now) ok = 1;
                        --Map[p][now];
                        if (Map[p][now] == 0) Map[p].erase(now);
                        if (ok) {
                            ans = modDiv(ans, modPow(ll(p), ll(now)));
                        }
                    }
                    if (ok && !Map[p].empty()) {
                        ans = modMul(ans, modPow(ll(p), ll((Map[p].rbegin())->first)));
                    }
                }
            }
            st[i].clear();
            en[i].clear();
        }
        cout << "Case " << tc << ":";
        for (int i = 0; i < N; ++i) cout << " " << arr[i];
        cout << endl;
    }
    return 0;
}
