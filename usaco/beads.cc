/*
  ID: zhou.yo1
  PROG: beads
  LANG: C++
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int extend_forward( const std::string& s, int start, int maxlen )
{
    char last = 'w';
    int black = 0;
    int red = 0;
    for(int i = start; i - start < maxlen; ++i)
    {
        if ( s[i] == 'w' )
        {
            if( last == 'w' )
            {
                black++;
                red++;
            }
            else if( last == 'r' )
            {
                red++;
            }
            else if( last == 'b' )
            {
                black++;
            }
        }
        else if( s[i] == 'r' )
        {
            if( last == 'w' || last == 'r' )
            {
                red++;
                last = 'r';
            }
            else
            {
                break;
            }
        }
        else if( s[i] == 'b' )
        {
            if( last == 'w' || last == 'b' )
            {
                black++;
                last = 'b';
            }
            else
            {
                break;
            }
        }
    }

    return max(black, red);
}

int extend_backward( const std::string& s, int start, int maxlen )
{
    char last = 'w';
    int black = 0;
    int red = 0;
    for(int i = start; start - i < maxlen; --i)
    {
        if ( s[i] == 'w' )
        {
            if( last == 'w' )
            {
                black++;
                red++;
            }
            else if( last == 'r' )
            {
                red++;
            }
            else if( last == 'b' )
            {
                black++;
            }
        }
        else if( s[i] == 'r' )
        {
            if( last == 'w' || last == 'r' )
            {
                red++;
                last = 'r';
            }
            else
            {
                break;
            }
        }
        else if( s[i] == 'b' )
        {
            if( last == 'w' || last == 'b' )
            {
                black++;
                last = 'b';
            }
            else
            {
                break;
            }
        }
    }

    return max(black, red);
}

int main()
{
    ifstream fin("beads.in");
    ofstream fout("beads.out");

    int i, N;
    string S;

    fin >> N >> S;

    S = S + S;

    int ans = 0;
    int forward = 0, backward = 0;

    for( i = 0; i < N; i += forward )
    {
        forward  = extend_forward ( S, i, N );
        backward = extend_backward( S, N-1+i, N-forward );

        ans = max(ans, forward + backward );
    }

    // cout << ans << endl;

    fout << ans << endl;

    return 0;
}
