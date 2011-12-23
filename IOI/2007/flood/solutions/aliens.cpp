#include <map>
#include <algorithm>

#include <cstdio>
#include <cstring>
#define SOLUTIONCOMMAND		"solution"
#define EXAMINECOMMAND		"examine"
void Initialize ( int *N, int *x0, int *y0 )
{
	scanf ("%d%d%d", N, x0, y0); 
}

int Rose ( int X, int Y )
{
	printf( "%s %d %d\n", EXAMINECOMMAND, X, Y );
	fflush( stdout );

	char answer[10];
	scanf ("%s", answer);

	return strcmp(answer, "true") == 0;
}

void Solution ( int X, int Y )
{
	printf( "%s %d %d\n", SOLUTIONCOMMAND, X, Y );
	fflush( stdout );
}


using namespace std;

int n, x0, y0;


int query(int x, int y) {
  if (x < 1 || x > n || y < 1 ||  y > n)
    return 0;
  return Rose(x, y);
}


int find_first_white(int dx, int dy) {
  int i = 0;
  while (query(x0+(dx<<i)-dx, y0+(dy<<i)-dy))
    i++;

  int lo = (1<<(i-1))-1;
  int hi = (1<<i)-1;
  while (lo+1 < hi) {
    int mid = (lo+hi)/2;
    if (query(x0+mid*dx, y0+mid*dy))
      lo = mid;
    else
      hi = mid;
  }
  return hi;
}


int main() {
  Initialize(&n, &x0, &y0);

  int left = find_first_white(0, -1);
  int right = find_first_white(0, 1);
  int up = find_first_white(-1, 0);

  int side_length = right+left-1;
  int squares_left = find_first_white(0, -2*side_length);
  int squares_right = find_first_white(0, 2*side_length);
  int squares_up = find_first_white(-2*side_length, 0);

  int edge_left = y0-left+1-(squares_left-1)*2*side_length;
  int edge_up = x0-up+1-(squares_up-1)*2*side_length;

  if (squares_left+squares_right-1 != 3) {
    edge_left -= side_length;
    edge_up -= side_length;
  }

  Solution(edge_up+5*side_length/2, edge_left+5*side_length/2);

  return 0;
}
