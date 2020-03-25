struct frac {
    ll n, d;

    frac(ll _n = 0, ll _d = 1) {
        if ( _d < 0 ) _n = -_n, _d = -_d;
        ll g = gcd ( abs(_n), _d );
        n = _n / g;
        d = _d / g;
    }

    friend frac operator + ( const frac &a, const frac &b ) {
        return frac ( ( a.n * b.d ) + ( b.n * a.d ), ( a.d * b.d ) );
    }

    friend frac operator - ( const frac &a, const frac &b ) {
        return frac ( ( a.n * b.d ) - ( b.n * a.d ), ( a.d * b.d ) );
    }

    friend frac operator * ( const frac &a, const frac &b ) {
        return frac ( ( a.n * b.n ), ( a.d * b.d ) );
    }

    friend frac operator / ( const frac &a, const frac &b ) {
        return frac ( a.n * b.d, b.n * a.d );
    }

    friend bool operator < ( const frac &a, const frac &b ) {
        frac ret = a - b;
        return ret.n < 0;
    }

    friend bool operator > ( const frac &a, const frac &b ) {
        frac ret = a - b;
        return ret.n >= 0;
    }

    friend void swap ( frac &a, frac &b ) {
        frac tmp = b;
        b = a;
        a = tmp;
    }

};



int main()
{

    frac f1 = frac ( 1, 2 ), f2 = frac( 2, 3 );
    frac ans;

    ans = f1 + f2;
    cout << ans.n << " " << ans.d << endl; ///7 6

    ans = f1 - f2;
    cout << ans.n << " " << ans.d << endl; ///-1 6

    ans = f1 * f2;
    cout << ans.n << " " << ans.d << endl; ///1 3

    ans = f1 / f2;
    cout << ans.n << " " << ans.d << endl; ///3 4

    swap ( f1, f2 );
    cout << f1.n << " " << f1.d << endl; ///2 3
    cout << f2.n << " " << f2.d << endl; ///1 2


    if ( f1 > f2 ) cout << "Greater\n";///Greater
    if ( f1 < f2 ) cout << "Smaller\n";///Condition is not true.

    swap( f1, f2 );
    if ( f1 > f2 ) cout << "Greater\n";///Condition is not true.
    if ( f1 < f2 ) cout << "Smaller\n";///Smaller

    return 0;
}
