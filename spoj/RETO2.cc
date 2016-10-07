#include <iostream>
#include <algorithm>
using namespace std;
 
int main() {
	
	// your code here
	
	long long L1, R1, L2, R2, K;
	
	cin >> L1 >> R1 >> L2 >> R2 >> K;
	
	long long L = max(L1, L2);
	long long R = min(R1, R2);
	
	if(K < L || K > R)
		cout << max((long long)0L, R - L + 1) << endl;
	else
		cout << max((long long)0L, R - L) << endl;
 
	return 0;
} 
