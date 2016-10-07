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
		
		int i, j, k;
		
		for(i = 0; i < row*3+1; ++i)
		{
			for(j = 0; j < col*3+1; ++j)
			{
				if(i % 3 == 0 || j % 3 == 0)
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
