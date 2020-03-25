const int INF = 2147483647;
const int MAX = 5005;
int D[MAX], N; // Keeps minimum distance to each node
vector<pair<int,int>> E[MAX]; // Adjacency list

void dijkstra()
{
    for(int i = 1; i <= N; i++) D[i] = INF;
    D[1] = 0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    q.push({0,1});

    while(!q.empty())
    {
        pair<int,int> p = q.top();
        q.pop();

        int u = p.second, dist = p.first;
        if(dist > D[u]) continue;

        for(pair<int,int> pr : E[u])
        {
            int v = pr.first;
            int next_dist = dist + pr.second;

            if(next_dist < D[v])
            {
                D[v] = next_dist;
                q.push({next_dist,v});
            }
        }
    }
}
