#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int i, N;
    cin >> N;

    if ( N == 1 )
    {
        cout << "I hate it" << endl;
        return 0;
    }

    cout << "I hate ";

    for ( i = 1; i < N; ++i )
    {
        if ( i > 0 && i % 2 == 0 )
            cout << "that I hate ";
        else if ( i > 0 )
            cout << "that I love ";
    }

    cout << "it" << endl;

    return 0;
}
