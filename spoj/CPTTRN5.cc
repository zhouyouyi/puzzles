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
		
        for(i = 0; i < row*(h+1)+1; ++i)
        {
            for(j = 0; j < col*(h+1)+1; ++j)
            {
                if(i % (h+1) == 0 || j % (h+1) == 0)
                    cout << '*';
                else if( ( (i/(h+1)) + (j/(h+1)) ) % 2 == 0 )
                {
                    if( i % (h+1) == j % (h+1) )
                        cout << '\\';
                    else
                        cout << '.';
                }
                else
                {
                    if( (i+j) % (h+1) == 0 )
                        cout << '/';
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
