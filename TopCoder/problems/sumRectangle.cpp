#include <vector>
#include <set>
#include <string>
using namespace std;

int strings[] = {7, 0, 5, 10, 2, 7};
string names[] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "G", "G#"};

struct WhatsThisChord {
	string classify(vector<int> chord){
		set<int> notes;
		for (int i = 0; i < chord.size(); ++i){
			if (chord[i] != -1){
			    notes.insert( ( chord[i] + strings[i] ) % 12 );
			}
		}
		if (notes.size() != 3) return "";
		

		
		for (int i = 0; i < 12; ++i){
		  set<int> major; major.insert((0 + i) % 12), major.insert((4 + i) % 12), major.insert((7 + i) % 12);
		  set<int> minor; minor.insert((0 + i) % 12), minor.insert((3 + i) % 12), minor.insert((7 + i) % 12);
		  if (major == notes) return names[i] + " Major";
		  if (minor == notes) return names[i] + " Minor";
		}
		return "";
	}
};
