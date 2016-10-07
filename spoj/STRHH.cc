#include <iostream>
using namespace std;
 
int main() {
	
	// your code here
	int N;
	
	cin >> N;
	
	while(N--)
	{
		string S;
		cin >> S;
		
		int i;
		
		for(i = 0; i < N/2; i += 2)
		{
			cout << S[i];
		}
		cout << endl;
	}
 
	return 0;
} 
