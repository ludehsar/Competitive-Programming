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
        int dw, mw, cw, rw;
        cin >> dw >> mw >> cw >> rw;
        int p;
        cin >> p;
        bool ok = 1;
        for (int i = 0; i < p; ++i) {
            int d, m, c;
            cin >> d >> m >> c;
            if (d == dw && m == mw && c == cw && rw == 0) ok = 0;
            else if (d == dw && m == mw && c != cw) ok = 0;
        }
        cout << "Case " << tc << ": " << (ok ? "Yes" : "No") << endl;
    }
    return 0;
}

