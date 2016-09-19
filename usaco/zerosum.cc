/*
  ID: zhou.yo1
  PROG: zerosum
  LANG: C++
*/

#define PROG "zerosum"

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

const char ops[] = { ' ', '+', '-' };

int eval( vector<char>& nums )
{
    int ans = 0;

    int i;
    char last_op = '+';
    int oprand = 0;
    for(i = 0; i < nums.size(); ++i)
    {
        if( nums[i] == '+' || nums[i] == '-' )
        {
            if(last_op == '+') ans += oprand;
            else if(last_op == '-') ans -= oprand;

            oprand = 0;
            last_op = nums[i];
        }
        else if( nums[i] >= '0' && nums[i] <= '9' )
        {
            oprand = oprand * 10 + (nums[i] - '0');
        }
    }

    if( last_op == '+' ) ans += oprand;
    else if( last_op == '-' ) ans -= oprand;

    return ans;
}

void search( vector<char>& nums, int digit, int K, int N, ostream& out )
{
    // if( digit > 9 ) return;

    int i, j;

    if( nums.size() == K && eval(nums) == 0 )
    {
        for(i = 0; i < nums.size(); ++i)
        {
            out << nums[i];
        }
        //out << " = 0";
        out << endl;

        return;
    }

    for(i = 0; i < 3; ++i)
    {
        nums.push_back( ops[i] );

        for(j = digit; j <= N; ++j)
        {
            nums.push_back( '0'+j );

            search( nums, j+1, K, N, out );

            nums.pop_back();
        }

        nums.pop_back();
    }
}

void solve( istream& fin, ostream& out )
{
    int N;
    fin >> N;

    vector<char> nums;

    for(int i = 1; i <= 1; ++i)
    {
        nums.push_back( '0'+i );
        search( nums, i+1, 2*N-1, N, out );
        nums.pop_back();
    }
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

#ifdef LOCAL
  solve( cin, cout );
#else
  solve( fin, out );
#endif

  return 0;
}
