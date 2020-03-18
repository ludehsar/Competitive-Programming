///mod inverse from 1 to N
///Complexity: O(N)


const int mx = 100005;
ll inv[mx];

void generate_modinv()
{
	inv[1] = 1;
	for( int i = 2; i < mx; i++ ) {
		inv[i] = (-(MOD/i) * inv[MOD%i] ) % MOD;
		inv[i] = inv[i] + MOD;
	}
}
