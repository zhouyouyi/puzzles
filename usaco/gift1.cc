/*
  ID: zhou.yo1
  PROG: gift1
  LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    ofstream fout( "gift1.out" );
    ifstream fin ( "gift1.in"  );

    int N, i;

    fin >> N;

    vector<string> S(N);
    map<string, int> M;

    for ( i = 0; i < N; ++i )
    {
        fin >> S[i];
        M[S[i]] = 0;
    }

    string name, f;
    int money, friends;

    while ( fin >> name )
    {
        fin >> money >> friends;

        M[name] -= money;

        if ( friends == 0 )
        {
            M[name] += money;
            continue;
        }

        M[name] += ( money % friends );

        for ( i = 0; i < friends; ++i )
        {
            fin >> f;
            M[f] += ( money / friends );
        }
    }

    for ( i = 0 ; i < N; ++i )
    {
        fout << S[i] << ' ' << M[S[i]] << endl;
    }

    return 0;
}
