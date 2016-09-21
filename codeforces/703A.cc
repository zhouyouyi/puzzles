#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int N, M, C;
    int chris = 0, mishka = 0;
    int i;
    cin >> N;

    for ( i = 0; i < N; ++i )
    {
        cin >> M >> C;

        if ( M > C ) mishka++;
        else if ( M < C ) chris++;
    }

    if ( mishka > chris ) cout << "Mishka" << endl;
    else if ( mishka < chris ) cout << "Chris" << endl;
    else cout << "Friendship is magic!^^" << endl;
    return 0;
}
