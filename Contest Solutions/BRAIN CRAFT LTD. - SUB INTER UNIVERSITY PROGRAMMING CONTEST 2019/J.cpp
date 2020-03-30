#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MOD 100019

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

const int inf = 90000000;

int visited[100012];

int main() {
    optimize();
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int n, q;
        cin >> n;
        pair<ll, ll> p[n];
        for (int i = 0; i < 100012; ++i) visited[i] = inf;
        for (int i = 0; i < n; ++i) {
            cin >> p[i].first >> p[i].second;
            normal(p[i].second);
            visited[p[i].first] = p[i].second;
        }
        ll denom[n];
        for (int i = 0; i < n; ++i) {
            denom[i] = 1LL;
            for (int j = 0; j < n; ++j) {
                if (i != j) denom[i] = modMul(denom[i], modSub(p[i].first, p[j].first));
            }
            // cout << denom[i] << " ";
        }
        cin >> q;
        cout << "Case " << tc << ":" << endl;
        while (q--) {
            ll x;
            cin >> x;
            if (visited[x] != inf) {
                cout << visited[x] << endl;
            }
            else {
                ll nom = 1LL;
                for (int i = 0; i < n; ++i) {
                    nom = modMul(nom, modSub(x, p[i].first));
                }
                // cout << nom << endl;
                ll ans = 0LL;
                for (int i = 0; i < n; ++i) {
                    ans = modAdd(ans, modDiv(modMul(p[i].second, nom), modMul(denom[i], modSub(x, p[i].first))));
                }
                cout << ans << endl;
            }
        }
    }
    return 0;
}

/*
1
1
1 5
2
1
2
*/
