/*
ID: zhou.yo1
PROG: ride
LANG: C++
*/

#include <fstream>
#include <string>

using namespace std;

int main()
{
  ofstream fout("ride.out");
  ifstream fin("ride.in");

  string a, b;
  fin >> a >> b;

  int A = 1, B = 1;
  int i;

  for ( i = 0; i < a.size(); ++i )
  {
    A *= ( a[i] - 'A' + 1 );
  }

  for ( i = 0; i < b.size(); ++i )
  {
    B *= ( b[i] - 'A' + 1 );
  }

  if ( (A % 47) == (B % 47) )
    fout << "GO" << endl;
  else
    fout << "STAY" << endl;

  return 0;
}
