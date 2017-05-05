#include <iostream>
#include <thread>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <memory>
#include <string>

using namespace std;

void runner( int id, int ntimes, int nchars, const char * str, int len, int rd, int wr )
{
    while( ntimes-- )
    {
        int pos;

        // block here
        if ( read( rd, &pos, sizeof(pos) ) > 0 )
        {
            std::cout << "Thread" << id << ": ";

            int i;
            for( i = 0; i < nchars; ++i )
            {
                std::cout << str[ (pos+i) % len ];
            }

            std::cout << std::endl;

            pos = (pos+nchars) % len;

            // trigger next event
            write( wr, &pos, sizeof(pos) );
        }
    }
}

int main(int argc, char * argv[])
{
    if( argc != 5 )
    {
        std::cerr << "usage: " << argv[0] << " <string> <nchar> <nthread> <k>" << std::endl;
        return -1;
    }

    const std::string str = argv[1];

    int nchar = std::atoi( argv[2] );

    if ( nchar <= 0 )
    {
        std::cerr << "nchar must be positive" << std::endl;
        return -1;
    }

    int nthread = std::atoi( argv[3] );

    if ( nthread <= 0 )
    {
        std::cerr << "nthreah must be positive" << std::endl;
        return -1;
    }

    int K = std::atoi( argv[4] );

    if ( K <= 0 )
    {
        std::cerr << "K must be positive" << std::endl;
        return -1;
    }

    std::vector<int> rdq, wrq;

    int i;
    for ( i = 0; i < nthread; ++i )
    {
        int pfd[2];

        if( pipe(pfd) == -1 )
        {
            perror("pipe");
            return -1;
        }

        rdq.push_back( pfd[0] );
        wrq.push_back( pfd[1] );
    }

    // shift write queue
    wrq.push_back( wrq.front() );
    wrq.erase(wrq.begin());

    // create threads
    typedef std::shared_ptr< std::thread > thread_ptr_t;
    typedef std::vector< thread_ptr_t > thread_ptr_vec_t;

    thread_ptr_vec_t threads;
    for ( i = 0; i < nthread; ++i )
    {
        threads.push_back( thread_ptr_t(new std::thread( runner, i+1, K, nchar, str.c_str(), str.size(), rdq[i], wrq[i] )) );
    }

    // kick off event chain
    int pos = 0;
    write( wrq.back(), &pos, sizeof(pos) );

    // join all threads
    for ( i = 0; i < nthread; ++i )
        threads[i]->join();

    return 0;
}
