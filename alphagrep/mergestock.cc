#include <iostream>
#include <vector>
#include <deque>
#include <limits>
#include <cstdint>

// for epoll
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

class merge_stock_t
{
public:
    merge_stock_t( int N );
    ~merge_stock_t() {}

    // add a new stock number V from exchange E
    void push( uint32_t E, uint64_t V );

    // remove the min stock number
    int pop();

    // test if the heap is valid, i.e. all N exchanges have sent at least one stock each
    bool is_valid() const;

    // mark an exchange is done sending data
    void mark_done( uint32_t E );

    bool all_done() const { return m_nExchange == 0; }

    bool empty() const { return m_heap.size() == 1; }

private:
    typedef std::deque<uint64_t> data_list_t;
    typedef std::vector<data_list_t> data_list_vec_t;
    typedef std::vector<int> heap_t; // stores the index of data_list_vec_t

    int m_nExchange;
    data_list_vec_t m_data_lists;
    heap_t m_heap;

    std::vector<bool> m_flag; // marks if an exchange is ready to read
    int m_nReady; // how many exchanges have already sent data
};

merge_stock_t::merge_stock_t(int N)
    : m_nExchange( N )
    , m_data_lists( N+1 )
    , m_flag( N+1, false )
    , m_nReady( 0 )
{
    m_heap.push_back( std::numeric_limits<int>::min() );
}

void merge_stock_t::push( uint32_t E, uint64_t V )
{
    m_data_lists[E].push_back(V);

    if ( !m_flag[E] )
    {
        m_flag[E] = true;
        m_nReady++;

        m_heap.push_back(E);

        int now = m_heap.size()-1;

        while ( now/2 && m_data_lists[m_heap[now/2]].front() > m_data_lists[E].front() )
        {
            m_heap[now] = m_heap[now/2];
            now /= 2;
        }

        m_heap[now] = E;
    }

    while ( is_valid() )
    {
        // pop heap and print
        std::cout << pop() << std::endl;
    }
}

int merge_stock_t::pop()
{
    uint64_t minval = m_data_lists[m_heap[1]].front();
    m_data_lists[m_heap[1]].pop_front();

    if ( m_data_lists[m_heap[1]].size() > 0 )
    {
        m_heap.push_back( m_heap[1] );
    }
    else
    {
        m_flag[ m_heap[1] ] = false;
        m_nReady--;
    }
    int pos = m_heap.size() - 1;
    int child, now;
    int lastind = m_heap[pos--];

    for( now = 1; now * 2 <= pos; now = child )
    {
        child = now * 2;

        if ( child != pos && m_data_lists[m_heap[child+1]].front() < m_data_lists[m_heap[child]].front() )
        {
            child++;
        }

        if ( m_data_lists[lastind].front() > m_data_lists[m_heap[child]].front() )
        {
            m_heap[now] = m_heap[child];
        }
        else
        {
            break;
        }
    }

    m_heap[now] = lastind;

    m_heap.pop_back();

    return minval;
}

bool merge_stock_t::is_valid() const
{
    return m_nReady == m_nExchange;
}

void merge_stock_t::mark_done(uint32_t E)
{
    m_flag[E] = false;
    m_nReady--;
    m_nExchange--;
}

static int make_socket_non_blocking (int sfd)
{
    int flags, s;

    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1)
    {
        perror ("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags);
    if (s == -1)
    {
        perror ("fcntl");
        return -1;
    }
    
    return 0;
}

static int create_and_bind (char *port)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;

    memset (&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
    hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
    hints.ai_flags = AI_PASSIVE;     /* All interfaces */

    s = getaddrinfo (NULL, port, &hints, &result);
    if (s != 0)
    {
        fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
        return -1;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

        s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
        if (s == 0)
        {
            /* We managed to bind successfully! */
            break;
        }

        close (sfd);
    }
    
    if (rp == NULL)
    {
        fprintf (stderr, "Could not bind\n");
        return -1;
    }

    freeaddrinfo (result);

    return sfd;
}

int main (int argc, char *argv[])
{
    int sfd, s;
    int efd;
    struct epoll_event event;
    struct epoll_event *events;

    if (argc != 3)
    {
        fprintf (stderr, "Usage: %s port N\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    const int NEXCHANGE = atoi( argv[2] );
    const int MAXEVENTS = NEXCHANGE + 2;

    sfd = create_and_bind (argv[1]);
    if (sfd == -1)
        abort ();

    s = make_socket_non_blocking (sfd);
    if (s == -1)
        abort ();

    s = listen (sfd, SOMAXCONN);
    if (s == -1)
    {
        perror ("listen");
        abort ();
    }

    efd = epoll_create1 (0);
    if (efd == -1)
    {
        perror ("epoll_create");
        abort ();
    }

    event.data.fd = sfd;
    event.events = EPOLLIN | EPOLLET;
    s = epoll_ctl (efd, EPOLL_CTL_ADD, sfd, &event);
    if (s == -1)
    {
        perror ("epoll_ctl");
        abort ();
    }

    /* Buffer where events are returned */
    events = (struct epoll_event*)calloc (MAXEVENTS, sizeof event);

    merge_stock_t mq( NEXCHANGE );

    /* the event loop */
    while ( ! mq.all_done() )
    {
        int n, i;

        n = epoll_wait (efd, events, MAXEVENTS, -1);
        for (i = 0; i < n; i++)
	{
            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN)))
	    {
                /* An error has occured on this fd, or the socket is not
                   ready for reading (why were we notified then?) */
                fprintf (stderr, "epoll error\n");
                close (events[i].data.fd);
                continue;
	    }

            else if (sfd == events[i].data.fd)
	    {
                /* We have a notification on the listening socket, which
                   means one or more incoming connections. */
                while (1)
                {
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd;
                    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

                    in_len = sizeof in_addr;
                    infd = accept (sfd, &in_addr, &in_len);
                    if (infd == -1)
                    {
                        if ((errno == EAGAIN) ||
                            (errno == EWOULDBLOCK))
                        {
                            /* We have processed all incoming
                               connections. */
                            break;
                        }
                        else
                        {
                            perror ("accept");
                            break;
                        }
                    }

                    s = getnameinfo (&in_addr, in_len,
                                     hbuf, sizeof hbuf,
                                     sbuf, sizeof sbuf,
                                     NI_NUMERICHOST | NI_NUMERICSERV);
                    /* Make the incoming socket non-blocking and add it to the
                       list of fds to monitor. */
                    s = make_socket_non_blocking (infd);
                    if (s == -1)
                        abort ();

                    event.data.fd = infd;
                    event.events = EPOLLIN | EPOLLET;
                    s = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
                    if (s == -1)
                    {
                        perror ("epoll_ctl");
                        abort ();
                    }
                }
                continue;
            }
            else
            {
                /* We have data on the fd waiting to be read. Read and
                   display it. We must read whatever data is available
                   completely, as we are running in edge-triggered mode
                   and won't get a notification again for the same
                   data. */
                int done = 0;
                
                while (1)
                {
                    struct packet_t
                    {
                        uint32_t exchange;
                        uint64_t stock;
                    };
                    ssize_t count;
                    packet_t buf;

                  count = read (events[i].data.fd, &buf, sizeof buf);
                  if (count == -1)
                  {
                      /* If errno == EAGAIN, that means we have read all
                         data. So go back to the main loop. */
                      if (errno != EAGAIN)
                      {
                          perror ("read");
                          done = 1;
                      }
                      break;
                  }
                  else if (count == 0)
                  {
                      /* End of file. The remote has closed the
                         connection. */
                      done = 1;
                      break;
                  }

                  if ( buf.stock )
                      mq.push( buf.exchange, buf.stock );
                  else
                  {
                      mq.mark_done(buf.exchange);
                  }
                  
                }

                if (done)
                {
                    /* Closing the descriptor will make epoll remove it
                       from the set of descriptors which are monitored. */
                    close (events[i].data.fd);
                }
            }
        }
    }

    while ( ! mq.empty() )
    {
        std::cout << mq.pop() << std::endl;
    }
    
    free (events);

    close (sfd);

    return EXIT_SUCCESS;
}
