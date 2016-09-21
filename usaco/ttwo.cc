/*
  ID: zhou.yo1
  PROG: ttwo
  LANG: C++
*/

#define PROG "ttwo"

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

int F_i, F_j, F_d = 0, C_i, C_j, C_d = 0;

void solve( istream& fin, ostream& out )
{
    string M[10];

    int i, j, t = 0;

    for(i = 0; i < 10; ++i)
    {
        fin >> M[i];

        for(j = 0; j < M[i].size(); ++j)
        {
            if( M[i][j] == 'F' )
            {
                F_i = i;
                F_j = j;
            }
            else if( M[i][j] == 'C' )
            {
                C_i = i;
                C_j = j;
            }
        }
    }

    while(true)
    {
        if( t > 10000 )
        {
            out << 0 << endl;
            break;
        }

        if( F_i == C_i && F_j == C_j )
        {
            out << t << endl;
            break;
        }

        switch(F_d)
        {
        case 0:
        {
            if( F_i - 1 < 0 || M[F_i-1][F_j] == '*' )
            {
                F_d = (F_d+1) % 4;
            }
            else
            {
                F_i--;
            }
            break;
        }
        case 1:
        {
            if( F_j + 1 > 9 || M[F_i][F_j+1] == '*' )
            {
                F_d = (F_d+1) % 4;
            }
            else
            {
                F_j++;
            }
            break;
        }
        case 2:
        {
            if( F_i + 1 > 9 || M[F_i+1][F_j] == '*' )
            {
                F_d = (F_d+1) % 4;
            }
            else
            {
                F_i++;
            }
            break;
        }
        case 3:
        {
            if( F_j - 1 < 0 || M[F_i][F_j-1] == '*' )
            {
                F_d = (F_d+1) % 4;
            }
            else
            {
                F_j--;
            }
            break;
        }
        }

        switch(C_d)
        {
        case 0:
        {
            if( C_i - 1 < 0 || M[C_i-1][C_j] == '*' )
            {
                C_d = (C_d+1) % 4;
            }
            else
            {
                C_i--;
            }
            break;
        }
        case 1:
        {
            if( C_j + 1 > 9 || M[C_i][C_j+1] == '*' )
            {
                C_d = (C_d+1) % 4;
            }
            else
            {
                C_j++;
            }
            break;
        }
        case 2:
        {
            if( C_i + 1 > 9 || M[C_i+1][C_j] == '*' )
            {
                C_d = (C_d+1) % 4;
            }
            else
            {
                C_i++;
            }
            break;
        }
        case 3:
        {
            if( C_j - 1 < 0 || M[C_i][C_j-1] == '*' )
            {
                C_d = (C_d+1) % 4;
            }
            else
            {
                C_j--;
            }
            break;
        }
        }

        ++t;

#ifdef LOCAL
        out << endl;
        for(i = 0; i < 10; ++i)
        {
            for(j = 0; j < 10; ++j)
            {
                if( F_i == i && F_j == j ) out << 'F';
                else if( C_i == i && C_j == j ) out << 'C';
                else if( M[i][j] == 'F' ) out << '.';
                else if( M[i][j] == 'C' ) out << '.';
                else out << M[i][j];
            }
            out << endl;
        }
        getchar();
#endif
    }
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
