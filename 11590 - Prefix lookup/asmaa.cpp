struct trie_node {

  // how many nodes are beneath this one?
  int count;

  // array of pointers to children
  trie_node *child_list[ALPH_SIZE];

  // initializer...
  trie_node();
};

trie_node::trie_node() {

  // there is nothing below us...
  count = 0;

  // all child pointers start out pointing nowhere...
  for(int index = 0; index < ALPHABET_SIZE; index++)
    child_list[index] = NULL;
}



class Trie {

public:

  // methods

  Trie(int level, int chars);        // create it
  ~Trie();                           // destroy trie nodes
  int node_count;                    // the number of nodes in whole trie
  void AddToTrie(const string \&s);   // add string to trie

private:

  // methods

  void recursive_delete (trie_node * t);     // recursive delete helper function



  // data

  int node_count;                      // number of nodes in the trie
  trie_node * Root;                  // the root of the trie
};




Trie::Trie() {
  node_count = 0;
  Root(new trie_node);
}


Trie::~Trie() {

  // delete whole trie
  recursive_delete(myRoot);
}


void Trie::recursive_delete(trie_node * t) {
  int index;

  if (t != NULL) {

    // delete all children
    for(index = 0; index < ALPHABET_SIZE; index++)
      recursive_delete(t->child_list[index]);

    // delete self
    delete t;
  }
}




int Trie::node_count() {

  return (node_count);

}



void Trie::AddToTrie(const string \&s) {
  int lcv, index;

  trie_node *t = Root;

  // there is one more string stored somewhere under the root...
  t->count++;


  // loop over the length of the string to add and traverse the trie...
  for(lcv=0; lcv < s.length(); lcv++) {

    index = s[lcv]; // the character in s we are processing...

    // is there a child node for this character?
    if (t->child_list[index] == NULL) {

      // if not, make one!
      t->child_list[index] = new trie_node;
      node_count++;
    }

    // there is another string under this node...
    t->child_list[index]->count++;

    // move to it this node... and loop
    t = t->child_list[index];
  }
}

int N, M;


int main(){
  while (cin >> N >> M && (N || M)){
    Trie t;
    unsigned long long i;
    string str;
    for(i=0; i<N; i++)
      {
        cin>>str;
        str = str.substr(0, str.size() - 1);        //to remove the *
        t.AddToTrie(str);
      }
    cin>>N;
    for(i=0; i<N; i++)
      {
        trie_node *r = t.Root;                     //I must keep the root of the Trie because I will change it later.
        cin>>str;
        str = str.substr(0, str.size() - 1);
        unsigned long long  j = 0;
        for(j=0; j<str.size(); j++)
          {
            t.Root = t.Root->child_list[str[j] - '0'];
          }
        unsigned long long  res = t.Find(str, 1);
        cout<<res<<endl;
        t.Root = r;                              //go back to the original root.
      }
    cout<<endl;
  }
  return 0;
}
