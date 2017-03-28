#ifndef BOOK_LEVEL_H
#define BOOK_LEVEL_H

#include <cstddef>
#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

#define BOOST_MULTI_INDEX_DISABLE_SERIALIZATION // eliminate unnecessary dependency
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#undef BOOST_MULTI_INDEX_DISABLE_SERIALIZATION

typedef uint64_t oid_t;
typedef uint32_t osize_t;
typedef double   oprice_t;
typedef char     oside_t;

class book_level_t;

// POD type for order
// for this particular problem, we only care about oid and order size.
// well if we only care about aggregated size, then we don't even need to know oid at all.
struct order_t
{
    oid_t oid;
    oside_t side;
    oprice_t price;
    osize_t size;

    book_level_t* level;

    order_t() : oid(0), side(0), price(0), size(0), level(NULL) {} // for container semantic

    order_t( const oid_t& _oid, const oside_t& _side, const oprice_t& _price, const osize_t& _size )
        : oid(_oid), side(_side), price(_price), size(_size), level(NULL) {}
};

namespace bmi = boost::multi_index;

class book_level_t : boost::noncopyable // prevent copying since book_level_t holds a list of orders
{
protected:
    // maintain an order list by the time priority (the order of insertion) with quick look-up by oid
    struct hash_by_oid {};
    struct sequencial  {};
    typedef boost::multi_index_container< const order_t*,
                                          bmi::indexed_by<
                                              bmi::hashed_unique< bmi::tag<hash_by_oid>, bmi::identity< const order_t* > >,
                                              bmi::sequenced< bmi::tag<sequencial> >
                                              > > orderlist_t;

    typedef typename orderlist_t::index<sequencial>::type time_index_t;
    typedef typename orderlist_t::index<hash_by_oid>::type oid_index_t;

public:
    book_level_t() : m_price(0), m_total_size(0), m_index( m_olist.get<sequencial>()) {}
    book_level_t( const oprice_t& _price ) : m_price(_price), m_total_size(0), m_index( m_olist.get<sequencial>()) {}
    book_level_t( const oprice_t& _price, const osize_t& _size ) : m_price(_price), m_total_size(_size), m_index( m_olist.get<sequencial>()) {}

    /*virtual*/ ~book_level_t();

    // inserts a new order into the book level
    // takes no ownership of the inserted order
    void insert_order( const order_t* o );
    // removes an existing order from the book level
    void remove_order( const order_t* o );

    const oprice_t& get_price() const { return m_price; }
    const osize_t&  get_size()  const { return m_total_size; }

    void set_price( const oprice_t& px ) { m_price = px; }
    void set_size( const osize_t& sz ) { m_total_size = sz; }

    void clear() { m_olist.clear(); }

public:
    // pimpl delegators
    typedef time_index_t::iterator iterator;
    typedef time_index_t::const_iterator const_iterator;

    inline iterator begin() { return m_index.begin(); }
    inline iterator end()   { return m_index.end(); }

    inline const_iterator begin() const { return m_index.begin(); }
    inline const_iterator end()   const { return m_index.end(); }

    inline const order_t* front() const { return m_index.front(); }

    inline void pop_front() { m_index.pop_front(); }

    inline bool empty() const { return m_index.empty(); }
    inline std::size_t size() const { return m_index.size(); }

protected:
    oprice_t m_price;
    osize_t  m_total_size;

    orderlist_t m_olist;
    time_index_t& m_index;
};

#endif
