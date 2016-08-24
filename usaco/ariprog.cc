/*
  ID: zhou.yo1
  PROG: ariprog
  LANG: C++
*/

#define PROG "ariprog"

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

set<int> nums;
vector<bool> idx(250*250 + 250*250 +1, false);

bool comp( const pair<int,int>& a, const pair<int,int>& b )
{
    return a.second < b.second || ( a.second == b.second && a.first < b.first );
}

bool is_valid( vector<int>& A, vector<bool>& idx, int start, int k, int N )
{
    for(int i = 1; i < N; i++)
    {
        if( A[start]+k*i >= idx.size() ||  !idx[ A[start]+k*i ] ) return false;
    }

    return true;
}

void solve( ifstream& fin, ofstream& out )
{
    int N, M;
    fin >> N >> M;

    int i, j;
    for(i = 0; i <= M; ++i)
        for(j = i; j <= M; ++j)
            nums.insert(i*i + j*j);

    vector<int> A(nums.begin(), nums.end());

    // cout << A.size() << endl;

    for(i = 0; i < A.size(); ++i)
    {
        idx[A[i]] = true;
    }

    // cout << A.size() << endl;

    vector< pair<int,int> > rs;

    int D = (A.back() - A.front()) / (N-1);

    for(i = 0; i < A.size(); ++i)
    {
        for(j = 1; j <= D; ++j)
        {
            if( is_valid( A, idx, i, j, N ) )
            {
                rs.push_back( make_pair( A[i], j ) );
            }
        }
    }

    if( rs.empty() )
    {
        out << "NONE" << endl;
    }
    else
    {
        sort( rs.begin(), rs.end(), comp );

        for(i = 0; i < rs.size(); ++i)
        {
            out << rs[i].first << " " << rs[i].second << endl;
        }
    }
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

  solve( fin, out );

  return 0;
}
