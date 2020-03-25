const int N = 1e4;

///beware! if k distinct patterns are given having sum of length m then size of ending array and oc array will
///be at most m.sqrt(m) ,But for similar patterns one must act with  them differently
struct aho_corasick
{
	bool  is_end[N];
	int link[N];            ///A suffix link for a vertex p is a edge that points to
                            ///the longest proper suffix of
                            ///the string corresponding to the vertex p.
    int psz = 1;                ///tracks node numbers of the trie
	map<char, int> to[N];   ///tracks the next node
	vector<int> ending[N];           ///ending[i] stores the indexes of patterns which ends
                            ///at node  i(from the trie)
	vector<int> oc[N];               ///oc[i] stores ending index of all occurrences of pattern[i]
                            ///so real oc[i][j]=oc[i][j]-pattern[i].size()+1,0-indexed
	void clear()
	{
		for(int i = 0; i <= psz; i++)
			is_end[i] = 0, link[i] = 0, to[i].clear(),ending[i].clear(),oc[i].clear();

		psz = 1;
		is_end[0] = 1;
	}

	void faho_corasick() {  clear(); }

	void add_word(string s,int idx)
	{
		int u = 0;
		for(char c: s)
		{
			if(!to[u].count(c)) to[u][c] = psz++;
			u = to[u][c];
		}

		is_end[u] = 1;
		ending[u].push_back(idx);
	}

    void populate(int cur)
    {
        /// merging the occurrences of patterns ending  at cur node in  the trie
        for(auto occ: ending[link[cur]])
            ending[cur].push_back(occ);
    }

    void populate(vector<int> &en, int cur)
    {
        /// occurrences of patterns in the given string
        for(auto idx: en)
        {
            oc[idx].push_back(cur);
        }
    }

	void push_links()
	{
		queue<int> q;
		int u, v, j;
		char c;

		q.push(0);
		link[0] = -1;

		while(!q.empty())
		{
			u = q.front();
			q.pop();

			for(auto it: to[u])
			{
				v = it.second;
				c = it.first;
				j = link[u];

				while(j != -1 && !to[j].count(c)) {
                    j = link[j];
				}
				if(j != -1) link[v] = to[j][c];
				else link[v] = 0;

				q.push(v);
				populate(v);
			}
		}
	}

	void traverse(string s)
    {
        int n=s.size();
        int cur=0;///root

        for(int i=0;i<n;i++){
            char c=s[i];
            while(cur!=-1 && !to[cur].count(c)) cur=link[cur];
            if(cur!=-1) cur=to[cur][c];
            else cur=0;
            populate(ending[cur],i);
        }
    }
};

aho_corasick t;

int main()
{

    int T;
    cin >> T;
    for ( int tc = 1; tc <= T; tc++ ) {

        t.faho_corasick();
        string s;
        cin >> s;
        int q;
        cin >> q;


        for ( int k = 1; k <= q; k++ ) {
            string p;
            cin >> p;
            t.add_word( p, k );
        }

        t.push_links();
        t.traverse( s );


        for ( int i = 1; i <= q; i++ ) {
            cout << t.oc[i].size() << endl; /// Ending index of patter i in s
            for ( auto u : t.oc[i] ) cout << u << " ";
            cout << endl;
        }
    }


    return 0;
}
