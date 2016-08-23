#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;

    cin >> s;

    int ans = 0;

    if( s[0] - 1 >= 'a' && s[1] - 1 >= '1' ) ans ++;
    if( s[0] - 1 >= 'a'                    ) ans ++;
    if( s[0] - 1 >= 'a' && s[1] + 1 <= '8' ) ans ++;
    if(                    s[1] - 1 >= '1' ) ans ++;
    if(                    s[1] + 1 <= '8' ) ans ++;
    if( s[0] + 1 <= 'h' && s[1] - 1 >= '1' ) ans ++;
    if( s[0] + 1 <= 'h'                    ) ans ++;
    if( s[0] + 1 <= 'h' && s[1] + 1 <= '8' ) ans ++;

    cout << ans << endl;
}
