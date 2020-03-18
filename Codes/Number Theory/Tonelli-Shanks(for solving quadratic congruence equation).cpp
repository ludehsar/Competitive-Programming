//solves TIMUS 1132
//can't figure out the time complexity, but its fast

/**
for details-
1. https://www.codechef.com/wiki/tutorial-number-theory#
2. https://www.codechef.com/wiki/tutorial-quadratic-equations#
**/
//This function solves quadratic equation modulo prime p;
//returns -1 if there is no possible solution. i.e the congruence equation is not valid.
//returns an answer(if exists) as integer less than prime p.
//This algorithm may work for prime power moduli (according to wikipedia, but not tested)

//solves x*x == a (mod p);

/**
							***Important notes***
**For even prime moduli(p = 2):
1. There is exactly 1 solution in range [1,p-1]. But when range is not concerned then there are infinite solutions. If a solution is x then the other solutions can be defined as k*p+x or k*p-x where k is any integer. you can prove it by showing that (k*p+x)^2 and x^2 are congruent modulo p or (k*p-x)^2 and x^2 are congruent modulo p.

**For odd prime moduli:
1.If the congruence equation is valid then there are always exactly 2 solutions in range [1, p-1]. if a solution is x(returned by the function) then the other solution is p-x. (Exception: if congruence equation is valid and x = 0 is returned by the function, then p-x = 0. So, even though the congruence equation is valid- there are no solutions in range [1,p-1]. However, if range is not concerned then there are infinitly many solutions.)
2.But, if range is not concerned then there exists infinite solution if the congruence equation is valid. If a solution is x then the other solutions can be defined as k*p+x or k*p-x where k is any integer. you can prove it by showing that (k*p+x)^2 and x^2 are congruent modulo p or (k*p-x)^2 and x^2 are congruent modulo p.

**/

ll expo( ll b, ll power, ll m ) {
    ll res = 1LL, x = b%m;
    while(power) {
        if ( power&1LL ) res = ( res*x ) % m;
        x = ( x*x ) % m;
        power >>= 1LL;
    }
    return res;
}

//solves x*x == a (mod p); [Here, p is prime. We find a possible value of x.]
int solvequadratic(int a, int p)
{
	if(p == 2) {
		if(a&1) return 1;
		return 0;
	}
	if(a > p) a = a%p;
	while(a < 0) a = a+p;
	if(a == 0) return 0;
	if(expo(a,(p-1)/2,p) != 1) return -1;

	int n = 0, k = p-1;
	while(k % 2 == 0) k/=2, n++;
	int q = 2;
	while(expo(q,(p-1)/2,p) != (p-1)) q++;
	int t = expo(a,(k+1)/2,p);
	int r = expo(a,k,p);
	while(true) {
		int s = 1;
		int i = 0;
		while(expo(r,s,p) != 1) i+=1, s*=2;
		if(i == 0) return t;
		int e = 1<<(n-i-1);
		int u = expo(q, k*e,p);
		t = ((long long)t*u)%p;
		r = ((long long)r*u*u)%p;
    }
}
