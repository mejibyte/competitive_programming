using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

bool doUnify;

bool isFunctor(string hash){
	int n = hash.size();
	if (n <= 3) return false;
	if (hash[0] < 'a' || hash[0] >'z') return false;
	for (int i = 1; i < n; i++){
		if (hash[i] == '('){
			return true;
		}
		if (hash[i] == ','){
			return false;
		}
	}
	return false;
}

string getFun(string hash){
	int n = hash.size();
	string ans = "";
	for (int i = 0; i < n; i++){
		if (hash[i] == '(') break;
		ans += hash[i];
	}
	return ans;
}
vector <string> getArgs (string hash){
	int n = hash.size();
	vector <string> args;
	string arg = "";
	bool paren = false;
	
	queue <char> p;
	for (int i = 0; i < n - 1; i++){
		if (hash[i] == ')'){
			p.pop();
		}
		
		if (hash[i] == ',' && p.size() == 0){
			args.push_back(arg);
			arg = "";
		}else{
			if(paren) arg += hash[i];
		}
		
		if (hash[i] == '('){
			if (!paren){
				paren = true;
			}else{
				p.push('(');
			}
		}
		if (i == n - 2) args.push_back(arg);
	}
	return args;
}

bool isVar(string hash){
	if(hash[0] < 'A' || hash[0] > 'Z') return false;
	return true;
}

bool isConst(string hash){
	if (isVar(hash) || isFunctor(hash)) return false;
	return true;
}

bool occurs(string var, string hash){
	if (hash.find(var) == string::npos) return false;
	return true;
}

vector<pair<string, string> > unify (string hash1, string hash2){
	vector <pair<string, string> > ans;
	// Verify if they already unify
	if (!doUnify) return ans;
	
	int n1 = hash1.size();
	int n2 = hash2.size();
	if (n1 == 0 || n2 == 0) return ans;
	// Unify functors
	if (isFunctor(hash1) and isFunctor(hash2)){
		if (getFun(hash1) == getFun(hash2)){
			//Unify arguments
			vector <string> v1 = getArgs(hash1);
			vector <string> v2 = getArgs(hash2);
			if (v1.size() != v2.size()){
				doUnify = false;
				return ans;
			}			
			for (int i = 0; i < v1.size(); i++){
				vector <pair<string, string> > vect = unify(v1[i], v2[i]);
				if (!doUnify) return ans;
				for (int j = 0; j < vect.size(); j++){
					ans.push_back(vect[j]);
				}
			}
		}else{
			doUnify = false;
			return ans;
		}
	}else{
		// Unify variable and constant
		if(isVar(hash1) && isConst(hash2)){
			ans.push_back(make_pair(hash1, hash2));
			return ans;
		}
		if(isVar(hash2) && isConst(hash1)){
			ans.push_back(make_pair(hash2, hash1));
			return ans;
		}
		// Unify variable and variable/ functor
		if(isVar(hash1) and !isConst(hash2)){
			if (occurs(hash1, hash2)){
				if(hash1 == hash2) return ans;
				doUnify = false;
				return ans;
			}
			ans.push_back(make_pair(hash1, hash2));
			return ans;
		}
		if(isVar(hash2) and !isConst(hash1)){
			if (occurs(hash2, hash1)){
				doUnify = false;
				return ans;
			}
			ans.push_back(make_pair(hash2, hash1));
			return ans;
		}
		// Unify two constants
		if (isConst(hash1) && isConst(hash2)){
			if(hash1 != hash2) doUnify = false;
			return ans;
		}
		// Unify a constant and a functor
		doUnify = false;
		return ans;
	}
	return ans;
}
string replce(string oc, string str, string rep){
	while(str.find(oc) != string::npos){
		int pos = str.find(oc);
		str.replace(pos, oc.size(), rep);
	}
	return str;
}

vector<pair<string, string> > make_replacements( vector<pair<string,string> > v ){
	int n = v.size();
	for (int i = 0; i < n; i++){
		string var = v[i].first;
		string rep = v[i].second;
		for (int j = 0; j < n; j++){
			if (j == i) continue;
			//If the variable is in the first term
			if (v[j].first == var){
				string second = v[j].second;
				if (!isVar(second)){
					v.erase (v.begin()+j);
					//Erase it and add the unification of the other varibles
					vector<pair<string, string> > unif = unify(rep, second);
					for (int k = 0; k < unif.size(); k++){
						v.push_back(unif[k]);
					}
				}else if(!isVar(rep)){
					v[j].second = rep;
					v[j].first = second;
				}else{
					v[j].first = rep;
				}
			}
			//If the variable is in the second term
			if (occurs(var, v[j].second) ){
				if (occurs(v[j].first, rep)){
					doUnify = false;
					return v;
				}
				v[j].second = replce(var, v[j].second, rep);
			}
			if (!doUnify) break;
		}
		if (!doUnify) break;
	}
	return v;
}


int main(){
	string name;
	int n;
	
	//CHEQUEO
	/*doUnify = true;
	vector< pair<string, string> > v = unify("f(f(X),Z)","f(f(Y), c)");
	for (int i = 0; i < v.size(); i++){
		printf("%s / %s\n", v[i].first.c_str(), v[i].second.c_str());
	}*/
	
	while (cin >> name >> n){
		if (n == 0) break;
		string hash [n];
		for (int i = 0; i < n; i++) cin >> hash[i];
	
	vector<pair<string, string> > unifiers [n - 1];
	
	for (int i = 0; i < n - 1; i++){
		doUnify = true;
		unifiers[i] = unify(hash[i], hash[i+1]);
		//Make replacements with unifiers
		if (doUnify) unifiers[i] = make_replacements(unifiers[i]);
		if (!doUnify) break;
	}
	/*for (int i = 0; i < n - 1; i++){
		int n = unifiers[i].size();
		printf("El unificador %d es:\n", i);
		for (int j = 0; j < n; j++){
			printf("%s / %s\n", (unifiers[i][j].first).c_str(), (unifiers[i][j].second).c_str());
		}
	}*/
	if (doUnify){
		vector <pair<string, string> > joint = unifiers[0];
		for (int i = 1; i < n - 1; i++){
			for (int k = 0; k < unifiers[i].size(); k++){
				for (int j = 0; j < joint.size(); j++){
					// Make replacement
					if (occurs(unifiers[i][k].first, joint[j].second)){
						if(occurs(joint[j].first, unifiers[i][k].second) ){
							doUnify = false;
							break;
						}else{
							joint[j].second = replce( unifiers[i][k].first, joint[j].second, unifiers[i][k].second );
						}
					}
				}
				if (!doUnify) break;
				for (int j = 0; j < joint.size(); j++){
					if(unifiers[i][k].first == joint[j].first){
						unifiers[i].erase(unifiers[i].begin()+k);
						break;
					}
				}
			}
			if (!doUnify) break;
			for (int k = 0; k < unifiers[i].size(); k++){
				joint.push_back(unifiers[i][k]);
			}
			int n = joint.size();
			/*printf("El unificador %d conjunto es:\n", i);
			for (int j = 0; j < n; j++){
				printf("%s / %s\n", (joint[j].first).c_str(), (joint[j].second).c_str());
			}*/
		}
	}
	
	if (!doUnify){
		printf("%s is a Starflyer agent\n", name.c_str());
	}else{
		printf("analysis inconclusive on %s\n", name.c_str());
	}

	
	}
    return 0;
}