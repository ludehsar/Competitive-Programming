///Complexity for each query: O(3*klogk) ~ O(klogk); k is the number of special nodes in each query;

/**
-Before approaching a virtual tree problem you must be able to understand this code!!!! This code is very easy. This code can be revised in 5 minutes(worst case maybe?)
-But no need to understand the logic of why the code is written that way.
**/

/**
**Brief explanation of the code**

For each query:
1. sort the nodes according to their dfs starting time
2. find the lca of the adjacent nodes and insert them to the same container
3. sort the nodes again according to their dfs starting time
4. edge banao
**/

/**
-if two nodes u and v belongs to an auxiliary tree then lca(u,v) also belongs to that auxiliary tree.
-for each query: for k special nodes there will be highest 2*k-1 nodes in the auxiliary tree.
**/

const int mx = 1e5+5;	///max no. of nodes;

/************LCA code needed here**********/

bool cmp( const int &lhs, const int &rhs ) {
  return tin[lhs] < tin[rhs]; /// tin is the starting dfs time of a node
}

vi aux[mx];	///auxiliary tree

int main() {
  /**
    Problem:
    You will be given a tree.
    You will be given many queries. In each query you will be given k special nodes. Now build an auxiliary tree out of these k special nodes.
    Constraints:
    Summation of k over all queries does not exceed 10^5
  **/
  int q; ///queries;
  cin >> q;
  while(q--) {
    int k; ///how many special nodes?
    cin >> k;
    vector<int> special; ///this contains the special nodes;
    for( int i = 0; i < k; ++i ) {
      int node;
      cin >> node;
      special.PB(node);
    }

    /**Node selection for the auxiliary tree - start**/
    sort( special.begin(), special.end(), cmp ); ///sort the nodes according to their starting dfs time;
    special.erase( unique(special.begin(), special.end()), special.end() );
    for( int i = special.size()-1; i > 0; --i ) {
      special.PB( lca( special[i-1], special[i] ) );
    }
    sort( special.begin(), special.end(), cmp ); ///sort the nodes according to their starting dfs time;
    special.erase( unique(special.begin(), special.end()), special.end() );
    /**Node selection for the auxiliary tree - end**/

    /**Edge selection for the auxiliary tree - start**/
    for( auto node : special ) {
      aux[node].clear(); ///clearing the auxiliary tree graph
    }
    stack<int> st;
    st.push(special[0]);
    for( int i = 1; i < special.size(); ++i ) {
      while( !is_ancestor(st.top(), special[i]) ) st.pop();
      int u = st.top(), v = special[i];
      aux[u].PB(v);
      aux[v].PB(u);
      st.push(special[i]);
    }
    /**Edge selection for the auxiliary tree - end**/

    /**Thus aux contains the auxiliary tree graph**/
  }
}
