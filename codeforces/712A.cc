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

int main()
{
    int N;
    int i;
    cin >> N;

    vector<int> A(N);

    for(i = 0; i < N; ++i)
        cin >> A[i];

    for(i = 0; i < N-1; ++i)
        cout << A[i] + A[i+1] << ' ';
    cout << A[N-1] << endl;
    return 0;
}
