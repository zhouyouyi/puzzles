/*
  ID: zhou.yo1
  PROG: friday
  LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ofstream fout("friday.out");
    ifstream fin ("friday.in");

    int N;
    fin >> N;

    int i, month;
    int day_one = 0;
    vector<int> count(8,0);
    for( i = 0; i < N; ++i )
    {
        int year = 1900 + i;

        for ( month = 1; month <= 12; ++month )
        {
            count[(day_one + 5) % 7]++;

            if ( month == 9 || month == 4 || month == 6 || month == 11 )
            {
                day_one = (day_one + 30) % 7;
            }
            else if ( month == 2 )
            {
                if ( year % 4 == 0 && ( year % 100 != 0 || year % 400 == 0 ) )
                    day_one = (day_one + 29) % 7;
                else
                    day_one = (day_one + 28) % 7;
            }
            else
            {
                day_one = (day_one + 31) % 7;
            }
        }
    }

    fout << count[5] << ' '
         << count[6] << ' '
         << count[0] << ' '
         << count[1] << ' '
         << count[2] << ' '
         << count[3] << ' '
         << count[4]
         << endl;

    return 0;
}
