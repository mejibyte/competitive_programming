// Andrés Mejía
// Accepted, slightly shorter version of juke.3.cpp.

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
#include <bitset>
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

int total_songs, total_artists;

int song_hash[30][30][30];
int artist_hash[6][30][30];

string songs[30];
string artists[6];
int artist_of_song[30];

map<string, int> artist_id;

map<int, int> songs_with_hash;
map<int, int> artists_with_hash;

const int oo = 1000000;

int find_shortest_golden_string_for_song(int s, int remain) {
    // find the shortest string in this song that doesn't appear in one of the remaining artists or in any other song
    for (int len = 1; len <= songs[s].size(); ++len) {
        for (int i = 0; i + len - 1 < songs[s].size(); ++i) {
            int hash = song_hash[s][i][i + len - 1];

            assert(songs_with_hash[hash] > 0);
            if (songs_with_hash[hash] != (1 << s)) continue; // this hash is in at least one other song
            if ((artists_with_hash[hash] & remain) != 0) continue; // is in an artist
            // we found a golden string for song s
            return len;
        }
    }
    // Nothing found, so return something huge
    return oo;
}

int best_improvement_after_assigning_artist(int a, int remain, const vector<int> &longest_for_artist, const vector<int> &golden_string) {
    for (int len = 1; len <= artists[a].size(); ++len) {
        for (int i = 0; i + len - 1 < artists[a].size(); ++i) {
            int hash = artist_hash[a][i][i + len - 1];

            assert(artists_with_hash[hash] > 0);
            if ((artists_with_hash[hash] & remain) != (1 << a)) continue; // ths substring is in two artists
            if (songs_with_hash.count(hash) == 0) {
                // assign to any of my songs, namely to the one with the longest golden string
                return -longest_for_artist[a] + len; // take back the longest golden string of one of my songs and add my length.
            } else {
                if (__builtin_popcount(songs_with_hash[hash]) > 1) continue; // doesn't work
                int song = __builtin_ctz(songs_with_hash[hash]);
                if (artist_of_song[song] != a) continue; // this artist can't be assigned to this song, because the song has a different artist!
                // Since is the only option, we have to assign this artist to that song.
                return -golden_string[song] + len; // take back the golden string if the only song I can be assigned to and add my length.
            }
        }
    }
    return 0; // This artist didn't help at all.
}

int solve() {
    int ans = oo;
    for (int remain = 0; remain < (1 << total_artists); ++remain) {
        int option = 0;
        vector<int> golden_string(total_songs); // length of golden string of song i
        vector<int> longest_for_artist(total_artists, -1); // length of the longest golden string of one of this artist's songs

        // For every song s, add up the "pessimistic" golden string of s.
        // That's the golden string for for song s assuming I didn't assign 
        // s's artist to s but to another song (with the same artist of s).
        for (int s = 0; s < total_songs; ++s) {
            int len = find_shortest_golden_string_for_song(s, remain);

            golden_string[s] = len;
            option += len;
            
            int my_artist = artist_of_song[s];
            if (len > longest_for_artist[my_artist]) {
                longest_for_artist[my_artist] = len;
            }
        }
        
        // Now, for every artist, try to assign it to one of its songs.
        // This will most likely improve the "pessimistic" golden string
        // we chose before, so we are going to take that back and add
        // the artist's golden string instead.
        for (int a = 0; a < total_artists; ++a) {
            if ((remain & (1 << a)) == 0) continue; // this artist goes away, so ignore it
            option += best_improvement_after_assigning_artist(a, remain, longest_for_artist, golden_string);
        }
        
        // covered_songs has the songs that got a valid golden string.
        // If there's at least one that didn't have a valid golden string,
        // just try the next subset of artists.
        ans = min(option, ans);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    while (cin >> total_songs) {
        if (total_songs == 0) break;

        total_artists = 0;
        artist_id.clear();
        songs_with_hash.clear();
        artists_with_hash.clear();

        for (int i = 0; i < total_songs; ++i) {
            string artist;
            cin >> songs[i] >> artist;
            if (artist_id.count(artist) == 0) {
                artists[total_artists] = artist;
                artist_id[artist] = total_artists++;
            }
            artist_of_song[i] = artist_id[artist];
        }
        
        for (int s = 0; s < total_songs; ++s) {
            const string &song = songs[s];
            for (int i = 0; i < song.size(); ++i) {
                int hash = 12579;
                for (int j = i; j < song.size(); ++j) {
                    hash = 33 * hash + song[j];
                    song_hash[s][i][j] = hash;
                    
                    songs_with_hash[hash] |= (1 << s);
                }
            }
        }

        for (int a = 0; a < total_artists; ++a) {
            const string &artist = artists[a];
            for (int i = 0; i < artist.size(); ++i) {
                int hash = 12579;
                for (int j = i; j < artist.size(); ++j) {
                    hash = 33 * hash + artist[j];
                    artist_hash[a][i][j] = hash;
                    
                    artists_with_hash[hash] |= (1 << a);
                }
            }
        }
        
        cout << solve() << endl;
    }
    return 0;
}