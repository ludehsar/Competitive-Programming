const int mx = 2e5+123;
ll t[mx*3], a[mx], prop[3*mx];
bool vis[3*mx];

int baseArry[mx], basePos[mx], chainNO, chainHead[mx], parent[mx], level[mx], chainInd[mx], ptr, p[mx][40], sz[mx];
vii adj[mx];

void shift ( int id, int b, int e )
{
    int mid = ( b + e ) >> 1;
    t[id*2] += ( mid-b+1 * prop[id] );
    t[id*2+1] += ( e-(mid+1)+1 * prop[id] );

    prop[id*2] += prop[id];
    prop[id*2+1] += prop[id];

    vis[id*2] = vis[id*2+1] = 1;
    prop[id] = vis[id] = 0;
}

void init ( int id, int b, int e )
{
    if ( b == e ) {
        t[id] = baseArry[b];
        return;
    }

    int mid = ( b + e ) >> 1;

    init ( id*2, b, mid );
    init ( id*2+1, mid+1, e );

    t[id] = t[id*2] + t[id*2+1];
}

void upd ( int id, int b, int e, int i, int j, ll val )
{
    if ( b > j || e < i ) return;
    if ( b >= i && e <= j ) {
        t[id] += ( val * e-b+1 );
        prop[id] += ( prop[id] * val );
        vis[id] = 1;
        return;
    }

    if ( vis[id] ) shift ( id, b, e );
    int mid = ( b + e ) >> 1;

    upd ( id*2, b, mid, i, j, val );
    upd ( id*2+1, mid+1, e, i, j, val );

    t[id] = t[id*2] + t[id*2+1];
}

ll ask ( int id, int b, int e, int i, int j )
{
    if ( b > j || e < i ) return 0;
    if ( b >= i && e <= j ) return t[id];

    if ( vis[id] ) shift ( id, b, e );
    int mid = ( b + e ) >> 1;

    ll ret1 = ask ( id*2, b, mid, i, j );
    ll ret2 = ask ( id*2+1, mid+1, e, i, j );

    return ret1 + ret2;
}

int dfs ( int u, int lev )
{
    int ret = 1;
    level[u] = lev;
    for ( auto v : adj[u] ) {
        if ( parent[u] != v.F ) {
            parent[v.F] = u;
            ret += dfs ( v.F, lev+1 );
        }
    }

    sz[u] = ret;
    return ret;
}


void HLD ( int u, int cost, int pU )
{
    if ( chainHead[chainNO] == -1 ) {
        chainHead[chainNO] = u;
    }

    chainInd[u] = chainNO;
    basePos[u] = ++ptr;
    baseArry[ptr] = cost;

    int m = -1, id = -1, c = -1;

    for ( auto v : adj[u] ) {
        if ( v.F != pU ) {
            if ( sz[v.F] > m ) {
                m = sz[v.F];
                id = v.F;
                c = v.S;
            }
        }
    }


    if ( id != -1 ) HLD ( id, c, u );

    for ( auto v : adj[u] ) {
        if ( v.F != pU && v.F != id ) {
            chainNO++;
            HLD ( v.F, v.S, u );
        }
    }
}

void preprocess ( int n )
{
    for ( int i = 1; i <= n; i++ ) p[i][0] = parent[i];

    for ( int j = 1; (1 << j) <= n; j++ ) {
        for ( int i = 1; i <= n; i++ ) {
            if ( p[i][j-1] != -1 ) p[i][j] = p[p[i][j-1]][j-1];
        }
    }
}

int LCA ( int u, int v )
{
    if ( level[u] < level[v] ) swap ( u, v );

    int dist = level[u] - level[v];

    int rise;
    while ( dist > 0 ) {
        rise = log2( dist );
        u = p[u][rise];
        dist -= ( 1 << rise );
    }

    if ( u == v ) return u;

    for ( int i = 20; i >= 0; i-- ) {
        if ( p[u][i] != p[v][i] && p[u][i] != -1 ) {
            u = p[u][i];
            v = p[v][i];
        }
    }

    return parent[u];
}


void query_upd ( int u, int v, ll val )
{
    if ( u == v ) return;
    int chainU, chainV = chainInd[v];

    while ( 1 ) {
        chainU = chainInd[u];
        if ( chainU == chainV ) {
            upd ( 1, 1, ptr, basePos[v]+1, basePos[u], val );
            break;
        }

        upd ( 1, 1, ptr, basePos[chainHead[chainU]], basePos[u], val );
        u = chainHead[chainU];
        u = parent[u];
    }

    return;
}


void queryUpd ( int u, int v, ll val )
{
    int lca = LCA ( u, v );
    query_upd ( u, lca, val );
    query_upd ( v, lca, val );
}



ll query_ask ( int u, int v )
{
    if ( u == v ) return 0;
    int chainU, chainV = chainInd[v];
    ll ans = 0;

    while ( 1 ) {
        chainU = chainInd[u];
        if ( chainU == chainV ) {
            ans += ask ( 1, 1, ptr, basePos[v]+1, basePos[u] );
            break;
        }

        ans += ask ( 1, 1, ptr, basePos[chainHead[chainU]], basePos[u] );
        u = chainHead[chainU];
        u = parent[u];
    }

    return ans;
}

ll queryAsk ( int u, int v )
{
    int lca = LCA ( u, v );
    return query_ask ( u, lca ) + query_ask ( v, lca );
}



int main()
{
    optimize();

    int n;

    ptr = 0, chainNO = 1;
    mem ( p, -1 );
    mem ( chainHead, -1 );


    dfs ( 1, 0 );
    HLD ( 1, 0, -1 );
    preprocess( n );
    init ( 1, 1, ptr );

    return 0;
}
