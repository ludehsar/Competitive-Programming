///Aho Corasick - O(N); N = sum of lengths of all strings in the set;

/// Vertex means state, state means vertex. They are used interchangeably;
/**
1. Proper suffix of root vertex is the root itself. So its suffix link will point to itself;
2. Suffix link of vertex of depth 1 will point to the root;
3. root vertex is 0;
**/

const int ALPHA = 26; ///max no. of alphabets
struct AhoCorasick{
  struct Vertex {
    int edge[ALPHA]; /// edges indicate letters of alphabet;
    bool leaf = false; /// leaf = true- means this state represents a string of the set;
    int p = -1; /// parent of this state;
    char pch; /// this state's parent ----pch---> this state;
    int link = -1; /// suffix link of this state;	/// link = -1 means suffix link has not been determined;
    int go[ALPHA]; /// go to next state through a char edge;
    Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
      memset( edge, -1, sizeof(edge) );
      memset( go, -1, sizeof(go) );
    }
  };

  vector<Vertex> trie;
  AhoCorasick() : trie(1) {}

  void add_string(string const& s) {
    int node = 0;
    for (char ch : s) {
      int ch_idx = ch - 'a';
      if (trie[node].edge[ch_idx] == -1) {
        trie[node].edge[ch_idx] = trie.size();
        trie.push_back( Vertex(node, ch) );
      }
      node = trie[node].edge[ch_idx];
    }
    trie[node].leaf = true;
  }

  int get_link(int node) { /// get suffix link;
    if (trie[node].link == -1) {
      if (node == 0 || trie[node].p == 0)
        trie[node].link = 0;
      else
        trie[node].link = go(get_link(trie[node].p), trie[node].pch);
    }
    return trie[node].link;
  }

  int go(int node, char ch) {	/// go to next state;
    int ch_idx = ch - 'a';
    if (trie[node].go[ch_idx] == -1) {
      if (trie[node].edge[ch_idx] != -1)
        trie[node].go[ch_idx] = trie[node].edge[ch_idx];
      else
        trie[node].go[ch_idx] = (node == 0) ? 0 : go(get_link(node), ch);
    }
    return trie[node].go[ch_idx];
  }
};
