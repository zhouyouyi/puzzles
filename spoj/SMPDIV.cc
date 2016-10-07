#include <iostream>

using namespace std;

int main()
{
    int N;

    cin >> N;

    while(N--)
    {
        int n, x, y;

        cin >> n >> x >> y;

        int i;

        for(i = x; i < n; i += x)
        {
            if( i % y )
                cout << i << ' ';
        }

        cout << endl;
    }

    return 0;
}
