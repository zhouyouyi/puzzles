/*
  Compiled and tested with clang++ 3.8 and g++ 6.1

  Please use -std=c++11 to compile.
*/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cstdint>
#include <memory>

using namespace std;

// useful typedefs
typedef uint64_t  price_t;
typedef uint64_t  quantity_t;
typedef string    oid_t;
typedef string    tif_t;
typedef string    dir_t;

// invariant constant definitions
const static tif_t TIF_IOC     = "IOC";
const static tif_t TIF_GFD     = "GFD";

const static dir_t DIR_BUY     = "BUY";
const static dir_t DIR_SELL    = "SELL";

const static string CMD_BUY    = "BUY";
const static string CMD_SELL   = "SELL";
const static string CMD_CANCEL = "CANCEL";
const static string CMD_MODIFY = "MODIFY";
const static string CMD_PRINT  = "PRINT";
// end constant definitions

// timestamp related types/functions section
typedef uint64_t  timestamp_t;

timestamp_t g_clock = 0;

inline timestamp_t next_timestamp() { return ++g_clock; }
// end timestamp section

// order_entry in our order book
struct _order_entry;
typedef shared_ptr<_order_entry> order_entry_ptr_t;
// this should really be a boost::multi_index as we want to iterate by
// time of enqueuing but find by order id.
typedef map< timestamp_t, order_entry_ptr_t > order_list_t;

struct _order_entry
{
    // _order_entry() : parent(NULL) {} // required by STL
    _order_entry(const price_t p, const quantity_t q, const oid_t& o, const dir_t& d, order_list_t& par)
        : price(p), quantity(q), oid(o), dir(d), timetag(next_timestamp()), parent(par) {}
    
    price_t     price;
    quantity_t  quantity;
    oid_t       oid;
    dir_t       dir;

    timestamp_t timetag;

    order_list_t& parent;
};

typedef _order_entry order_entry_t;

ostream& operator << ( ostream& os, const order_entry_t& o )
{
    return os << "[" << o.timetag << "," << o.oid << "," << o.dir << "," << o.price << "," << o.quantity << "]";
}

// our order book definition
typedef map< price_t, order_list_t, std::greater<price_t> > bid_side_t; // bid side increasing price
typedef map< price_t, order_list_t, std::less<price_t> >    ask_side_t; // ask side decreasing price

bid_side_t bid_side;
ask_side_t ask_side;

inline bid_side_t& get_bids() { return bid_side; }
inline ask_side_t& get_asks() { return ask_side; }

// global order index
typedef unordered_map< oid_t, order_entry_ptr_t > oid_index_t;

oid_index_t g_index;

void insert_order_index( const order_entry_ptr_t& o )
{
#ifdef LOCAL
    cout << "add idx " << *o << endl;
#endif
    g_index[o->oid] = o;
}

order_entry_ptr_t find_order_index( const oid_t& oid )
{
    oid_index_t::iterator it = g_index.find( oid );

    if( it != g_index.end() ) return it->second;

    return order_entry_ptr_t();
}

bool remove_order_index( const oid_t& oid )
{
    return g_index.erase( oid ) > 0;
}

// end global order index

void handle_buy(const price_t price, const quantity_t quantity_, const oid_t& oid, const tif_t& tif)
{
    quantity_t quantity = quantity_;
    // check matching
    ask_side_t::iterator ait = get_asks().upper_bound(price);

    vector<price_t> levels_to_delete;
    
    for(ask_side_t::iterator it = get_asks().begin(); it != ait && quantity > 0; ++it)
    {
        // match, something before ait have matched
        order_list_t& olist = it->second;
        
        while(quantity > 0 && olist.size() > 0)
        {
            // need to hold a ptr in case it gets deleted before we finish updating it
            order_entry_ptr_t order = olist.begin()->second;
#ifdef LOCAL
            cout << "match " << *order << endl;
#endif
            quantity_t traded = min(quantity, order->quantity);
            
            // show trades
            cout << "TRADE "
                 << order->oid << ' ' << order->price << ' ' << traded << ' '
                 << oid        << ' ' << price        << ' ' << traded
                 << endl;
            
            quantity -= traded;
            order->quantity -= traded;
            
            if(order->quantity == 0)
            {
                // existing order all traded
                olist.erase(olist.begin());
                // remove index
                remove_order_index( order->oid );
            }
        }

        if(olist.empty())
            levels_to_delete.push_back( it->first );
    }

    // clean up empty levels
    for(int i = 0; i < levels_to_delete.size(); ++i)
    {
        get_asks().erase( levels_to_delete[i] );
    }

    if(tif == TIF_IOC)
    {
        // done with ioc orders
        return;
    }
    
    if(quantity > 0)
    {
        // place the remaining size into bid side
        bid_side_t::iterator bit = get_bids().find(price);
        
        if(bit != get_bids().end())
        {
            // append to existing level
            order_entry_ptr_t o( new order_entry_t(price, quantity, oid, DIR_BUY, bit->second) );
            bit->second.insert( make_pair(o->timetag, o) ); // could be better if we use move semantic, but I am not very familiar with it
            insert_order_index( o );
#ifdef LOCAL
            cout << "new order " << *o << endl;
#endif
        }
        else
        {
            // insert a new level
            // this can be done better with C++11
            order_list_t olist;
            get_bids()[price] = olist;
            order_entry_ptr_t o( new order_entry_t( price, quantity, oid, DIR_BUY, (get_bids()[price]) ) );
            get_bids()[price].insert( make_pair( o->timetag, o) );

            insert_order_index( o );
#ifdef LOCAL
            cout << "new level " << *o << endl;
#endif
        }
    }
}

void handle_sell(const price_t price, const quantity_t quantity_, const oid_t& oid, const tif_t& tif)
{
    quantity_t quantity = quantity_;
    // check matching
    bid_side_t::iterator bit = get_bids().upper_bound(price);

    vector<price_t> levels_to_delete;
    
    for(bid_side_t::iterator it = get_bids().begin(); it != bit && quantity > 0; ++it)
    {
        // match, something before bit have matched
        order_list_t& olist = it->second;
        
        while(quantity > 0 && olist.size() > 0)
        {
            order_entry_ptr_t order = olist.begin()->second;
#ifdef LOCAL
            cout << "match " << *order << endl;
#endif
            quantity_t traded = min(quantity, order->quantity);
            
            // show trades
            cout << "TRADE "
                 << order->oid << ' ' << order->price << ' ' << traded << ' '
                 << oid        << ' ' << price        << ' ' << traded
                 << endl;
            
            quantity -= traded;
            order->quantity -= traded;
            
            if(order->quantity == 0)
            {
                // existing order all traded
                olist.erase(olist.begin());
                // remove index
                remove_order_index( order->oid );
            }
        }

        if(olist.empty())
            levels_to_delete.push_back( it->first );
    }

    for(int i = 0; i < levels_to_delete.size(); ++i)
    {
        get_bids().erase( levels_to_delete[i] );
    }
    
    if(tif == TIF_IOC)
    {
        // done with ioc orders
        return;
    }
    
    if(quantity > 0)
    {
        // place the remaining size into ask side
        ask_side_t::iterator ait = get_asks().find(price);
        
        if(ait != get_asks().end())
        {
            // append to existing level
            order_entry_ptr_t o( new order_entry_t( price, quantity, oid, DIR_SELL, (ait->second) ) );
            ait->second.insert( make_pair(o->timetag, o) ); // could be better if we use move semantic, but I am not very familiar with it
            insert_order_index( o );
#ifdef LOCAL
            cout << "new order " << *o << endl;
#endif
        }
        else
        {
            // insert a new level
            // this can be done better with C++11
            order_list_t olist;
            get_asks()[price] = olist;
            order_entry_ptr_t o( new order_entry_t( price, quantity, oid, DIR_SELL, (get_asks()[price]) ) );
            get_asks()[price].insert( make_pair( o->timetag, o) );

            insert_order_index( o );
#ifdef LOCAL
            cout << "new level " << *o << endl;
#endif
        }
    }
}

void handle_print()
{
    // according to requirements, ask prices will also be printed in
    // decreasing order, weird.
    cout << "SELL:" << endl;
    {
        ask_side_t::reverse_iterator iter = get_asks().rbegin();
        ask_side_t::reverse_iterator iend = get_asks().rend();

        for(; iter != iend; ++iter)
        {
            // it's better to maintain a total sum on the fly
            // instead of computing it every time.
            quantity_t total = 0;
            const order_list_t& olist = iter->second;

            order_list_t::const_iterator oi = olist.begin();
            order_list_t::const_iterator oe = olist.end();

            for(; oi != oe; ++oi)
                total += oi->second->quantity;

            cout << iter->first << ' ' << total << endl;
        }
    }

    cout << "BUY:" << endl;
    {
        bid_side_t::iterator iter = get_bids().begin();
        bid_side_t::iterator iend = get_bids().end();

        for(; iter != iend; ++iter)
        {
            // it's better to maintain a total sum on the fly
            // instead of computing it every time.
            quantity_t total = 0;
            const order_list_t& olist = iter->second;

            order_list_t::const_iterator oi = olist.begin();
            order_list_t::const_iterator oe = olist.end();

            for(; oi != oe; ++oi)
                total += oi->second->quantity;

            cout << iter->first << ' ' << total << endl;
        }
    }
}

void handle_cancel(const oid_t& oid)
{
    order_entry_ptr_t o = find_order_index( oid );

    if( o )
    {
#ifdef LOCAL
        cout << "cancel " << *o << endl;
#endif
        // remove the order from order list first
        price_t price = o->price;
        o->parent.erase( o->timetag );

        if( o->parent.empty() )
        {
            if( o->dir == DIR_BUY )
                get_bids().erase( price );
            else
                get_asks().erase( price );
        }

        // remove from the global index
        remove_order_index( oid );
    }
}

void handle_modify(const oid_t& oid, const dir_t& dir, const price_t new_px, const quantity_t new_qty)
{
    order_entry_ptr_t o = find_order_index( oid );

    if( !o ) return;

#ifdef LOCAL
    cout << "modify " << *o << endl;
#endif
    price_t p = o->price;
    // this order will be removed from the previous level no matter what
    o->parent.erase( o->timetag );
    if( o->parent.empty() )
    {
        if(o->dir == DIR_BUY)
            get_bids().erase( p );
        else
            get_asks().erase( p );
    }
    // remove index
    remove_order_index( o->oid );

    // now treat it as if a new order was inserted
    if( dir == DIR_BUY )
        handle_buy( new_px, new_qty, oid, TIF_GFD );
    else
        handle_sell( new_px, new_qty, oid, TIF_GFD );
}

void dispatch( const string& line )
{
    string cmd;
    istringstream iss(line);

    if( iss >> cmd )
    {
        if( cmd == CMD_BUY )
        {
            tif_t      tif;
            price_t    price;
            quantity_t quantity;
            oid_t      oid;

            if( iss >> tif >> price >> quantity >> oid )
            {
                handle_buy( price, quantity, oid, tif );
            }
        }
        else if( cmd == CMD_SELL )
        {
            tif_t      tif;
            price_t    price;
            quantity_t quantity;
            oid_t      oid;

            if( iss >> tif >> price >> quantity >> oid )
            {
                handle_sell( price, quantity, oid, tif );
            }
        }
        else if( cmd == CMD_CANCEL )
        {
            oid_t oid;

            if( iss >> oid )
            {
                handle_cancel( oid );
            }
        }
        else if( cmd == CMD_MODIFY )
        {
            oid_t      oid;
            dir_t      dir;
            price_t    price;
            quantity_t quantity;

            if( iss >> oid >> dir >> price >> quantity )
            {
                handle_modify( oid, dir, price, quantity );
            }
        }
        else if( cmd == CMD_PRINT )
        {
            handle_print();
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string line;
    while( getline(cin, line) )
    {
        dispatch( line );
    }
    return 0;
}
