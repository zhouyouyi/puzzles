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

typedef unsigned long long ull_t;
typedef long long ll_t;

int main()
{
    int X, Y;
    cin >> X >> Y;

    int ans = 0;

    int y[] = {Y, Y, Y};

    while(y[0] != X || y[1] != X || y[2] != X)
    {
        sort( y, y+3 );

        y[0] = min( y[1] + y[2] - 1, X );

        ans++;

        // cout << "(" << y[0] << "," << y[1] << "," << y[2] << ")" << endl;
    }

    cout << ans << endl;
    return 0;
}
