
bool equalTo ( double a, double b ){ if ( fabs ( a - b ) <= eps ) return true; else return false; }

bool notEqual ( double a, double b ){if ( fabs ( a - b ) > eps ) return true; else return false; }

bool lessThan ( double a, double b ){ if ( a + eps < b ) return true; else return false; }

bool lessThanEqual ( double a, double b ){if ( a < b + eps ) return true;   else return false;}

bool greaterThan ( double a, double b ){if ( a > b + eps ) return true;else return false;}

bool greaterThanEqual ( double a, double b ){if ( a + eps > b ) return true;else return false;}

