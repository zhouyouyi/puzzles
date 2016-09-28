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

const static ll_t MOD = 1E8L;

template<class T>
class binary_index_tree_t
{
public:
    binary_index_tree_t( int N ) : m_array(N) {}
    binary_index_tree_t( int N, const T& val ) : m_array(N, val) {}

    void update( int i, const T& val )
    {
        ++i;
        T delta = val;

        while( i < m_array.size()+1 )
        {
            m_array[i-1] = (m_array[i-1] % MOD + delta % MOD) % MOD;

            i += (i & (-i));
        }
    }

    T sum( int i )
    {
        T ans = 0;
        ++i;

        while( i > 0 )
        {
            ans = (ans % MOD + m_array[i-1] % MOD) % MOD;

            i -= (i & (-i));
        }

        return ans;
    }
private:
    vector<T> m_array;
};

struct course_t
{
    int start;
    int end;

    bool operator < ( const course_t& other ) const
    {
        return end < other.end;
    }
};

int main()
{
    int N, i;
    while( cin >> N )
    {
        if( N == -1 ) break;

        vector<course_t> C(N);

        for(i = 0; i < N; ++i)
        {
            cin >> C[i].start >> C[i].end;
        }

        sort( C.begin(), C.end() );

        binary_index_tree_t<ll_t> bit(N, 0);

        vector<ll_t> T(N,0);

        T[0] = 1;
        bit.update(0, T[0]);

        for(i = 1; i < N; ++i)
        {
            course_t c;
            c.end = C[i].start;

            vector<course_t>::iterator it = std::upper_bound( C.begin(), C.end(), c );

            if( it == C.begin() )
            {
                T[i] = 1;
                bit.update(i, T[i]);
            }
            else
            {
                int idx = (it - C.begin()) - 1;

                T[i] = ( bit.sum( idx ) + 1 ) % MOD;
                bit.update(i, T[i]);
            }
        }

        cout << setw(8) << setfill('0') << bit.sum(N-1) << endl;
    }
    return 0;
}
