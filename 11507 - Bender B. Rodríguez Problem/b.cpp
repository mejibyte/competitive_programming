/*
  Accepted
*/
#include<iostream>
#include<string>
#include<cassert>

using namespace std;
int encode(string s){
    if(s=="+y") return 0;
    if(s=="-y") return 1;
    if(s=="+z") return 2;
    if(s=="-z") return 3;
    return -100;
}
string decode(int n){
    if(n==0)return "+y";
    if(n==1)return "-y";
    if(n==2)return "+z";
    if(n==3)return "-z";
    if(n==4)return "+x";
    if(n==5)return "-x";
    assert(0);
}
int main(){    int move[6][4]={{5,4,0,0},
                    {4,5,1,1},
                    {2,2,5,4},
                    {3,3,4,5},
                    {0,1,2,3},
                    {1,0,3,2}};
    int n;
    while(cin>>n &&n){
         int s=4;
         string in;
         for(int i=1;i<n;++i){
             cin>>in;
             if(in!="No"){
                s=move[s][encode(in)];          
             }
         }
         cout<<decode(s)<<endl;
    }
    return 0;
}
