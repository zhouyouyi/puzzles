#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    unordered_map<string, vector<string> > cache;
    
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        if(cache.count(s)) return cache[s];
        int N = s.size();
        int i;
        
        //cout << s << endl;
        
        vector<string> rs;
        
        if(wordDict.count(s))
        {
            rs.push_back(s);
        }
        
        for(i = 1; i <= N; ++i)
        {
            string word = s.substr(0, i);
            
            if(wordDict.count(word))
            {
                if(i < N)
                {
                    vector<string> t = wordBreak(s.substr(i), wordDict);
                    
                    for(int j = 0; j < t.size(); ++j)
                    {
                        //cout << t[j] << endl;
                        t[j] = word + " " + t[j];
                    }
                    
                    rs.insert(rs.end(), t.begin(), t.end());
                }
            }
        }
        
        cache[s] = rs;
        
        return rs;
    }
};

int main()
{
    unordered_set<string> dict;
    string w, s;

    cin >> s;

    while(cin >> w)
    {
        dict.insert(w);
    }

    Solution sol;

    for(auto i : sol.wordBreak(s, dict))
    {
        cout << i << endl;
    }

    return 0;
}
