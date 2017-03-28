#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include <boost/cstdint.hpp>

#include "order_book.h"
#include "perf_counter.h"

int main(int argc, char* argv[])
{
    if ( argc < 2 )
    {
        std::cerr << "usage: " << argv[0] << " <messages.in>" << std::endl;
        return -1;
    }

    order_book_t ob;
    std::string line;
    std::ifstream ifs( argv[1] );

    perf_counter_t line_pf;

    int processed = 0, discarded = 0;
    int counter = 0;

    while ( std::getline( ifs, line ) )
    {
        char action;
        oid_t oid;
        char side;
        int size;
        double price;

        if ( sscanf(line.c_str(), "%c,", &action) < 1 )
        {
            std::cerr << "Cannot read message type " << line << std::endl;
            ++discarded;
            continue;
        }

        PROFILE(line_pf)
        {
            switch( action )
            {
            case 'A':
            {
                if ( sscanf( line.c_str(), "%c,%lx,%c,%d,%lf", &action, &oid, &side, &size, &price ) < 5 )
                {
                    std::cerr << "Cannot parse line " << line << std::endl;
                    ++discarded;
                    break;
                }

                if ( oid < 0 || LTZ(price) || size < 0 || ( side != 'B' && side != 'S' ) )
                {
                    std::cerr << "Invalid message format " << line << std::endl;
                    ++discarded;
                    break;
                }

                ob.on_order_insert(oid, side, price, size);
                ++processed;
                break;
            }
            case 'X':
            {
                if ( sscanf( line.c_str(), "%c,%lx,%c,%d,%lf", &action, &oid, &side, &size, &price ) < 5 )
                {
                    std::cerr << "Cannot parse line " << line << std::endl;
                    ++discarded;
                    break;
                }

                if ( oid < 0 || LTZ(price) || size < 0 || ( side != 'B' && side != 'S' ) )
                {
                    std::cerr << "Invalid message format " << line << std::endl;
                    ++discarded;
                    break;
                }

                ob.on_order_remove(oid, side, price, size);
                ++processed;
                break;
            }
            case 'M':
            {
                if ( sscanf( line.c_str(), "%c,%lx,%c,%d,%lf", &action, &oid, &side, &size, &price ) < 5 )
                {
                    std::cerr << "Cannot parse line " << line << std::endl;
                    ++discarded;
                    break;
                }

                if ( oid < 0 || LTZ(price) || size < 0 || ( side != 'B' && side != 'S' ) )
                {
                    std::cerr << "Invalid message format " << line << std::endl;
                    ++discarded;
                    break;
                }

                ob.on_order_modify(oid, side, price, size);
                ++processed;
                break;
            }
            case 'T':
            {
                if ( sscanf( line.c_str(), "%c,%d,%lf", &action, &size, &price ) < 3 )
                {
                    std::cerr << "Cannot parse line " << line << std::endl;
                    ++discarded;
                    break;
                }

                if ( LTZ(price) || size < 0 )
                {
                    std::cerr << "Invalid message format " << line << std::endl;
                    ++discarded;
                    break;
                }

                // ob.on_trade(price, size);
                ++processed;
                break;
            }
            default:
                std::cerr << "Unknown action " << action << std::endl;
                break;
            }
        }

        if ( ++counter % 10 == 0 )
        {
            // std::cout << ob << std::endl;
            counter = 0;
        }

        std::cout << "midquote: " << ob.get_mid_price() << std::endl;
    }

    // std::cout << ob << std::endl;

    std::cout << "Processed " << processed << " message(s), discarded " << discarded << " message(s)." << std::endl;

    std::cout << "Average message processing time " << line_pf.get_average_time() * 1000000000 << " ns, "
              << "max " << line_pf.get_max_time() * 1000000000 << " ns, "
              << "min " << line_pf.get_min_time() * 1000000000 << " ns."
              << std::endl;

    return 0;
}
