typedef complex<dl> cd;
typedef vector<cd> vcd;

void fft ( vcd &a, bool invert )
{
    int n = sz ( a );

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for ( int len = 2; len <= n; len <<= 1 ) {
        dl ang = ( ( 2.0 * PI ) / (dl)len ) * ( invert ? -1 : 1 );
        cd wlen ( cos ( ang ), sin ( ang ) );

        for ( int i = 0; i < n; i += len ) {
            cd  w(1);
            for ( int j = 0; j < ( len >> 1 ); j++ ) {
                cd u = a[i+j], v = w * a[i+j+(len>>1)];
                a[i+j] = u + v;
                a[i+j+(len>>1)] = u - v;
                w *= wlen;
            }
        }
    }

    if ( invert ) {
        for ( int i = 0; i < n; i++ ) {
            a[i] /= n;
        }
    }
}

vl mul ( vi a, vi b )
{
    vcd fa ( all ( a ) ), fb ( all ( b ) );
    int n = 1;
    while ( n  < sz ( a ) + sz ( b ) ) {
        n <<= 1;
    }

    fa.resize ( n ), fb.resize ( n );

    fft ( fa, 0 );
    fft ( fb, 0 );

    for ( int i = 0; i < n; i++ ) {
        fa[i] *= fb[i];
    }

    fft ( fa, 1 );

    vl ret(n+1);
    for ( int i = 0; i < n; i++ ) {
        ret[i] = round ( fa[i].real() );
    }

    return ret;
}

int main()
{
    optimize();

    int t;
    cin >> t;

    while ( t-- ) {
        int n;
        cin >> n;
        vi a(n+1), b(n+1);
        for ( int i = 0; i < n+1; i++ ) cin >> a[i];
        for ( int i = 0; i < n+1; i++ ) cin >> b[i];

        vl ans = mul ( a, b );

        for ( int i = 0; i < (2*n)+1; i++ ) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
