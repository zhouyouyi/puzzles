/*
  ID: zhou.yo1
  PROG: castle
  LANG: C++
*/

#define PROG "castle"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

const static int W = 0x1;
const static int N = 0x2;
const static int E = 0x4;
const static int S = 0x8;

typedef vector< vector<bool> > visited_t;
typedef vector< vector<int> > matrix_t;
typedef pair<int, int> node_t;
typedef deque<node_t> node_queue_t;

matrix_t castle;
matrix_t component;
visited_t visited;

vector<int> room_size;

int largest_room = 0;
int largest_new_room = 0;
int num_room = 0;

node_t room;
int wall_to_go;

char to_char( int d )
{
    switch(d)
    {
    case 0x1: return 'W';
    case 0x2: return 'N';
    case 0x4: return 'E';
    case 0x8: return 'S';
    }
}

void find_new_room(int row, int col)
{
    int i, j;
    for(j = 1; j <= col; ++j)
    {
        for(i = row; i >= 1; --i)
        {
            int wall = castle[i][j];

            if( (wall & N) != 0 && i - 1 > 0 && component[i][j] != component[i-1][j] )
            {
                int a = room_size[ component[i][j] ] + room_size[ component[i-1][j] ];
                if( a > largest_new_room )
                {
                    largest_new_room = a;

                    room.first = i;
                    room.second = j;
                    wall_to_go = N;
                }
            }
            if( (wall & E) != 0 && j + 1 <= col && component[i][j] != component[i][j+1] )
            {
                int a = room_size[ component[i][j] ] + room_size[ component[i][j+1] ];
                if( a > largest_new_room )
                {
                    largest_new_room = a;

                    room.first = i;
                    room.second = j;
                    wall_to_go = E;
                }
            }
            // if( (wall & S) != 0 && i + 1 <= row && component[i][j] != component[i+1][j] )
            // {
            //     int a = room_size[ component[i][j] ] + room_size[ component[i+1][j] ];
            //     if( a > largest_new_room )
            //     {
            //         largest_new_room = a;

            //         room.first = i;
            //         room.second = j;
            //         wall_to_go = S;
            //     }
            // }
            // if( (wall & W) != 0 && j - 1 > 0 && component[i][j] != component[i][j-1] )
            // {
            //     int a = room_size[ component[i][j] ] + room_size[ component[i][j-1] ];
            //     if( a > largest_new_room )
            //     {
            //         largest_new_room = a;

            //         room.first = i;
            //         room.second = j;
            //         wall_to_go = W;
            //     }
            // }
        }
    }
}

void assign_component(int row, int col)
{
    int i, j;
    int comp = 0;
    for(i = 1; i <= row; ++i)
    {
        for(j = 1; j <= col; ++j)
        {
            if( ! visited[i][j] )
            {
                comp++;
                node_queue_t q;

                q.push_back( node_t(i, j) );

                component[i][j] = comp;

                int area = 0;

                while( q.size() > 0 )
                {
                    node_t n = q.front(); q.pop_front();

                    if( visited[n.first][n.second] ) continue;

                    visited[n.first][n.second] = true;

                    area++;

                    int wall = castle[n.first][n.second];

                    int ni = n.first;
                    int nj = n.second;

                    if( (wall & W) == 0 && nj - 1 > 0 && ! visited[ni][nj-1] )
                    {
                        q.push_back( node_t(ni, nj-1) );
                        component[ni][nj-1] = comp;
                    }
                    if( (wall & N) == 0 && ni - 1 > 0 && ! visited[ni-1][nj] )
                    {
                        q.push_back( node_t(ni-1, nj) );
                        component[ni-1][nj] = comp;
                    }
                    if( (wall & E) == 0 && nj + 1 <= col && ! visited[ni][nj+1] )
                    {
                        q.push_back( node_t(ni, nj+1) );
                        component[ni][nj+1] = comp;
                    }
                    if( (wall & S) == 0 && ni + 1 <= row && ! visited[ni+1][nj] )
                    {
                        q.push_back( node_t(ni+1, nj) );
                        component[ni+1][nj] = comp;
                    }
                }

                room_size[comp] = area;

                largest_room = max( largest_room, area );
                num_room = comp;
            }
        }
    }

#ifdef LOCAL
    cout << "---- COMPONENT ----" << endl;
    for(i = 1; i <= row; ++i)
    {
        for(j = 1; j <= col; ++j)
        {
            cout << setw(4) << component[i][j];
        }
        cout << endl;
    }
    cout << "---- ROOM ----" << endl;
    for(i = 1; i <= comp; ++i)
    {
        cout << setw(4) << room_size[i];
    }
    cout << endl;
#endif
}

void solve( istream& fin, ostream& out )
{
    int col, row;
    int i, j;
    fin >> col >> row;

    castle.resize( row+1, vector<int>(col+1) );
    component.resize( row+1, vector<int>(col+1, -2) );
    visited.resize( row+1, vector<bool>(col+1, false) );

    room_size.resize( (col+1)*(row+1)+1, 0 );

    for(i = 1; i <= row; ++i)
    {
        for(j = 1; j <= col; ++j)
        {
            fin >> castle[i][j];
        }
    }

    assign_component( row, col );

    find_new_room( row, col );

    out << num_room << endl;
    out << largest_room << endl;
    out << largest_new_room << endl;
    out << room.first << ' ' << room.second << ' ' << to_char(wall_to_go) << endl;
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

#ifdef LOCAL
  solve( cin, cout );
#else
  solve( fin, out );
#endif

  return 0;
}
