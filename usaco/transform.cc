/*
  ID: zhou.yo1
  PROG: transform
  LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<string> matrix_t;

bool operator == ( const matrix_t& a, const matrix_t& b )
{
    if ( a.size() != b.size() ) return false;

    int i, N = a.size();
    for ( i = 0; i < N; ++i )
    {
        if ( a[i] != b[i] ) return false;
    }

    return true;
}

void rotate_90( matrix_t& a )
{
    int i, j, N = a.size();
    for ( i = 0; i < N/2; ++i )
    {
        for ( j = i; j < N-1-i; ++j )
        {
            swap( a[i][j], a[N-j-1][i] );
            swap( a[N-j-1][i], a[N-i-1][N-j-1] );
            swap( a[N-i-1][N-j-1], a[j][N-i-1] );
        }
    }

#ifdef ZYY
    cout << "R90:" << endl;
    for ( i = 0; i < N; ++i )
        cout << a[i] << endl;
    cout << endl;
#endif
}

void mirror( matrix_t& a )
{
    int i, j, N = a.size();

    for ( i = 0; i < N; ++i )
    {
        for ( j = 0; j < a[i].size() / 2; ++j )
        {
            swap( a[i][j], a[i][N-j-1] );
        }
    }

#ifdef ZYY
    cout << "MIRROR:" << endl;
    for ( i = 0; i < N; ++i )
        cout << a[i] << endl;
    cout << endl;
#endif
}

int main()
{
    ifstream fin("transform.in");
    ofstream fout("transform.out");

    int i, N;
    fin >> N;

    matrix_t S(N), T(N);

    for ( i = 0; i < N; ++i )
        fin >> S[i];
    for ( i = 0; i < N; ++i )
        fin >> T[i];

#ifdef ZYY
    for ( i = 0; i < N; i++ )
        cout << S[i] << endl;
    cout << endl;
#endif

    for ( i = 1; i < 4; ++i )
    {
        rotate_90( S );

        if ( S == T )
        {
            fout << i << endl;
            return 0;
        }
    }

    rotate_90( S );
    mirror( S );

    if ( S == T )
    {
        fout << 4 << endl;
        return 0;
    }

    for ( i = 1; i < 4; ++i )
    {
        rotate_90( S );

        if ( S == T )
        {
            fout << 5 << endl;
            return 0;
        }
    }

    rotate_90( S );
    mirror( S );

    if ( T == S )
    {
        fout << 6 << endl;
        return 0;
    }

    fout << 7 << endl;
    return 0;
}
