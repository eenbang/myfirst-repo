#include <iostream>
#include <vector>
#include <algorithm>
int main(){
    std::vector <int> vec;
    int n,k;
    int num = 0;
    std::cin >> n >> k;
    int sum = 0;
    for(int i = 0; i < n; i++){
        int t;
        std::cin >> t;
        sum+=t;
        vec.push_back(t);
    }
    int minvalue = sum;
    for(int i = 0; i < k + 1; i++){
        int temp = 0;
        for(int j = 0; j < n - k; j++){
            temp += vec[i+j];
        }
        minvalue = std::min(minvalue,temp);
    }
    std::cout << sum-minvalue;
    
}