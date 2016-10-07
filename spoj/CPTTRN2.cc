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
		
		for(i = 0; i < row; ++i)
		{
			for(j = 0; j < col; ++j)
			{
				if(i == 0 || i == row-1 || j == 0 || j == col-1)
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
