#include <iostream>
#include <vector>

typedef struct _node
{
    int val;
    struct _node * prev;
    struct _node * next;

    _node(int v) : val(v), prev(NULL), next(NULL) {}
} node_t;

class version_queue_t
{
public:
    version_queue_t() : root(NULL), last(NULL), curver(0)
    {
        // version 0 is empty queue
        heads.push_back(root);
        tails.push_back(last);
    }

    ~version_queue_t()
    {
        while( root )
        {
            node_t * t = root->next;
            delete root;
            root = t;
        }
    }

    void enqueue( int val );

    int  dequeue();

    void print(int ver);

protected:
    // non-copyable
    version_queue_t( const version_queue_t& ) {}
    version_queue_t& operator = ( const version_queue_t& ) { return *this; }

protected:
    node_t * root, * last;
    int curver;
    std::vector<node_t*> heads;
    std::vector<node_t*> tails;
};

void version_queue_t::enqueue(int val)
{
    curver++;

    node_t * n = new node_t(val);

    if ( root == NULL )
    {
        root = n;
        last = n;

        heads.push_back( root );
        tails.push_back( last );
    }
    else
    {
        last->next = n;
        n->prev = last;

        last = last->next;

        if ( heads.back() == NULL )
            heads.push_back( n );
        else
            heads.push_back( heads.back() );
        tails.push_back( last );
    }
}

int version_queue_t::dequeue()
{
    curver++;

    if ( heads.back() == NULL )
    {
        heads.push_back( NULL );
        tails.push_back( NULL );

        return 0;
    }
    else if ( heads.back() == tails.back() )
    {
        int val = heads.back()->val;
        heads.push_back( NULL );
        tails.push_back( NULL );

        return val;
    }
    else
    {
        int val = heads.back()->val;

        heads.push_back( heads.back()->next );
        tails.push_back( tails.back() );

        return val;
    }
}

void version_queue_t::print(int ver)
{
    if( ver >= heads.size() )
    {
        return;
    }

    node_t * h = heads[ver], * t = tails[ver];

    while( h && t && h != t )
    {
        std::cout << h->val << " ";
        h = h->next;
    }

    if ( h )
        std::cout << h->val;
    std::cout << std::endl;
}

int main()
{
    using namespace std;

    int N;

    cin >> N;

    version_queue_t Q;

    while( N-- )
    {
        char op;

        cin >> op;

        switch( op )
        {
        case 'e':
        {
            int val;
            cin >> val;
            Q.enqueue( val );
            break;
        }
        case 'd':
            Q.dequeue();
            break;
        case 'p':
        {
            int ver;
            cin >> ver;
            Q.print(ver);
            break;
        }
        default:
            break;
        }
    }

    return 0;
}
