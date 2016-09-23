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
    int N, C;
    cin >> N >> C;

    int i, a = -1, b, ans = 1;

    cin >> a;

    for(i = 1; i < N; ++i)
    {
        cin >> b;

        if( b - a <= C ) ans++;
        else ans = 1;

        a = b;
    }

    cout << ans << endl;
    return 0;
}
