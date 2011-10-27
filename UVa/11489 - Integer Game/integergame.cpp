#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
int main(){
    string bigint;
    int cases=1;
    int mod;
    int n3;
    int n;
    cin>>n;
    string winner="TS";
    while(n-- && cin>>bigint){
        printf("Case %d: ",cases++);
        mod=0;
        n3=0;
        for(int i=0;i<bigint.size();++i){
            mod=(mod+(bigint[i]-'0')%3)%3;
            if((bigint[i]-'0')%3==0) ++n3;
        }
        bool empiezan=false;
        if(mod!=0){
             for(int i=0;i<bigint.size();++i){
                 if((bigint[i]-'0')%3==mod){
                      ++n3;
                      empiezan=true;
                      break;
                 }
             }
        }else{
              empiezan=true;
        }
        if(empiezan)   cout<<winner[n3%2]<<endl;
        else cout<<"T"<<endl;
    }
    return 0;
}
