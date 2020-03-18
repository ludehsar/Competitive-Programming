// complexity: O(lgN)
// checked. OK.
// https://codeforces.com/blog/entry/60702
// https://www.hackerearth.com/practice/algorithms/searching/ternary-search/tutorial/
// https://cp-algorithms.com/num_methods/ternary_search.html

// Be careful about choosing the boundary

/**
What is Unimodal function?
-We are given a function f(x) which is unimodal on an interval [l,r]. By unimodal function, we mean one of two behaviors of the function:

 1. The function strictly increases first, reaches a maximum (at a single point or over an interval), and then strictly decreases.

 2. The function strictly decreases first, reaches a minimum, and then strictly increases.
**/

/// Ternary search on function f

/**
	This part is an unproven concept. Invented by me. Use it at your own risk.

	If the extrema of the unimodal function is a segment instead of a point
	then to get the leftmost or rightmost extremum return value of the
	function we may consider adding >= instead of > in the "if(  )" part of
	the code only if necessary.
**/

// Finding the minimum function (doubles precision)

int steps = 200;

void ternary_search()
{
	double lo = -inf, hi = inf, mid1, mid2;
	for(int i = 0; i < steps; i++) {
		mid1 = (lo*2+hi) / 3.0;
		mid2 = (lo+2*hi) / 3.0;
		if(f(mid1) > f(mid2)) lo = mid1;
		else hi = mid2;
	}
    double ans = f(lo);
	return ans;
}


// Finding the maximum function (doubles precision)

void ternary_search()
{
	double lo = -inf, hi = inf, mid1, mid2;
	for(int i = 0; i < steps; i++) {
		mid1 = (lo*2+hi) / 3.0;
		mid2 = (lo+2*hi) / 3.0;
		if(f(mid1) > f(mid2)) hi = mid2;
		else lo = mid1;
	}
    double ans = f(lo);
	return ans;
}


// Finding the minimum function (search on integer range)

void ternary_search()
{
	int lo = -inf, hi = inf, mid1, mid2;
	while(hi - lo > 4) {
		mid1 = (lo + hi) / 2;
		mid2 = (lo + hi) / 2 + 1;
		if(f(mid1) > f(mid2)) lo = mid1;
		else hi = mid2;
	}
	ans = inf;
	for(int i = lo; i <= hi; i++) ans = min(ans , f(i));
}


// Finding the maximum function (search on integer range)

void ternary_search()
{
	int lo = -inf, hi = inf, mid1, mid2;
	while(hi - lo > 4) {
		mid1 = (lo + hi) / 2;
		mid2 = (lo + hi) / 2 + 1;
		if(f(mid1) > f(mid2)) hi = mid2;
		else lo = mid1;
	}
	ans = inf;
	for(int i = lo; i <= hi; i++) ans = min(ans , f(i));
}













