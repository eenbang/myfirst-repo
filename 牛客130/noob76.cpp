#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

vector<int> vec;

int main(){
    int input = 0;
    int q = 0;
    int x=-1,i=-1;
    cin >> q;
    while(q--){
        cin >> input;
        if(input == 1){
            cin >> x; vec.push_back(x); 
        }
        if(input == 2){
            if(!vec.empty()) vec.pop_back();
        }
        if(input == 3){
            cin >> i; cout << vec[i] << endl;
        }
        if(input == 4){
            cin >> i >> x;
            vec.push_back(0);
            for(int j = vec.size() - 2; j >= i + 1; j--) vec[j+1] = vec[j];
            vec[i + 1] = x;
        }
        if(input == 5){
            sort(vec.begin(),vec.end());
        }
        if(input == 6){
            sort(vec.begin(),vec.end());
            reverse(vec.begin(),vec.end());
        }
        if(input == 7){
            cout << vec.size() << endl;
        }
        if(input == 8){
            for(int i = 0; i < vec.size(); i++) cout << vec[i] << " ";
            cout << endl;
        }
    }
}

