namespace Fasta {
    // Returns a list of strings read until EOF
    // in the FASTA format.
    // The first item is the name, and the second
    // item is the actual content.
    vector< pair<string, string> > read() {
        vector< pair<string, string> > ans;
        string s;
        cin >> s;
        while (!cin.eof()) {
                string name = s.substr(1);
                string dna = "";
                while (cin >> s and s[0] != '>') dna += s;
                ans.push_back( make_pair(name, dna) );
        }
        return ans;
    }
}

namespace DNA {
    // Returns the reverse complement of the DNA string s.
    string reverse_complement(const string &s) {
        string ans = s;
        reverse(ans.begin(), ans.end());
        int at = 'A' ^ 'T';
        int cg = 'C' ^ 'G';
        for (int i = 0; i < ans.size(); ++i) {
            if (ans[i] == 'A' or ans[i] == 'T') ans[i] ^= at;
            else if (ans[i] == 'C' or ans[i] == 'G') ans[i] ^= cg;
            else throw "Invalid DNA string. All characters must be one of GACT.";
        }
        return ans;
        
    }
}