#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class contact_book_t
{
    public:
    contact_book_t() {}
    
    void add(const std::string& name);
    int  find(const std::string& name);
    
    protected:
    struct trie_node_t
    {
        int subcount; // count of all descending nodes
        
        struct trie_node_t* parent; // for easier back-trace
        struct trie_node_t* children[26];
        
        trie_node_t() : subcount(0), parent(NULL)
        {
            std::fill(children, children+26, (trie_node_t*)(NULL));
        }
    };
    
    trie_node_t root; // fake root to make life easier
};

void contact_book_t::add(const std::string& name)
{
    int i;
    trie_node_t * t = &root;
    trie_node_t * parent = root.parent;
    for(i = 0; i < name.size(); ++i)
    {
        parent = t;
        t = t->children[name[i]-'a'];
        
        if(t == NULL)
        {
            parent->children[name[i]-'a'] = new trie_node_t;
            
            t = parent->children[name[i]-'a'];
            
            t->parent = parent;
        }
    }
    
    while(t)
    {
        t->subcount++;
        t = t->parent;
    }
}

int contact_book_t::find(const std::string& name)
{
    int i;
    trie_node_t * t = &root;
    
    for(i = 0; i < name.size(); ++i)
    {
        t = t->children[name[i]-'a'];
        
        if(t == NULL) return 0;
    }
    
    return t->subcount;
}

contact_book_t book;

int main(){
    int n;
    cin >> n;
    for(int a0 = 0; a0 < n; a0++){
        string op;
        string contact;
        cin >> op >> contact;
        
        if(op == "add") book.add(contact);
        else if(op == "find") cout << book.find(contact) << endl;
    }
    return 0;
}
