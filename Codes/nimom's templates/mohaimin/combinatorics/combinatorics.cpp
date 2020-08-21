1. nCr = nC(r-1) * ((n-r+1)/r)
2. nCr = (n-1)Cr + (n-1)C(r-1)
3. nC0+nC2+nC4+.... = nC1+nC3+nC5.... = 2^(n-1)
4. summation of x*nCx such that (1 <= x <= n or 0 <= x <= n) = n*2^(n-1). (easy to prove). 

1. Catalan Number(1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190)
  1.1 Catn = (1/(n+1))*((2n)Cn)
  1.2 Catn = summation of Cat(k-1)*Catk(n-k) such that 1 <= k <= n
  1.3 Cat(n+1) = ((2*(2n+1))/(n+2)) * Catn

