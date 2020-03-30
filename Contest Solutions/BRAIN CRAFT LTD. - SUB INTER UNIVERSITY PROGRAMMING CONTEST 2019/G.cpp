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
        int k;
        string a, b;
        cin >> k >> a >> b;
        if (a > b) swap(a, b);
        int id1 = -1, id2 = -1;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] == '.') {
                id1 = i;
                break;
            }
        }
        if (id1 == -1) {
            a += '.';
            id1 = a.size() - 1;
        }
        for (int i = 0; i < b.size(); ++i) {
            if (b[i] == '.') {
                id2 = i;
                break;
            }
        }
        if (id2 == -1) {
            b += '.';
            id2 = b.size() - 1;
        }
        while (a.size() < b.size()) a += '0';
        if (id1 != id2) {
            cout << "Case " << tc << ": rejected" << endl;
        }
        else {
            int cnt = 0, pos = 0;
            while (pos < a.size() && a[pos] == b[pos]) {
                if (a[pos++] == '.') continue;
                cnt++;
            }
            cout << "Case " << tc << ": " << (pos >= a.size() || cnt >= k ? "accepted" : "rejected") << endl;
        }
    }
    return 0;
}

