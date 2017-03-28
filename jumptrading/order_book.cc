#include <iostream>
#include <limits>
#include <iomanip>

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
        // std::cerr << "Duplicated order id " << _oid << std::endl;
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
        // std::cerr << "Unknown order id " << std::hex << std::uppercase << _oid << std::nouppercase << std::dec << std::endl;
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
        // std::cerr << "Unknown order id " << std::hex << std::uppercase << _oid << std::nouppercase << std::dec << std::endl;
        return;
    }

    order_t* order = iter->second.get();

    if ( _size == 0 || _size > order->size )
    {
        // std::cerr << "Order size " << _size << " larger than original size " << order->size << std::endl;
        return;
    }

    order->level->set_size( order->level->get_size() + _size - order->size );
    order->size = _size;
}

void order_book_t::on_trade(const oprice_t &price, const osize_t &size)
{
    if ( EQ( price, m_last_traded_price ) )
    {
        m_volume_at_last_traded_price += size;
    }
    else
    {
        m_last_traded_price = price;
        m_volume_at_last_traded_price = size;
    }
}

void order_book_t::print( std::ostream& os ) const
{
    os << "------------------------------------------------------------" << std::endl;

    price_index_t::reverse_iterator ater = m_book[1].get<1>().rbegin();
    price_index_t::reverse_iterator aend = m_book[1].get<1>().rend();

    for(; ater != aend; ++ater)
    {
        const book_level_t* bl = *ater;
        os << std::setw(12) << std::fixed << std::setprecision(2) << bl->get_price();

        book_level_t::const_iterator iter = bl->begin();
        book_level_t::const_iterator iend = bl->end();

        for(; iter != iend; ++iter)
        {
            os << " " << (*iter)->side << " " << (*iter)->size;
        }

        os << std::endl;
    }

    os << "------------------------------------------------------------" << std::endl;

    price_index_t::reverse_iterator bter = m_book[0].get<1>().rbegin();
    price_index_t::reverse_iterator bend = m_book[0].get<1>().rend();

    for(; bter != bend; ++bter)
    {
        const book_level_t* bl = *bter;
        os << std::setw(12) << std::fixed << std::setprecision(2) << bl->get_price();

        book_level_t::const_iterator iter = bl->begin();
        book_level_t::const_iterator iend = bl->end();

        for(; iter != iend; ++iter)
        {
            os << " " << (*iter)->side << " " << (*iter)->size;
        }

        os << std::endl;
    }

    os << "------------------------------------------------------------" << std::endl;
}

oprice_t order_book_t::get_mid_price() const
{
    if ( m_book[0].empty() || m_book[1].empty() )
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double bid = (*(m_book[0].get<1>().rbegin()))->get_price();
    double ask = (*(m_book[1].get<1>().begin()))->get_price();
    if ( GE( bid, ask ) ) return std::numeric_limits<double>::quiet_NaN();

    return (bid+ask) / 2.0;
}

order_book_t::const_bid_iterator order_book_t::bid_begin() const
{
    return m_book[0].get<1>().rbegin();
}

order_book_t::const_bid_iterator order_book_t::bid_end()   const
{
    return m_book[0].get<1>().rend();
}

order_book_t::const_ask_iterator order_book_t::ask_begin() const
{
    return m_book[1].get<1>().begin();
}

order_book_t::const_ask_iterator order_book_t::ask_end()   const
{
    return m_book[1].get<1>().end();
}

std::ostream& operator << ( std::ostream& os, const order_book_t& ob )
{
    ob.print(os);
    return os;
}
