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
        int n;
        cin >> n;
        cout << "Case " << tc << ": " << (n - 1) << "/1" << endl;
    }
    return 0;
}

