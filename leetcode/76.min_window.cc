#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> count(128, 0);
        int head = 0, tail = 0, ans_head = 0, ans_tail = numeric_limits<int>::max();
        int min_len = t.size();
        for(auto c : t)
        {
            count[c]++;
        }
        
        while(tail < s.size())
        {
            if(count[s[tail++]]-- > 0) min_len--;
            
            while(min_len == 0)
            {
                // cout << "extend " << head << ' ' << tail << endl;
                if(tail - head < ans_tail - ans_head)
                {
                    ans_head = head;
                    ans_tail = tail;
                }
                if(count[s[head++]]++ == 0) min_len++;
            }
        }
        
        return (ans_tail == numeric_limits<int>::max() ? "" : s.substr(ans_head, ans_tail-ans_head));
    }
};

int main()
{
    string s, t;

    Solution sol;

    while(cin >> s >> t)
    {
        cout << sol.minWindow(s, t) << endl;
    }

    return 0;
}
