1. bool equalTo ( double a, double b ){ if ( abs ( a - b ) <= eps ) return true; else return false; }
2. bool notEqual ( double a, double b ){if ( abs ( a - b ) > eps ) return true; else return false; }
3. bool lessThan ( double a, double b ){ if ( a + eps < b ) return true; else return false; }
4. bool lessThanEqual ( double a, double b ){if ( a < b + eps ) return true;   else return false;}
5. bool greaterThan ( double a, double b ){if ( a > b + eps ) return true;else return false;}
6. bool greaterThanEqual ( double a, double b ){if ( a + eps > b ) return true;else return false;}
