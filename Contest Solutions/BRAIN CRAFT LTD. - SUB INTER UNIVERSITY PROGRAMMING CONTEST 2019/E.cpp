#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define optimize() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define fraction() cout.unsetf(ios::floatfield); cout.precision(10); cout.setf(ios::fixed, ios::floatfield);
#define file() freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);

int main() {
    optimize();
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int p, n, t;
        cin >> p >> n >> t;
        vector<ll> products[p];
        for (int i = 0; i < n; ++i) {
            int ptype;
            ll date;
            cin >> ptype >> date;
            ptype--;
            products[ptype].push_back(date);
        }
        for (int i = 0; i < p; ++i) sort(products[i].begin(), products[i].end());
        vector<ll> trav(t);
        for (int i = 0; i < t; ++i) cin >> trav[i];
        sort(trav.begin(), trav.end());
        ll ans = 0LL;
        bool ok = 1;
        for (int i = 0; i < p; ++i) {
            if (!ok) break;
            int prev = 0;
            for (int j = 0; j < products[i].size(); ++j) {
                int id = lower_bound(trav.begin(), trav.end(), products[i][j]) - trav.begin();
                id = max(id, prev);
                if (id >= t) {
                    ok = 0;
                    break;
                }
                ans = max(ans, trav[id] - products[i][j]);
                prev = id + 1;
            }
        }
        if (!ok) cout << "Case " << tc << ": -1" << endl;
        else cout << "Case " << tc << ": " << ans << endl;
    }
    return 0;
}

