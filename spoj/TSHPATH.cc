// C++11

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
Dijkstra Algothrim:

for all v in V:
    distance(v) = inf
    visited(v) = false
   
distance(s) = 0

while visited nodes < total nodes:
    n = select from the unvisited nodes that has the minimum distance(i)
    visited(n) = true
    if(distance(n) == inf):
        continue; // unconnected part
    for all j in n's neighbours:
        if(distance(j) > distance(n) + cost(n,j)):
            distance(j) = distance(n) + cost(n,j)
*/

const static int inf = std::numeric_limits<int>::max();

unordered_map<string, int> city;
unordered_set<int> adj[10001];

int cost[10001][10001];

struct edge_t
{
    int dist;
    int node;

    edge_t(int n) : dist(inf), node(n) {}
};

bool GT(const edge_t* a, const edge_t* b)
{
    return a->dist > b->dist;
}

vector<edge_t*> E(10001, NULL);

int shortest_path( const string& q1, const string& q2, int N )
{
    int s = city[q1];
    int e = city[q2];

    vector<edge_t*> heap;
    vector<bool> done(N+1, false);

    int i;
    for(i = 1; i <= N; ++i)
    {
        if( E[i] == NULL )
            E[i] = new edge_t(i);
        E[i]->dist = inf;
        E[i]->node = i;

        heap.push_back(E[i]);
    }

    E[s]->dist = 0;

    make_heap( heap.begin(), heap.end(), GT );

    while( heap.size() > 0 )
    {
        edge_t* r = heap.front();

        pop_heap( heap.begin(), heap.end(), GT );
        heap.pop_back();

        done[r->node] = true;

        if(r->dist == inf) continue;

        for( int c : adj[r->node] )
        {
            E[c]->dist = min( E[c]->dist, E[r->node]->dist + cost[r->node][c] );
        }

        make_heap( heap.begin(), heap.end(), GT );
    }

    return E[e]->dist;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int ncase;

    cin >> ncase;

    while(ncase--)
    {
        memset( cost, 0, sizeof(cost) );

        int N;

        cin >> N;

        int i, nb, j, nr, c;

        string sname, q1, q2;

        for(i = 1; i <= N; ++i)
        {
            cin >> sname >> nb;

            city[sname] = i;

            adj[i].clear();

            for(j = 1; j <= nb; ++j)
            {
                cin >> nr >> c;

                if( cost[i][nr] == 0 )
                    cost[i][nr] = cost[nr][i] = c;
                else
                    cost[i][nr] = cost[nr][i] = min( cost[nr][i], c );

                adj[i].insert( nr );
            }
        }

        int Q;

        cin >> Q;

        for(i = 0; i < Q; ++i)
        {
            cin >> q1 >> q2;

            cout << shortest_path(q1, q2, N) << endl;
        }
    }

    for( int i = 0; i < E.size(); ++i)
    {
        if(E[i]) delete E[i];
    }

    return 0;
}
