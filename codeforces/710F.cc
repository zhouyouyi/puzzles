#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct trie_node_t
{
    bool is_word;
    struct trie_node_t* children[26];

    trie_node_t() : is_word(false) { for(int i = 0; i < 26; ++i) children[i] = NULL; }
};

trie_node_t ROOT;
set<string> S;

void insert( trie_node_t * root, const string& s )
{
    for(int i = 0; i < s.size(); ++i)
    {
        int c = s[i] - 'a';

        if( root->children[c] == NULL )
        {
            root->children[c] = new trie_node_t;
        }

        root = root->children[c];
    }

    root->is_word = true;
}

void remove( trie_node_t * root, const string& s )
{
    for(int i = 0; i < s.size(); ++i)
    {
        int c = s[i] - 'a';

        root = root->children[c];
    }

    root->is_word = false;
}

long count( trie_node_t * root, const string& s )
{
    long ans = 0;
    if( S.size() < 100 )
    {
        set<string>::iterator it = S.begin();
        for(; it != S.end(); ++it)
        {
            string::size_type next_pos = 0;

            while( ( next_pos = s.find( *it, next_pos ) ) != string::npos )
            {
                ans++;
                next_pos ++;
            }
        }

        return ans;
    }
    for(int start = 0; start < s.size(); ++start)
    {
        trie_node_t * n = root;

        for(int i = start; i < s.size(); ++i)
        {
            int c = s[i] - 'a';

            if( n->children[c] )
            {
                n = n->children[c];

                if( n->is_word ) ans++;
            }
            else
            {
                break;
            }
        }
    }

    return ans;
}

int main()
{
    int N;
    cin >> N;
    string s;
    int i, q;
    for(i = 0; i < N; ++i)
    {
        cin >> q >> s;

        if( q == 1 ) { insert( &ROOT, s ); S.insert(s); }
        else if ( q == 2 ) { remove( &ROOT, s ); S.erase(s); }
        else if ( q == 3 ) cout << count( &ROOT, s ) << endl;
    }
    return 0;
}
