#include <iostream>
using namespace std;

int main()
{	
    int ncase;
	
    cin >> ncase;
	
    while(ncase--)
    {
        int row, col, h, w;
		
        cin >> row >> col >> h >> w;
		
        int i, j, k;
		
        for(i = 0; i < row*(h+1)+1; ++i)
        {
            for(j = 0; j < col*(w+1)+1; ++j)
            {
                if(i % (h+1) == 0 || j % (w+1) == 0)
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
