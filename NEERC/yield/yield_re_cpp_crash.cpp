#include <fstream>
#include <utility>

using namespace std;

int main() {
	ifstream in("yield.in");
	ofstream out("yield.out");
	pair<int,int> p;
	in >> p.first >> p.second;
	int sum = 0;
	sum = p.first / sum;
	out << sum << endl;
	return 0;
}
