#include <fstream>
#include <utility>

using namespace std;

int main() {
	ifstream in("yield.in");
	ofstream out("yield.out");
	pair<int,int> p;
	in >> p.first >> p.second;
	out << (p.first + p.second) << endl;
	return 0;
}
