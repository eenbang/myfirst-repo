#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector  <int> vec;
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        vec.push_back(t);
    }
    sort(vec.begin(),vec.end());
    for(int i = 0; i < n; i ++){
        cout << vec[i] << ' ';
    }
}