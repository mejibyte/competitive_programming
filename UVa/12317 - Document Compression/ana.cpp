// Code written by Ana Echavarría
using namespace std;
#include <iostream>
#include <vector>
#include <queue>

// Maximum base size is 2^16 - 1
const int maxN = 1 << 16;
int length [maxN];

int main(){
	int nBases, nDocs;
	while(cin >> nBases >> nDocs){
		if  (nBases == 0 and nDocs == 0) break;
		//Initialize length
		for (int i = 0; i < maxN; i++) length[i] = -1;
		// Read the bases
		vector <int> bases(nBases, 0);
		for (int b = 0; b < nBases; b++){
			int k; cin >> k;
			while(k--){
				int num; cin >> num;
				bases[b] |= 1 << (num-1);
			}
		}
		// Read the documents
		vector <int> docs(nDocs, 0);
		for (int d = 0; d < nDocs; d++){
			int k; cin >> k;
			while(k--){
				int num; cin >> num;
				docs[d] |= 1 << (num-1);
			}
		}
		// Start BFS
		queue <int> q;
		q.push(0);
		length[0] = 0;
		while(q.size() > 0){
			int curr = q.front();
			q.pop();
			for (int i = 0; i < bases.size(); i++){
				// Build next document
				int next = curr | bases[i];
				// Check if it has not been visited yet
				if (length[next] >= 0) continue;
				length[next] = length[curr] + 1;
				q.push(next);	
			}
		}
		// Print answers
		for (int d = 0; d < docs.size(); d++){
			int document = docs[d];
			if (length[document] >= 0) cout << length[document];
			else cout << 0;
			if (d < docs.size() - 1) cout << " ";
			else cout << endl;
		}
		
	}
	
    return 0;
}
