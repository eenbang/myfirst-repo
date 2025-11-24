#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    string s,res;
    cin >> s;
    int num = s.size();
    for(int i = num-1; i >= 0 ; i--){
        if((num - 1 - i) % 3 == 0 && (num - 1- i) != 0) res+=',';
        res+= s[i];
    }
    reverse(res.begin(),res.end());
    cout << res;
}