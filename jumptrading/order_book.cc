#include <iostream>
#include <limits>

#include <boost/foreach.hpp>

#include "order_book.h"

static const oside_t BID = 'B';
static const oside_t ASK = 'A';

order_book_t::~order_book_t()
{
    for( int i = 0; i < 2; ++i)
    {
        ident_index_t::iterator iter = m_book[i].get<0>().begin();
        ident_index_t::iterator iend = m_book[i].get<0>().end();

        for(; iter != iend; ++iter)
        {
            delete *iter;
        }
    }
}

void order_book_t::on_order_insert(const oid_t &_oid, const oside_t &_side, const oprice_t &_price, const osize_t &_size)
{
    order_inventory_t& orders = ( _side == BID ? m_orders[0] : m_orders[1] );

    if ( orders.find( _oid ) != orders.end() )
    {
        std::cerr << "Duplicated order id " << _oid << std::endl;
        return;
    }

    order_ptr_t order( new order_t( _oid, _side, _price, _size ) );

    orders[order->oid] = order;

    book_side_t& bside = ( _side == BID ? m_book[0] : m_book[1] );

    price_index_t& index = bside.get<1>();

    price_index_t::iterator iter = index.find( order->price );

    if ( iter == index.end() )
    {
        book_level_t * bl = new book_level_t( order->price );
        bl->insert_order(order.get());
        order->level = bl;
        index.insert( bl );
    }
    else
    {
        (*iter)->insert_order(order.get());
        order->level = (*iter);
    }
}

void order_book_t::on_order_remove(const oid_t &_oid, const oside_t& _side, const oprice_t& _price, const osize_t& _size)
{
    order_inventory_t& orders = ( _side == BID ? m_orders[0] : m_orders[1] );

    order_inventory_t::iterator iter = orders.find( _oid );
    if ( iter == orders.end() )
    {
        std::cerr << "Unknown order id " << _oid << std::endl;
        return;
    }

    order_t* order = iter->second.get();

    order->level->remove_order(order);

    if ( order->level->empty() )
    {
        book_side_t& bside = ( _side == BID ? m_book[0] : m_book[1] );
        bside.get<0>().erase( order->level );
        delete order->level;
    }

    orders.erase( iter );
}

void order_book_t::on_order_modify(const oid_t &_oid, const oside_t &_side, const oprice_t &_price, const osize_t &_size)
{
    order_inventory_t& orders = ( _side == BID ? m_orders[0] : m_orders[1] );

    order_inventory_t::iterator iter = orders.find( _oid );
    if ( iter == orders.end() )
    {
        std::cerr << "Unknown order id " << _oid << std::endl;
        return;
    }

    order_t* order = iter->second.get();

    if ( _size == 0 || _size > order->size )
    {
        std::cerr << "Order size " << _size << " larger than original size " << order->size << std::endl;
        return;
    }

    order->level->set_total_size( order->level->get_total_size() + _size - order->size );
    order->size = _size;
}

void order_book_t::print( std::ostream& os ) const
{
    price_index_t::reverse_iterator ater = m_book[1].get<1>().rbegin();
    price_index_t::reverse_iterator aend = m_book[1].get<1>().rend();

    for(; ater != aend; ++ater)
    {
        const book_level_t* bl = *ater;
        os << bl->get_price();

        book_level_t::const_iterator iter = bl->begin();
        book_level_t::const_iterator iend = bl->end();

        for(; iter != iend; ++iter)
        {
            os << " " << (*iter)->side << " " << (*iter)->size;
        }

        os << std::endl;
    }

    price_index_t::reverse_iterator bter = m_book[0].get<1>().rbegin();
    price_index_t::reverse_iterator bend = m_book[0].get<1>().rend();

    for(; bter != bend; ++bter)
    {
        const book_level_t* bl = *bter;
        os << bl->get_price();

        book_level_t::const_iterator iter = bl->begin();
        book_level_t::const_iterator iend = bl->end();

        for(; iter != iend; ++iter)
        {
            os << " " << (*iter)->side << " " << (*iter)->size;
        }

        os << std::endl;
    }
}

oprice_t order_book_t::get_mid_price() const
{
    if ( m_book[0].empty() || m_book[1].empty() || GE( (*(m_book[0].get<1>().rbegin()))->get_price(), (*(m_book[1].get<1>().begin()))->get_price() ) )
        return std::numeric_limits<double>::quiet_NaN();

    return ((*(m_book[0].get<1>().rbegin()))->get_price()+(*(m_book[1].get<1>().begin()))->get_price()) / 2.0;
}

std::ostream& operator << ( std::ostream& os, const order_book_t& ob )
{
    ob.print(os);
    return os;
}
