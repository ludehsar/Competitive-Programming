//https://codeforces.com/blog/entry/44351

Hi!

Most of the people know about dsu but what is the "dsu on tree"?

In Iran, we call this technique "Guni" (the word means "sack" in English), instead of "dsu on tree".

I will explain it and post ends with several problems in CF that can be solved by this technique.

What is the dsu on tree?
With dsu on tree we can answer queries of this type:

How many vertices in the subtree of vertex v has some property in  time (for all of the queries)?

For example:

Given a tree, every vertex has color. Query is how many vertices in subtree of vertex v are colored with color c?

Let's see how we can solve this problem and similar problems.

First, we have to calculate the size of the subtree of every vertice. It can be done with simple dfs:

int sz[maxn];
void getsz(int v, int p){
    sz[v] = 1;  // every vertex has itself in its subtree
    for(auto u : g[v])
        if(u != p){
            getsz(u, v);
            sz[v] += sz[u]; // add size of child u to its parent(v)
        }
}
Now we have the size of the subtree of vertex v in sz[v].

The naive method for solving that problem is this code(that works in O(N ^ 2) time)

int cnt[maxn];
void add(int v, int p, int x){
    cnt[ col[v] ] += x;
    for(auto u: g[v])
        if(u != p)
            add(u, v, x)
}
void dfs(int v, int p){
    add(v, p, 1);
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    add(v, p, -1);
    for(auto u : g[v])
        if(u != p)
            dfs(u, v);
}
Now, how to improve it? There are several styles of coding for this technique.

1. easy to code but .
map<int, int> *cnt[maxn];
void dfs(int v, int p){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p){
           dfs(u, v);
           if(sz[u] > mx)
               mx = sz[u], bigChild = u;
       }
    if(bigChild != -1)
        cnt[v] = cnt[bigChild];
    else
        cnt[v] = new map<int, int> ();
    (*cnt[v])[ col[v] ] ++;
    for(auto u : g[v])
       if(u != p && u != bigChild){
           for(auto x : *cnt[u])
               (*cnt[v])[x.first] += x.second;
       }
    //now (*cnt[v])[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.

}

2. easy to code and .
vector<int> *vec[maxn];
int cnt[maxn];
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
           mx = sz[u], bigChild = u;
    for(auto u : g[v])
       if(u != p && u != bigChild)
           dfs(u, v, 0);
    if(bigChild != -1)
        dfs(bigChild, v, 1), vec[v] = vec[bigChild];
    else
        vec[v] = new vector<int> ();
    vec[v]->push_back(v);
    cnt[ col[v] ]++;
    for(auto u : g[v])
       if(u != p && u != bigChild)
           for(auto x : *vec[u]){
               cnt[ col[x] ]++;
               vec[v] -> push_back(x);
           }
    //now (*cnt[v])[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    // note that in this step *vec[v] contains all of the subtree of vertex v.
    if(keep == 0)
        for(auto u : *vec[v])
            cnt[ col[u] ]--;
}

3. heavy-light decomposition style .
int cnt[maxn];
bool big[maxn];
void add(int v, int p, int x){
    cnt[ col[v] ] += x;
    for(auto u: g[v])
        if(u != p && !big[u])
            add(u, v, x)
}
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1), big[bigChild] = 1;  // bigChild marked as big and not cleared from cnt
    add(v, p, 1);
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    if(bigChild != -1)
        big[bigChild] = 0;
    if(keep == 0)
        add(v, p, -1);
}

4. My invented style .
This implementation for "Dsu on tree" technique is new and invented by me. This implementation is easier to code than others. Let st[v] dfs starting time of vertex v, ft[v] be it's finishing time and ver[time] is the vertex which it's starting time is equal to time.

int cnt[maxn];
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1);  // bigChild marked as big and not cleared from cnt
    for(auto u : g[v])
	if(u != p && u != bigChild)
	    for(int p = st[u]; p < ft[u]; p++)
		cnt[ col[ ver[p] ] ]++;
    cnt[ col[v] ]++;
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    if(keep == 0)
        for(int p = st[v]; p < ft[v]; p++)
	    cnt[ col[ ver[p] ] ]--;
}

But why it is ? You know that why dsu has  time (for q queries); the code uses the same method. Merge smaller to greater.

If you have heard heavy-light decomposition you will see that function add will go light edges only, because of this, code works in  time.

Any problems of this type can be solved with same dfs function and just differs in add function.
