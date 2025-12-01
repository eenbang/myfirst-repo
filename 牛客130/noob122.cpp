#include <iostream>
#include <unordered_map>
#include <cmath>
int main(){
    int n;
    std::unordered_map <unsigned long long,unsigned long long> mp;
    std::cin >> n;
    unsigned long long x,y;
    unsigned long long sum = 0;
    for(int i = 0; i < n; i++){
        std::cin >> x >> y;
        sum += (i+1) * mp[x];
        mp[x] = y;
    }
    std::cout << sum ;
}