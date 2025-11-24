#include<iostream>
#include<cctype>

using namespace std;
int main(){
    string s,shortS;
    getline(cin , s);
    shortS = toupper(s[0]);
    for(int i = 0; i < s.size(); i++){
        if(s[i] == ' ') shortS += toupper(s[i+1]);
    }
    cout << shortS;

}