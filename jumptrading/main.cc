#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>

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

    std::vector<double> quantiles;

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

        if( line_pf.get_count() ) quantiles.push_back( line_pf.get_time() * 1e9 );

        PROFILE(line_pf)
        {
            switch( action )
            {
            case 'A':
            {
                if ( sscanf( line.c_str()+2, "%lx,%c,%d,%lf", &oid, &side, &size, &price ) < 4 )
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
                if ( sscanf( line.c_str()+2, "%lx,%c,%d,%lf", &oid, &side, &size, &price ) < 4 )
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
                if ( sscanf( line.c_str()+2, "%lx,%c,%d,%lf", &oid, &side, &size, &price ) < 4 )
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
                if ( sscanf( line.c_str()+2, "%d,%lf", &size, &price ) < 2 )
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

                ob.on_trade(price, size);
                ++processed;
                break;
            }
            default:
                std::cerr << "Unknown action " << action << std::endl;
                break;
            }
        }

        if ( action == 'T' )
        {
            std::cout << line << " => " << ob.last_volume() << "@" << ob.last_price() << std::endl;
        }

        if ( ++counter % 10 == 0 )
        {
            std::cout << ob << std::endl;
            counter = 0;
        }

        std::cout << "midquote: " << ob.get_mid_price() << std::endl;
    }

    std::cout << ob << std::endl;

    std::cerr << "Processed " << processed << " message(s), discarded " << discarded << " message(s)." << std::endl;

    std::cerr << "Average message processing time " << line_pf.get_average_time() * 1000000000 << " ns, "
              << "max " << line_pf.get_max_time() * 1000000000 << " ns, "
              << "min " << line_pf.get_min_time() * 1000000000 << " ns."
              << std::endl;

    std::sort( quantiles.begin(), quantiles.end() );
    std::cerr << "Quantiles:"
              << " 25% -> " << quantiles[ int(quantiles.size() * 0.25) ]
              << " 50% -> " << quantiles[ int(quantiles.size() * 0.5) ]
              << " 75% -> " << quantiles[ int(quantiles.size() * 0.75) ]
              << " 90% -> " << quantiles[ int(quantiles.size() * 0.9) ]
              << " 95% -> " << quantiles[ int(quantiles.size() * 0.95) ]
              << " 99% -> " << quantiles[ int(quantiles.size() * 0.99) ]
              << std::endl
        ;

    return 0;
}
