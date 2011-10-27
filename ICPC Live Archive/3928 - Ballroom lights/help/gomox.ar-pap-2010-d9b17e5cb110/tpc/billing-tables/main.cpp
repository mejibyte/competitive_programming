#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <stdio.h>

using namespace std;

#define forsn(i, s, n)	for (int i = (s); i < (n); i++)
#define forn(i, n)	forsn (i, 0, n)
#define dforn(i, n)	for (int i = (n); i-- > 0;)

#define ALPHA_SIZE	10
#define ALPHA_VAL(C)	((C) - '0')
#define foralpha(x)	forn (x, ALPHA_SIZE)

typedef unsigned long long int lluint;

typedef const string *Value;

string itos(lluint i, int width) {
	if (width == 0) return "";
	ostringstream os;
	os << setw(width) << setfill('0') << i;
	return os.str();
}

/**** String register ****/

set<string> _reg;

Value reg_intern(const string& s) {
	return &*_reg.insert(s).first;
}

void reg_free() {
	_reg = set<string>();
}

/**** Trie ****/

struct Node {
	Node *children[ALPHA_SIZE];
	Value value;
};

typedef Node *Trie;
#define trie_new()	NULL
#define Empty		NULL

void trie_free(Trie tr) {
	if (!tr) return;
	foralpha (dig) {
		trie_free(tr->children[dig]);
	}
	delete tr;
}

void _trie_delete_children(Trie tr) {
	foralpha (dig) if (tr->children[dig]) {
		trie_free(tr->children[dig]);
		tr->children[dig] = NULL;
	}
}

void _trie_collapse_children(Trie tr) {
	if (!tr->children[0] || tr->children[0]->value == Empty) return;
	foralpha (dig) {
		if (!tr->children[dig]) return;
		if (tr->children[dig]->value != tr->children[0]->value) return;
	}

	tr->value = tr->children[0]->value;
	_trie_delete_children(tr);
}

// invariante: los valores estan en las hojas
void trie_add(Trie *tr, const char *s, Value v) {
	if (*tr == NULL) {
		*tr = new Node();
		foralpha (dig) (*tr)->children[dig] = NULL;
		(*tr)->value = Empty;
	}
	if (!*s) {
		(*tr)->value = v;
		_trie_delete_children(*tr);
	} else {
		if ((*tr)->value != Empty) {
			foralpha (dig) {
				trie_add(&(*tr)->children[dig], "", (*tr)->value);
			}
			(*tr)->value = Empty;
		}
		trie_add(&(*tr)->children[ALPHA_VAL(*s)], &s[1], v);

		_trie_collapse_children(*tr);
	}
}

bool trie_has_children(Trie tr) {
	foralpha (dig) {
		if (tr->children[dig] == NULL) continue;
		return true;
	}
	return false;
}

void trie_debug(Trie tr, int depth) {
	if (!tr) return;
	foralpha (dig) {
		if (!tr->children[dig]) continue;
		forn (i, depth) { cout << " "; }
		cout << itos(dig, 1);
		if (tr->children[dig]->value) {
			cout << "  (" << *(tr->children[dig]->value) << ")";
		}
		cout << endl;
		trie_debug(tr->children[dig], depth + 1);
	}
}

/**** Resultado ****/

typedef pair<string, Value> ResultItem;
vector<ResultItem> result;
Value Invalid;

#define _produce(S, V)		if ((V) != Invalid) { result.push_back(ResultItem((S), (V))); }
#define Maxlen 20
char prefix_buf[Maxlen];
void _build_result_rec(Trie tr, int prefix_length) {
	if (tr == NULL) return;
	if (!trie_has_children(tr)) {
		// no children
		prefix_buf[prefix_length] = '\0';
		_produce(string(prefix_buf), tr->value);
	} else {
		// visit the children
		foralpha (dig) {
			prefix_buf[prefix_length] = '0' + dig;
			_build_result_rec(tr->children[dig], prefix_length + 1);
		}
	}
}

void trie_print_result(Trie tr) {
	Invalid = reg_intern("invalid");
	result = vector<ResultItem>();

	if (!trie_has_children(tr) && tr->value != Empty && tr->value != Invalid) {
		// special case: every prefix has the same type
		printf("%d\n",ALPHA_SIZE);
		foralpha (dig) {
			printf("%d %s\n",dig,(*tr->value).c_str());
		}
	} else {
		_build_result_rec(tr, 0);

		printf("%d\n",result.size());
		forn (i, (int)result.size()) {
			printf("%s %s\n",result[i].first.c_str(),(*result[i].second).c_str());
		}
	}
}

/**** Intervalos ****/

#define IMP(X, Y)	(!(X) || (Y))
void add_interval(Trie *tr, int pref_size, lluint from, lluint to, Value val) {
	lluint pot = 1;
	forn (t, 2) {
		lluint *from_to = (t == 0 ? &from : &to);
		while (pot > 0 && IMP(t == 0, from + pot <= to)) {
			while (from + pot <= to && *from_to % (pot * 10) > 0) {
				string element(itos(from / pot, pref_size));
				trie_add(tr, element.c_str(), val);
				from += pot;
			}
			if (t == 0) {
				pot *= 10;
				pref_size--;
			} else {
				pot /= 10;
				pref_size++;
			}
		}
		if (t == 1) break;
		while (from + pot > to) { pot /= 10; pref_size++; }
	}
}

lluint atoll_(string s) {
	lluint r = 0;
	forn (i, s.size()) {
		r = 10 * r + ALPHA_VAL(s[i]);
	}
	return r;
}

/**** Main ****/

struct InputItem {
	int pref_size;
	lluint from, to;
	Value name_id;
};
int main() {
	bool primero = true;
	while (true) {
		int nlines;
		cin >> nlines;
		if (cin.eof()) break;

		if (primero) {
			primero = false;
		} else {
			printf("\n");
		}

		vector<InputItem> todo_list;

		// Read the lines and build the todo list
		forn (line, nlines) {
			string from, sep, to, name;
			cin >> from >> sep >> to >> name;

			int k = from.size() - to.size();
			InputItem item;
			item.name_id = reg_intern(name);
			item.from = atoll_(from);
			item.to = atoll_(from.substr(0, k) + to) + 1;
			item.pref_size = from.size();

			todo_list.push_back(item);
		}

		// Process the lines in reverse order
		Trie tr = trie_new();
		dforn (i, nlines) {
			InputItem& item(todo_list[i]);
			add_interval(&tr, item.pref_size, item.from, item.to, item.name_id);
		}

		trie_print_result(tr);
		trie_free(tr);
		reg_free();
	}

	return 0;
}
