1. If N = ( p1^a1 ) * ( p2^a2 ) * ... * ( pN^aN )then NOD ( N ) = ( a1+1 ) * ( a2+1 ) * ... * ( aN+1 )
2. If N = ( p1^a1 ) * ( p2^a2 ) * ... * ( pN^aN )then, SOD( N ) = ( ( p1^( a1+1 )) - 1) / (p1-1) *...* ( ( pN^( aN+1 )) - 1) / (pN-1)

1. If M & N are co-prime then the formula holds :: [ Phi ( M ) * Phi ( N ) = Phi ( M*N ) ]
2. The Numbers( a ) less than or Equal to N  who all have [ gcd( a,N ) = d ] will be Phi( N/d )
3. ( sum of all the [ Phi( d ) ) = N ] ; where d represents all the divisors of N
4. For N>2 Phi(N) is always Even
5. Sum of all the Numbers less than or Equal to N that are Co Prime with N is  [ N * Phi( N ) / 2 ]
6.[ Lcm( 1 , n ) + Lcm( 2 , n ) + . . . + Lcm ( 1 , n ) = ( n / 2 ) * (  (sum of all Phi( d ) * d) + 1 ) ]; d is the divisors of n

1. Mod Inverse can be solved recursively with the following formula :: inv[ a ] = (-Floor( Mod / A ) * inv[ Mod%A ] + Mod) %Mod

1. logB(x) = ( logC(x) / logC(B) ) , [ Here , logB(x) means log(x) based B] ;
2. What does log10(X) means? 10^(fractional part of the result) means the leading digit!!!
3. lgamma(x) = log(1)+...log(x-1) // this is like magic!!
