/*
  ID: zhou.yo1
  PROG: milk3
  LANG: C++
*/

#define PROG "milk3"

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

struct status_t
{
    status_t(){}
    status_t(int a, int b, int c): ma(a), mb(b), mc(c) {}
    int ma;
    int mb;
    int mc;
};

struct status_less
{
    bool operator() ( const status_t& a, const status_t& b )
    {
        return a.ma < b.ma || ( a.ma == b.ma && a.mb < b.mb ) || ( a.ma == b.ma && a.mb == b.mb && a.mc < b.mc );
    }
};

typedef deque<status_t> status_q_t;

int va, vb, vc;

set<status_t, status_less> flag;
set<int> ans;

void solve( istream& fin, ostream& out )
{
    int ma, mb, mc;
    fin >> va >> vb >> vc;

    ma = 0, mb = 0, mc = vc;

    status_q_t q;

    q.push_back( status_t(ma, mb, mc) );

    while( q.size() > 0 )
    {
        status_t cur = q.front(); q.pop_front();

        // cout << "status [" << cur.ma << "," << cur.mb << "," << cur.mc << "] " << endl;

        if( flag.find( cur ) != flag.end() )
            continue;

        flag.insert( cur );

        if( cur.ma == 0 ) ans.insert( cur.mc );

        if( cur.ma > 0 )
        {
            if( cur.mb < vb )
            {
                status_t n;
                n.ma = max( 0, cur.ma - (vb - cur.mb) );
                n.mb = min( vb, cur.ma + cur.mb );
                n.mc = cur.mc;

                if( flag.find( n ) == flag.end() )
                    q.push_back( n );
            }

            if( cur.mc < vc )
            {
                status_t n;
                n.ma = max( 0, cur.ma - (vc - cur.mc) );
                n.mb = cur.mb;
                n.mc = min( vc, cur.ma + cur.mc );

                if( flag.find( n ) == flag.end() )
                    q.push_back( n );
            }
        }

        if( cur.mb > 0 )
        {
            if( cur.ma < va )
            {
                status_t n;
                n.ma = min( va, cur.ma + cur.mb );
                n.mb = max( 0, cur.mb - (va - cur.ma) );
                n.mc = cur.mc;

                if( flag.find( n ) == flag.end() )
                    q.push_back( n );
            }

            if( cur.mc < vc )
            {
                status_t n;
                n.ma = cur.ma;
                n.mb = max( 0, cur.mb - (vc - cur.mc) );
                n.mc = min( vc, cur.mb + cur.mc );

                if( flag.find( n ) == flag.end() )
                    q.push_back( n );
            }
        }

        if( cur.mc > 0 )
        {
            if( cur.ma < va )
            {
                status_t n;
                n.ma = min( va, cur.ma + cur.mc );
                n.mb = cur.mb;
                n.mc = max( 0, cur.mc - (va - cur.ma) );

                if( flag.find( n ) == flag.end() )
                    q.push_back( n );
            }

            if( cur.mb < vb )
            {
                status_t n;
                n.ma = cur.ma;
                n.mb = min( vb, cur.mb + cur.mc );
                n.mc = max( 0, cur.mc - (vb - cur.mb ) );

                if( flag.find( n ) == flag.end() )
                    q.push_back( n );
            }
        }

#ifdef LOCAL
        for(int i = 0; i < q.size(); ++i)
        {
            cout << "[" << q[i].ma << "," << q[i].mb << "," << q[i].mc << "] ";
        }
        cout << endl;
#endif
    }

    vector<int> tmp( ans.begin(), ans.end() );

    for(int i = 0; i < tmp.size(); ++i)
    {
        out << tmp[i];

        if( i != tmp.size() - 1 ) out << ' ';
    }
    out << endl;
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
