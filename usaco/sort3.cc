/*
  ID: zhou.yo1
  PROG: sort3
  LANG: C++
*/

#define PROG "sort3"

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

void solve( istream& fin, ostream& out )
{
    int N;
    fin >> N;

    vector<int> A(N);
    vector<int> count(4, 0);

    int i, j;
    for(i = 0; i < N; i++)
    {
        fin >> A[i];
        count[A[i]]++;
    }

    int ans = 0;

    for(i = 0; i < N; ++i)
    {
        if(A[i] == 2)
        {
            if(i < count[1])
            {
                for(j = count[1]; j < N; ++j)
                {
                    if(A[j] == 1)
                    {
                        ans++;
                        swap(A[i], A[j]);
                        break;
                    }
                }
            }
            else if(i >= count[1] + count[2])
            {
                for(j = N-count[3]-1; j >= 0; --j)
                {
                    if(A[j] == 3)
                    {
                        ans++;
                        swap(A[i], A[j]);
                        break;
                    }
                }
            }
        }
        else if(A[i] == 3)
        {
            if(i < count[1])
            {
                for(j = N-1; j >= 0; --j)
                {
                    if(A[j] == 1)
                    {
                        ans++;
                        swap(A[i], A[j]);
                        break;
                    }
                }
            }
            else if(i < count[1] + count[2])
            {
                for(j = N-1; j >= 0; --j)
                {
                    if(A[j] == 2)
                    {
                        ans++;
                        swap(A[i], A[j]);
                        break;
                    }
                }
            }
        }
    }

    out << ans << endl;
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
