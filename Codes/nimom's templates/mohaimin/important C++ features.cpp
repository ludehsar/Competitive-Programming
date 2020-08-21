/// 1. Unique vector
sort(vec.begin(), vec.end());
vec.erase( unique( vec.begin(), vec.end() ), vec.end() );

/// 2. bit manipulation
inline bool checkBit(ll n, int i) { return n&(1LL<<i); }
inline ll setBit(ll n, int i) { return n|(1LL<<i);; }
inline ll resetBit(ll n, int i) { return n&(~(1LL<<i)); }

///3. dir array
int dx[] = {0, 0, +1, -1};
int dy[] = {+1, -1, 0, 0};
//int dx[] = {+1, 0, -1, 0, +1, +1, -1, -1};
//int dy[] = {0, +1, 0, -1, +1, -1, +1, -1};


///4. constructor overwriting
struct Vertex {
  int next[K];
  bool leaf = false;
  int p = -1;
  char pch;
  int link = -1;
  int go[K];
  Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
    fill(begin(next), end(next), -1);
    fill(begin(go), end(go), -1);
  }
};

///5. substring copy(Very fast. faster than hand-made custom. can avoid TLE)
string s;
s.substr(idx); //copy substring of range [idx, s.size()-1]
s.substr(idx, x); //copy substring of range [idx, idx+x-1]

///6. priority queue in ascending order
priority_queue<int, vector<int>, greater<int> > pq;

///7. random number generator
mt19937 rng((unsigned)chrono::system_clock::now().time_since_epoch().count()); //mt199937_64 for ll (**use this above main function**)

shuffle( vec.begin(), vec.end(), rng ); ///shuffles a vector
int temp = rng(); ///generates a random number

///8. make map faster
ump.reserve(1<<10);  ump.max_load_factor(0.25);

///9. Architectural improvement. (Use this above header file) (Noticeable incase of bitset)
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

///10. count the number of set bits in a number
__builtin_popcount(num); // for integer;
__builtin_popcountll(num); // for long long;
