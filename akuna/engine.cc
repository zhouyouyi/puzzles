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

using namespace std;

typedef long   price_t;
typedef long   quantity_t;
typedef string oid_t;
typedef string tif_t;

const static tif_t TIF_IOC = "IOC";
const static tif_t TIF_GFD = "GFD";

typedef struct _order_entry
{
    _order_entry() {} // required by STL
    _order_entry(const price_t p, const quantity_t q, const oid_t& o) : price(p), quantity(q), oid(o) {}
    
    price_t    price;
    quantity_t quantity;
    oid_t      oid;

} order_entry_t;

typedef deque< order_entry_t > order_list_t;
typedef map< price_t, order_list_t, std::less<price_t> >     bid_side_t; // bid side decreasing price
typedef map< price_t, order_list_t, std::greater<price_t> >  ask_side_t; // ask side increasing price

bid_side_t bid_side;
ask_side_t ask_side;

inline bid_side_t& get_bids() { return bid_side; }
inline ask_side_t& get_asks() { return ask_side; }

const static string CMD_BUY    = "BUY";
const static string CMD_SELL   = "SELL";
const static string CMD_CANCEL = "CANCEL";
const static string CMD_MODIFY = "MODIFY";
const static string CMD_PRINT  = "PRINT";

void handle_buy(const price_t price, const quantity_t quantity_, const oid_t& oid, const tif_t& tif)
{
    quantity_t quantity = quantity_;
    // check matching
    ask_side_t::iterator ait = get_asks().upper_bound(price);
    
    for(ask_side_t::iterator it = get_asks().begin(); it != ait && quantity > 0; ++it)
    {
        // match, something before ait have matched
        order_list_t& olist = it->second;
        
        while(quantity > 0 && olist.size() > 0)
        {
            order_entry_t& order = olist.front();
            quantity_t traded = min(quantity, order.quantity);
            
            // show trades
            cout << "TRADE "
                 << order.oid << ' ' << order.price << ' ' << traded << ' '
                 << oid       << ' ' << price       << ' ' << traded
                 << endl;
            
            quantity -= traded;
            order.quantity -= traded;
            
            if(order.quantity == 0)
            {
                // existing order all traded
                olist.pop_front();
            }
        }
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
            bit->second.push_back(order_entry_t(price, quantity, oid));
        }
        else
        {
            // insert a new level
            // this can be done better with C++11
            order_list_t olist;
            olist.push_back(order_entry_t(price, quantity, oid));
            get_bids()[price] = olist;
        }
    }
}

void handle_sell(const price_t price, const quantity_t quantity_, const oid_t& oid, const tif_t& tif)
{
    quantity_t quantity = quantity_;
    // check matching
    bid_side_t::iterator bit = get_bids().upper_bound(price);
    
    for(bid_side_t::iterator it = get_bids().begin(); it != bit && quantity > 0; ++it)
    {
        // match, something before bit have matched
        order_list_t& olist = it->second;
        
        while(quantity > 0 && olist.size() > 0)
        {
            order_entry_t& order = olist.front();
            quantity_t traded = min(quantity, order.quantity);
            
            // show trades
            cout << "TRADE "
                 << order.oid << ' ' << order.price << ' ' << traded << ' '
                 << oid       << ' ' << price       << ' ' << traded
                 << endl;
            
            quantity -= traded;
            order.quantity -= traded;
            
            if(order.quantity == 0)
            {
                // existing order all traded
                olist.pop_front();
            }
        }
    }
    
    if(tif == TIF_IOC)
    {
        // done with ioc orders
        return;
    }
    
    if(quantity > 0)
    {
        // place the remaining size into bid side
        ask_side_t::iterator ait = get_asks().find(price);
        
        if(ait != get_asks().end())
        {
            // append to existing level
            ait->second.push_back(order_entry_t(price, quantity, oid));
        }
        else
        {
            // insert a new level
            // this can be done better with C++11
            order_list_t olist;
            olist.push_back(order_entry_t(price, quantity, oid));
            get_asks()[price] = olist;
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
                total += oi->quantity;

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
                total += oi->quantity;

            cout << iter->first << ' ' << total << endl;
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string line;
    while(cin >> line)
    {
        string cmd;
        istringstream iss(line);
        iss >> cmd;
        
        if(cmd == CMD_BUY)
        {
            
        }
    }
    return 0;
}
