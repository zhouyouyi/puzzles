#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
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

typedef long long ll_t;

const static ll_t inf     = std::numeric_limits<ll_t>::max();

struct edge_t
{
    ll_t dist;
    int node;
    
    edge_t() : dist(inf) {}
};

bool GT(const edge_t * a, const edge_t * b)
{
    return a->dist > b->dist;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--)
    {
        int N, M, S;
        
        cin >> N >> M;
        
        vector< unordered_set<int> > nb(N+1);
        vector< vector<int> > cost(N+1, vector<int>(N+1, -1));
        vector<edge_t*> distance(N+1);
        vector<edge_t*> heap;
        
        int i, j;
        for(i = 0; i < M; ++i)
        {
            int a,b,c;
            cin >> a >> b >> c;
            
            cost[a][b] = (cost[a][b] == -1 ? c : min(cost[a][b], c));
            cost[b][a] = cost[a][b];
            
            nb[a].insert(b);
            nb[b].insert(a);
        }
        
        for(i = 1; i <= N; ++i)
        {
            distance[i] = new edge_t;
            distance[i]->node = i;
            
            heap.push_back(distance[i]);
        }
        
        cin >> S;
        
        distance[S]->dist = 0;
        
        std::make_heap(heap.begin(), heap.end(), GT);
        
        while(heap.size() > 0)
        {
            edge_t * e = heap.front();
            
            std::pop_heap(heap.begin(), heap.end(), GT);
            heap.pop_back();
                        
            if(e->dist == inf) { continue ;}
            
            for(int c : nb[e->node])
            {
                i = c;
                if(distance[i]->dist > distance[e->node]->dist + cost[e->node][i])
                {
                    distance[i]->dist = distance[e->node]->dist + cost[e->node][i];
                }
            }
            
            std::make_heap(heap.begin(), heap.end(), GT);
        }
        
        for(i = 1; i <= N; ++i)
        {
            if(i != S)
            {
                cout << ( distance[i]->dist == inf ? -1 : distance[i]->dist ) << ' ';
            }
            
            delete distance[i];
        }
        
        cout << endl;
    }
    return 0;
}
