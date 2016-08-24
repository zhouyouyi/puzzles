/*
  ID: zhou.yo1
  PROG: NAME
  LANG: C++
*/

#define PROG NAME

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

void solve( istream& fin, ostream& out )
{
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

#ifdef LOCAL
  solve( cin, cout );
#else
  solve( fin, out );
#enfif

  return 0;
}
