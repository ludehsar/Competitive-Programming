
///Unique vector
sort(vec.begin(), vec.end());
vec.erase( unique( vec.begin(), vec.end() ), vec.end() );

///bit manipulation
inline bool checkBit(ll n, int i) { return n&(1LL<<i); }
inline ll setBit(ll n, int i) { return n|(1LL<<i);; }
inline ll resetBit(ll n, int i) { return n&(~(1LL<<i)); }

///dir array
int dx[] = {0, 0, +1, -1};
int dy[] = {+1, -1, 0, 0};
//int dx[] = {+1, 0, -1, 0, +1, +1, -1, -1};
//int dy[] = {0, +1, 0, -1, +1, -1, +1, -1};


///constructor overwriting
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

///substring copy(Very fast. faster than hand-made custom. can avoid TLE)
string s;
s.substr(idx); //copy substring of range [idx, s.size()-1]
s.substr(idx, x); //copy substring of range [idx, idx+x-1]


///priority queue in ascending order
priority_queue<int, vector<int>, greater<int> > pq;

///random number generator
mt19937 rng((unsigned)chrono::system_clock::now().time_since_epoch().count()); //mt199937_64 for ll (**use this above main function**)

shuffle( vec.begin(), vec.end(), rng );	///shuffles a vector
int temp = rng();	///generates a random number

