/*
  ID: zhou.yo1
  PROG: holstein
  LANG: C++
*/

#define PROG "holstein"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

vector< vector<int> > scoops;

vector<int> diet;

void answer( vector<int>& rem, vector< vector<int> >& scoops, int start, vector<int>& ans )
{
    int i, j;
    for(i = start; i < scoops.size(); ++i)
    {
        bool left = false;
        ans.push_back(i);
        for(j = 0; j < scoops[i].size(); ++j)
        {
            rem[j] -= scoops[i][j];
            if( rem[j] > 0 ) left = true;
        }

        if( ! left )
        {
            if( diet.empty() || diet.size() > ans.size() )
            {
                diet = ans;
            }
        }
        else
        {
            answer( rem, scoops, i+1, ans );
        }

        for(j = 0; j < scoops[i].size(); ++j)
        {
            rem[j] += scoops[i][j];
        }

        ans.pop_back();
    }
}

void solve( istream& fin, ostream& out )
{
    int V, G, i, j;

    fin >> V;
    vector<int> R(V);
    for(i = 0; i < V; ++i)
    {
        fin >> R[i];
    }

    fin >> G;
    scoops.resize(G+1);
    for(i = 1; i <= G; ++i)
    {
        scoops[i].resize(V);
        for(j = 0; j < V; ++j)
        {
            fin >> scoops[i][j];
        }
    }

    vector<int> ans;

    answer( R, scoops, 1, ans );

    out << diet.size() << ' ';
    for(i = 0; i < diet.size(); ++i)
    {
        out << diet[i];
        if( i != diet.size()-1 )
            out << ' ';
    }
    out << endl;
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

#ifdef LOCAL
  solve( cin, cout );
#else
  solve( fin, out );
#endif

  return 0;
}
