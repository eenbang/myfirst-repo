#include <iostream>
using namespace std;

int main(){
    string s;
    cin >> s;
    int r=0,g=0,b = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'R') r++;
        else if(s[i] == 'G') g++;
        else b++;
    }
    cout << '(' << r << ',' << g << ',' << b << ')';
}