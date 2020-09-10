struct simpleHash{
    vector<long long>p;
    vector<long long>h;

    long long base,mod,len;

    simpleHash(){}
    simpleHash(string &str, long long b, long long m){
        //0 base index array.
        base=b; mod=m; len=str.size();
        p.resize(len,1);
        h.resize(len+1,0);

        for(int i=1;i<len;i++)p[i]=(p[i-1]*base)%mod;
        for(int i=1;i<=len;i++)h[i]=(h[i-1]*base+(str[i-1]-'a'+3))%mod;
    }

    long long rangeHash(int l,int r){   //l and r inclusive
        return  (h[r+1]-((h[l]*p[r-l+1])%mod)+mod)%mod;
    }
};


struct doubleHashing{
    simpleHash h1,h2;

    doubleHashing(string &str){
        h1=simpleHash(str,43, (long long)1e9+7);
        h2=simpleHash(str,97, (long long)1e9+7);
    }

    long long rangeHash(int l,int r){
        return (h1.rangeHash(l,r)<<32LL)^h2.rangeHash(l,r);
    }
};

//***Double Hashing***


int pw[123], hash_s[123];

int main()
{
    optimize();

    string s = "asdf";
    doubleHashing d = doubleHashing( s );
    cout << d.rangeHash( 0, sz ( s ) );

    ///Normal Hashing :

    int p = 31; /// Magical primes : 31, 41, 37
    pw[0] = 1;
    for ( int i = 1; i <= 12; i++ ) {
        pw[i] = ( p * pw[i-1] ) % MOD;
    }

    hash_s[0] = ( s[0] - 'a' )+1;
    for ( int i = 1; i < sz(s); i++ ) hash_s[i] = ( hash_s[i-1] + ( pw[i] * ( s[i] - 'a' + 1 ) ) ) % MOD;



    return 0;
}
