#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
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
    int N;
    cin >> N;

    while(N--)
    {
        string a, b;

        cin >> a >> b;

        int carry = 0;
        int i;

        string r;

        for(i = 0; i < a.size() && i < b.size(); ++i)
        {
            int c = a[i] - '0' + b[i] - '0' + carry;

            carry = c / 10;
            c = c % 10;

            r.push_back( c + '0' );
        }

        for(; i < a.size(); ++i)
        {
            int c = a[i] - '0' + carry;

            carry = c / 10;
            c = c % 10;

            r.push_back( c + '0' );
        }

        for(; i < b.size(); ++i)
        {
            int c = b[i] - '0' + carry;

            carry = c / 10;
            c = c % 10;

            r.push_back( c + '0' );
        }

        if( carry )
            r.push_back( '1' );

        for(i = 0; i < r.size() && r[i] == '0'; ++i);

        for(; i < r.size(); ++i)
            cout << r[i];
        cout << endl;
    }
    return 0;
}
