#include <iostream>
using namespace std;

int main() {
	
	// your code here
	
	int ncase;
	
	cin >> ncase;
	
	while(ncase--)
	{
		int row, col;
		
		cin >> row >> col;
		
		int start = 0;
		int i, j, k;
		
		for(i = 0; i < row; ++i)
		{
			start = 1 - start;
			for(j = 0, k = start; j < col; ++j, k = 1 - k)
			{
				if(k)
					cout << '*';
				else
					cout << '.';
			}
			cout << endl;
		}
		cout << endl;
	}

	return 0;
}
