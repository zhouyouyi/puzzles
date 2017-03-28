#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>

#define BOOST_MULTI_INDEX_DISABLE_SERIALIZATION // eliminate unnecessary dependency
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#undef BOOST_MULTI_INDEX_DISABLE_SERIALIZATION

#include "fpmath.h"
#include "book_level.h"

namespace bmi = boost::multi_index;

class order_book_t : boost::noncopyable
{
protected:
    typedef boost::multi_index_container< book_level_t*,
                                          bmi::indexed_by<
                                              bmi::hashed_unique< bmi::identity< book_level_t* > >,
                                              bmi::ordered_unique< bmi::const_mem_fun< book_level_t, const oprice_t&, &book_level_t::get_price > >
                                              > > book_side_t;
    typedef book_side_t::nth_index<0>::type ident_index_t;
    typedef book_side_t::nth_index<1>::type price_index_t;

    // typedef boost::multi_index_container< book_level_t*,
    //                                       bmi::indexed_by<
    //                                           bmi::hashed_unique< bmi::identity< book_level_t* > >,
    //                                           bmi::ordered_unique< bmi::const_mem_fun< book_level_t, const oprice_t&, &book_level_t::get_price >, FPGreater >
    //                                           > > bid_side_t;
    // typedef bid_side_t::nth_index<0>::type bid_ident_index_t;
    // typedef bid_side_t::nth_index<1>::type bid_price_index_t;

    typedef boost::shared_ptr<order_t> order_ptr_t;

    typedef boost::unordered_map< oid_t, order_ptr_t > order_inventory_t;
public:
    order_book_t() : m_last_traded_price(-1), m_volume_at_last_traded_price(0) {};

    /*virtual*/ ~order_book_t();

    void on_order_insert( const oid_t& _oid, const oside_t& _side, const oprice_t& _price, const osize_t& _size );

    void on_order_remove( const oid_t& _oid, const oside_t& _side, const oprice_t& _price, const osize_t& _size );

    void on_order_modify( const oid_t& _oid, const oside_t& _side, const oprice_t& _price, const osize_t& _size );

    void print( std::ostream& os ) const;

    oprice_t get_mid_price() const;

protected:
    book_side_t m_book[2]; // 0 - BID, 1 - ASK
    //bid_side_t m_bid;

    oprice_t m_last_traded_price;
    osize_t  m_volume_at_last_traded_price;

    order_inventory_t m_orders[2]; // 0 - BID, 1 - ASK
};

std::ostream& operator << ( std::ostream& os, const order_book_t& ob );

#endif
