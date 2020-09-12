#include "../utility/template.cpp"

const int MAXN = 1e5 + 123;

int n;
ll a[MAXN];
ll seg[MAXN * 4 + 12], prop[MAXN * 4 + 12];

void shift(int id, int s, int e) {
  if (prop[id]) {
    seg[id] += (e - s + 1) * prop[id];
  }
  if (s != e) {
    prop[id * 2] += prop[id];
    prop[id * 2 + 1] += prop[id];
  }
  prop[id] = 0;
}

void init(int id, int s, int e) {
  if (s == e) {
    seg[id] = a[s];
    return;
  }
  int mid = (s + e) / 2;
  init(id * 2, s, mid);
  init(id * 2 + 1, mid + 1, e);
  seg[id] = seg[id * 2] + seg[id * 2 + 1];
}

void update(int id, int s, int e, int l, int r, ll val) {
  shift(id, s, e);
  if (l > e || s > r) return;
  if (l <= s && e <= r) {
    prop[id] += val;
    shift(id, s, e);
    return;
  }
  int mid = (s + e) / 2;
  update(id * 2, s, mid, l, r, val);
  update(id * 2 + 1, mid + 1, e, l, r, val);
  seg[id] = seg[id * 2] + seg[id * 2 + 1];
}

ll query(int id, int s, int e, int l, int r) {
  shift(id, s, e);
  if (l > e || s > r) return 0;
  if (l <= s && e <= r) return seg[id];
  int mid = (s + e) / 2;
  ll ret1 = query(id * 2, s, mid, l, r);
  ll ret2 = query(id * 2 + 1, mid + 1, e, l, r);
  return ret1 + ret2;
}

int main() {
  int m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  mem(prop, 0);
  init(1, 1, n);
  while (m--) {
    int i, l, r;
    cin >> i >> l >> r;
    if (i == 1) {
      int v;
      cin >> v;
      update(1, 1, n, l, r, v);
    }
    else {
      cout << query(1, 1, n, l, r) << endl;
    }
  }
  return 0;
}
