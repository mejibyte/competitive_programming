#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

#define MOD 1000000009LL

using namespace std;

vector <string> song;
vector <string> artist;
map <string, int> artistIdx;

int songHash[31][31][31];
int artistHash[10][31][31];

bool uniqueSongSubstr[31][31][31];

map <int, int> songHashCnt;

vector <string> uniqueArtists;
map < int, vector <int> > artistsWithHash;
set <int> artistHashes[10][31];

vector <int> songCnt;
vector < vector <int> > songsByArtist;

vector <int> uniqueHashes[31][31];
vector <int> uniqueHashesArtist[31][31];

int main()
{
  // freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);
    
    int N;
    while(cin>>N)
    {
        if(!N) break;
        
        song = vector <string> (N);
        artist = vector <string> (N);
        
        uniqueArtists.clear();
        artistsWithHash.clear();
        songCnt.clear();
        songsByArtist.clear();
        
        artistIdx.clear();
        songHashCnt.clear();
        
        for(int i=0; i<N; i++)
            for(int j=0; j<=30; j++)
                uniqueHashes[i][j].clear();

        for(int i=0; i<N; i++)
            for(int j=0; j<=30; j++)
                uniqueHashesArtist[i][j].clear();
        
        for(int i=0; i<10; i++)
            for(int j=0; j<=30; j++)
                artistHashes[i][j].clear();
              
        int nArtist = 0;
        for(int i=0; i<N; i++)
        {
            cin>>song[i]>>artist[i];
            if(artistIdx.find(artist[i]) == artistIdx.end()) 
            {
                artistIdx[artist[i]] = nArtist++;
                uniqueArtists.push_back(artist[i]);
                songCnt.push_back(1);
                songsByArtist.push_back(vector <int> (1, i));
            }
            else
            {
                songCnt[artistIdx[artist[i]]]++;
                songsByArtist[artistIdx[artist[i]]].push_back(i);
            }
        }
        
        // artists
        for(int i=0; i<uniqueArtists.size(); i++)
        {
            set <int> hashes;
            
            for(int j=0; j<uniqueArtists[i].size(); j++)
            {
                long long hash = 0;
                for(int k=j; k<uniqueArtists[i].size(); k++)
                {
                    hash = (256*hash + uniqueArtists[i][k]) % MOD;
                    artistHash[i][j][k] = hash;
                    hashes.insert(hash);
                    artistHashes[i][k-j+1].insert(hash);
                }
            }
            
            //artistHashes[i] = hashes;
            
            set <int> :: iterator it;
            for(it = hashes.begin(); it != hashes.end(); it++)
                artistsWithHash[*it].push_back(i);
        }
        
        // songs
        for(int i=0; i<N; i++)
        {
            set <int> hashes;
            
            for(int j=0; j<song[i].size(); j++)
            {
                long long hash = 0;
                for(int k=j; k<song[i].size(); k++)
                {
                    hash = (256*hash + song[i][k]) % MOD;
                    songHash[i][j][k] = hash;
                    hashes.insert(hash);
                }
            }
            
            set <int> :: iterator it;
            for(it = hashes.begin(); it != hashes.end(); it++)
                songHashCnt[*it]++;
        }
        
        // uniqueHashes Song
        for(int i=0; i<N; i++)        
            for(int j=0; j<song[i].size(); j++)
                for(int k=j; k<song[i].size(); k++)
                    if(songHashCnt[songHash[i][j][k]] == 1)
                        uniqueHashes[i][k-j+1].push_back(songHash[i][j][k]);

        // uniqueHashes Artist
        for(int i=0; i<uniqueArtists.size(); i++)        
            for(int j=0; j<uniqueArtists[i].size(); j++)
                for(int k=j; k<uniqueArtists[i].size(); k++)
                    if(songHashCnt[artistHash[i][j][k]] == 0)
                        uniqueHashesArtist[i][k-j+1].push_back(artistHash[i][j][k]);
                        
        int maxSongs = 0, minS = 1<<30;
        
        for(int mask = 0; mask < (1<<nArtist); mask++)
        {
            int sum = 0, cnt = 0;
            
            int sSum[10] = {};
            int sCnt[10] = {};
            int maxT[10] = {};
            
            for(int i=0; i<N; i++)
            {
                int myArtist = artistIdx[artist[i]];
                
                int minT = 1<<30;
                
                for(int T=1; T<=song[i].size(); T++)
                {
                    bool ok = 0;
                    
                    for(int j=0; j<uniqueHashes[i][T].size(); j++)
                    {
                        ok = 1;
                        
                        for(int ii=0; ii<nArtist; ii++)
                        {
                            if((mask & (1<<ii)) && artistHashes[ii][T].find(uniqueHashes[i][T][j]) != artistHashes[ii][T].end())
                            {
                                ok = 0;
                                break;
                            }
                        }
                        
                        if(ok) break;
                    }
                    
                    if(ok)
                    {
                        sSum[myArtist] += T;
                        sCnt[myArtist]++;
                        maxT[myArtist] = max(maxT[myArtist], T);
                        
                        minT = T;
                        sum += T;
                        cnt++;
                        break;
                    }
                }
            }
            
            for(int ii=0; ii<nArtist; ii++)
            {
                if(mask & (1<<ii))
                {
                    if(sCnt[ii] < songCnt[ii])
                    {
                        for(int T=1; T<=uniqueArtists[ii].size(); T++)
                        {
                            bool found = 0;
                            
                            for(int j=0; j<uniqueHashesArtist[ii][T].size(); j++)
                            {
                                bool valid = 1;
                                for(int jj=0; jj<nArtist; jj++)
                                {
                                    if((mask & (1<<jj)) && ii != jj && artistHashes[jj][T].find(uniqueHashesArtist[ii][T][j]) != artistHashes[jj][T].end())
                                    {
                                        valid = 0;
                                        break;
                                    }
                                }
                                if(valid)
                                {
                                    found = 1;
                                    break;
                                }
                            }
                            
                            if(found)
                            {
                                sum+=T;
                                cnt++;
                                break;
                            }                         
                        }
                    }
                    else if(sCnt[ii] == songCnt[ii])
                    {
                        for(int T=1; T<=uniqueArtists[ii].size(); T++)
                        {
                            bool found = 0;
                            
                            for(int j=0; j<uniqueHashesArtist[ii][T].size(); j++)
                            {
                                bool valid = 1;
                                for(int jj=0; jj<nArtist; jj++)
                                {
                                    if((mask & (1<<jj)) && ii != jj && artistHashes[jj][T].find(uniqueHashesArtist[ii][T][j]) != artistHashes[jj][T].end())
                                    {
                                        valid = 0;
                                        break;
                                    }
                                }
                                if(valid)
                                {
                                    found = 1;
                                    break;
                                }
                            }
                            
                            if(found && maxT[ii] > T)
                            {
                                sum -= (maxT[ii] - T);
                                //cnt++;
                                break;
                            }                         
                        }                        
                    }
                }
            }
            
            if(cnt > maxSongs)
            {
                maxSongs = cnt;
                minS = sum;
            }
            else if(cnt == maxSongs) minS = min(minS, sum);
            
        }
        
        cout<<minS<<endl;
    }
    return 0;
}
