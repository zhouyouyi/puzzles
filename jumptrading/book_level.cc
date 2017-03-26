#include <iostream>

#include "book_level.h"

book_level_t::~book_level_t()
{
}

void book_level_t::insert_order(const order_t* o)
{
    m_olist.get<sequencial>().push_back( o );
    m_total_size += o->size;
}

void book_level_t::remove_order(const order_t* o)
{
    m_total_size -= o->size;
    m_olist.get<hash_by_oid>().erase(o);
}
