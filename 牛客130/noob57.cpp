#include<iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i++){
        s[i] = (s[i]-96 + n) % 26 + 96;
        if(s[i] == 96) s[i] ='z';
    }
    cout << s;
}