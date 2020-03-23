///DSU: Path compression + Union by size
///It turns out, that the final amortized time complexity is O(α(n)), where α(n) is the inverse Ackermann function, which grows very slowly. In fact it grows so slowly, that it doesn't exceed 4 for all reasonable n (approximately n<10^600).


int par[10005];
int sz[10005];

int Find(int r)	///Path compression
{
	if( par[r] == r ) return r;
	par[r] = Find(par[r]);
	return par[r];
}

void Union(int a, int b) {	///Union by size of subtrees.
    a = Find(a);
    b = Find(b);
    if (a != b) {
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }
}

int main()
{
    for( int i = 0; i < 10005; ++i ) {
	par[i] = i;
	sz[i] = 1;
    }
}
