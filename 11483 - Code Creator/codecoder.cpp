#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int cases;
    string header="#include<string.h>\n#include<stdio.h>\nint main()\n{\n";
    string cola="printf(\"\\n\");\nreturn 0;\n}\n";
    int n=0;
    while(cin >> cases && cases){
        cout<<"Case "<<++n<<":"<<endl;
        cout<<header;
        string ans;
        getline(cin,ans);
        while(cases--){
             getline(cin,ans);
             if(ans==""){
                         cases++;
                         continue;
                         
                         }
             for(int i=0;i<ans.size();++i){
                     //cout<<"debug"<<endl;
                  if(ans[i]=='\\'){
                        ans.insert(i+1,"\\");
                        ++i;            
                  }else if(ans[i]=='"'){
                        //ans[i]='';
                        ans.insert(i,"\\");
                        ++i;
                  }else if(ans[i]=='"'){
                        ans.insert(i,"\\");
                        ++i;
                  }
             }
             cout<<"printf(\""<<ans<<"\\n\");"<<endl;
        }
        cout<<cola;
    }
    //getchar();
    return 0;
}
