#define mx 100001010
long long a[mx / 64 + 200];
int prime[5800000];
int cnt = 0;


void sieveGen( int limit )
{
    limit += 100;
    int sq = sqrt ( limit );

	for (long long i = 3; i <= sq; i += 2) {
		if(!(a[i/64]&(1LL<<(i%64)))) {
			for(long long j = i * i; j <= limit; j += 2 * i) {
				a[j/64] |= (1LL<<(j%64));
			}
		}
	}

	prime[cnt++] = 2;
	for (long long i = 3; i <= limit; i += 2) {
		if(!(a[i / 64] & (1LL << (i % 64)))) {
			prime[cnt++] = i;
		}

	}

}
