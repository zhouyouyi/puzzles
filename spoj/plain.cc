#include <iostream>
#include <string>

using namespace std;

int main()
{
    int T;
    cin >> T;

    string s;

    while( T-- )
    {
        cin >> s;

        int larger = -1;
        for(int i = 0; i < s.size()/2; ++i)
        {
            if( s[i] < s[s.size()-1-i] )
            {
                larger = 0;
            }
            else if( s[i] > s[s.size()-i-1] )
            {
                larger = 1;
            }
            s[s.size()-i-1] = s[i];
        }

        int pos = -1;
        int carry = 0;
        if( larger < 1 )
        {
            if( s.size() % 2 == 1 )
            {
                // start from the middle digit
                int k = s.size() / 2;
                if( s[k] == '9' )
                {
                    s[k] = '0';
                    carry = 1;
                    pos = k - 1;
                }
                else
                {
                    s[k] = s[k] + 1;
                }
            }
            else
            {
                int k = s.size() / 2 - 1;
                if( s[k] == '9' )
                {
                    s[k] = s[k+1] = '0';
                    carry = 1;
                    pos = k - 1;
                }
                else
                {
                    s[k] = s[k+1] = s[k] + 1;
                }
            }

            for(; pos >= 0 && carry; --pos)
            {
                if( s[pos] == '9' )
                {
                    s[pos] = s[s.size()-pos-1] = '0';
                }
                else
                {
                    s[pos] = s[s.size()-pos-1] = s[pos] + 1;
                    carry = 0;
                }
            }

            if( carry )
            {
                s[0] = '1';
                s.push_back('1');
            }
        }

        cout << s << endl;
    }

    return 0;
}
