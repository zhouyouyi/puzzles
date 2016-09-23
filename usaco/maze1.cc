/*
  ID: zhou.yo1
  PROG: maze1
  LANG: C++
*/

#define PROG "maze1"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

void shortest_path( vector<string>& M, int x, int y, vector< vector<int> >& D )
{
    vector< vector<bool> > visited( D.size(), vector<bool>( D.front().size(), false ) );
    int i, j;
    for(i = 0; i < D.size(); ++i)
        for(j = 0; j < D.front().size(); ++j)
            D[i][j] = std::numeric_limits<int>::max();

    D[x][y] = 0;

    int next_i = -1, next_j = -1, dist = std::numeric_limits<int>::max();

    while( true )
    {
        next_i = -1;
        next_j = -1;
        dist = std::numeric_limits<int>::max();

        for(i = 1; i < D.size(); i+=2)
        {
            for(j = 1; j < D.front().size(); j+=2)
            {
                if( !visited[i][j] && D[i][j] < dist )
                {
                    next_i = i;
                    next_j = j;
                    dist   = D[i][j];
                }
            }
        }

        if( next_i == -1 && next_j == -1 ) break;

        visited[next_i][next_j] = true;

        i = next_i - 2;
        j = next_j;

        if( i >= 1 && M[i+1][j] == ' ' )
        {
            if( D[i][j] > D[next_i][next_j] + 1 )
            {
                D[i][j] = D[next_i][next_j] + 1;
            }
        }

        i = next_i + 2;
        j = next_j;

        if( i < D.size()-1 && M[i-1][j] == ' ' )
        {
            if( D[i][j] > D[next_i][next_j] + 1 )
            {
                D[i][j] = D[next_i][next_j] + 1;
            }
        }

        i = next_i;
        j = next_j - 2;

        if( j >= 1 && M[i][j+1] == ' ' )
        {
            if( D[i][j] > D[next_i][next_j] + 1 )
            {
                D[i][j] = D[next_i][next_j] + 1;
            }
        }

        i = next_i;
        j = next_j + 2;

        if( j < D.front().size()-1 && M[i][j-1] == ' ' )
        {
            if( D[i][j] > D[next_i][next_j] + 1 )
            {
                D[i][j] = D[next_i][next_j] + 1;
            }
        }

    }
}

void solve( istream& fin, ostream& out )
{
    int W, H;
    fin >> W >> H;

    vector<string> M( 2*H+1, string() );

    int i, j;

    int exit[2][2];
    int e = 0;

    fin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    for(i = 0; i < 2*H+1; ++i)
    {
        std::getline( fin, M[i] );

        // out << M[i] << endl;

        if( i == 0 || i == 2*H )
        {
            for(j = 0; j < M[i].size(); ++j)
            {
                if( M[i][j] == ' ' )
                {
                    exit[e][0] = ( i == 2*H ? i - 1 : i + 1 );
                    exit[e][1] = j;
                    e++;
                }
            }
        }
        else
        {
            if( M[i][0] == ' ' )
            {
                exit[e][0] = i;
                exit[e][1] = 1;
                e++;
            }

            if( M[i][2*W] == ' ' )
            {
                exit[e][0] = i;
                exit[e][1] = 2*W - 1;
                e++;
            }
        }
    }

    vector< vector<int> > D1(2*H+1, vector<int>( 2*W+1 ) );
    vector< vector<int> > D2(2*H+1, vector<int>( 2*W+1 ) );

    shortest_path( M, exit[0][0], exit[0][1], D1 );
    shortest_path( M, exit[1][0], exit[1][1], D2 );

    int ans = 0;

    // for(i = 0; i < M.size(); ++i)
    // {
    //     for(j = 0; j < M.front().size(); ++j)
    //     {
    //         if( D1[i][j] == std::numeric_limits<int>::max() )
    //             out << '#';
    //         else
    //             out << setw(3) << D1[i][j];
    //     }
    //     out << endl;
    // }

    // for(i = 0; i < M.size(); ++i)
    // {
    //     for(j = 0; j < M.front().size(); ++j)
    //     {
    //         if( D2[i][j] == std::numeric_limits<int>::max() )
    //             out << '#';
    //         else
    //             out << setw(3) << D2[i][j];
    //     }
    //     out << endl;
    // }

    for(i = 1; i < M.size(); i += 2)
    {
        for(j = 1; j < M.front().size(); j += 2)
        {
            ans = max( ans, min( D1[i][j], D2[i][j] ) );
        }
    }

    out << ans+1 << endl;
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
