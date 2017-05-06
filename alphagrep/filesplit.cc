#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <cstdio>
#include <cstdlib>

struct record_t
{
    std::string line;
    std::vector<record_t*> children;

    record_t( const std::string& l ) : line(l) {}
};

void display( record_t * root )
{
    std::deque<record_t*> queue;

    queue.push_back( root );

    while( queue.size() > 0 )
    {
        root = queue.front(); queue.pop_front();

        std::cout << root->line << std::endl;

        for(int i = 0; i < root->children.size(); ++i)
            queue.push_back( root->children[i] );
    }
}

int count( record_t * root )
{
    int rs = 1;
    std::deque<record_t*> queue;

    queue.push_back( root );

    while( queue.size() > 0 )
    {
        root = queue.front(); queue.pop_front();

        rs += root->children.size();

        for(int i = 0; i < root->children.size(); ++i)
            queue.push_back( root->children[i] );
    }

    return rs;
}

void output( record_t* root, int fileno )
{
    std::ostringstream oss;

    oss << "output_" << fileno << ".txt";

    std::ofstream ofs( oss.str().c_str() );

    std::deque<record_t*> queue;

    queue.push_back( root );

    while( queue.size() > 0 )
    {
        root = queue.front(); queue.pop_front();

        ofs << root->line << std::endl;

        for(int i = 0; i < root->children.size(); ++i)
            queue.push_back( root->children[i] );
    }
}

int main(int argc, char * argv[])
{
    if ( argc != 3 )
    {
        std::cerr << "usage: " << argv[0] << " <file> <X>" << std::endl;
        return -1;
    }

    int X = std::atoi( argv[2] );

    typedef std::unordered_map< int, record_t* > record_map_t;
    record_map_t records;

    std::string line;

    std::ifstream ifs( argv[1] );

    while( std::getline( ifs, line ) )
    {
        std::cout << line << std::endl;

        char type;
        int rid, prid;

        type = line[0];

        int pos = line.rfind( ',' );
        prid = std::atoi( line.c_str()+pos+1 );
        pos = line.rfind( ',', pos-1 );
        rid = std::atoi( line.c_str()+pos+1 );

        std::cout << type << " " << rid << " " << prid << std::endl;

        record_t * rec;
        record_map_t::iterator iter = records.find( rid );

        if ( iter != records.end() )
        {
            iter->second->line = line;
            rec = iter->second;
        }
        else
        {
            rec = new record_t( line );
            records[ rid ] = rec;
        }

        iter = records.find( prid );

        if ( iter != records.end() )
        {
            iter->second->children.push_back( rec );
        }
        else
        {
            records[ prid ] = new record_t("");
            records[ prid ]->children.push_back( rec );
        }
    }

    display( records[0] );

    int fileno = 1;

    for(int i = 0; i < records[0]->children.size(); ++i)
    {
        int cnt = count( records[0]->children[i] );
        std::cout << records[0]->children[i]->line << " " << cnt << std::endl;

        if( cnt >= X )
        {
            output( records[0]->children[i], fileno++ );
        }
    }

    ifs.close();

    return 0;
}
    
