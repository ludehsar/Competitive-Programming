///mos algorithm
///Complexity: O(sqrt(N) * (N+M))

const int mx = 3e5+5;

const int block_sz = 550;	// N ~ 3e5
int freq[mx], mo_cnt = 0;
int ret[mx];

inline void add(int idx) {
	++freq[a[idx]];
	if(freq[a[idx]] == 1) ++mo_cnt;
}

inline void del(int idx) {
	--freq[a[idx]];
	if(freq[a[idx]] == 0) --mo_cnt;
}

inline int get_ans() {
	return mo_cnt;
}

struct queries {
	int l, r, idx;
	queries() { }
	queries(int _l, int _r, int _i) : l(_l), r(_r), idx(_i) { }
	bool operator < (const queries &p) const {
		if(l/block_sz != p.l/block_sz) return l < p.l;
		return ((l/block_sz) & 1) ? r > p.r : r < p.r;
	}
};

void mo(vector<queries> &q) {
	sort(q.begin(), q.end());
	memset(ret, -1, sizeof ret);

	// l = 1, r = 0 if 1-indexed array
	int l = 0, r = -1;
	for(auto &qq : q) {
		while(qq.l < l) add(--l);
		while(qq.r > r) add(++r);
		while(qq.l > l) del(l++);
		while(qq.r < r) del(r--);
		ret[qq.idx] = get_ans();
	}
}
