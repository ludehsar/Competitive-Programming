const int mx = 2e5+123;
ll t[mx*3], a[mx], prop[3*mx];
bool vis[3*mx];

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
        t[id] = a[b];
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
