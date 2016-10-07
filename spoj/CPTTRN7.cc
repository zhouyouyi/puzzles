#include <iostream>
using namespace std;

int main()
{	
    int ncase;
	
    cin >> ncase;
	
    while(ncase--)
    {
        int row, col, h;
		
        cin >> row >> col >> h;
		
        int i, j, k;
		
        for(i = 1; i <= row*2*h; ++i)
        {
            for(j = 1; j <= col*2*h; ++j)
            {
                if( ( ((i-1)/h) + ((j-1)/h) ) % 2 == 0 )
                {
                    if( h == 1 || (i+j) % (h) == 1 )
                        cout << '/';
                    else
                        cout << '.';
                }
                else
                {
                    if( i % (h) == j % (h) )
                        cout << '\\';
                    else
                        cout << '.';
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    
    return 0;
}
