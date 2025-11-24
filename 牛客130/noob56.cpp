#include<iostream>

using namespace std;

int main(){
    string S;
    bool note = false;
    int i;
    cin >> S;
    for( i = 0; i+2 < S.size(); i++){
        if((S[i]=='B'||S[i]=='b') && (S[i+1]=='o'||S[i+1]=='O') && (S[i+2]=='b'||S[i+2]=='B')){    
            note = true;
            break;
        } 
    }
    if(!note) cout << -1;
    else cout << i;
}