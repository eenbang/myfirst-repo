#include <iostream>
#include <string>
#include <limits>
#include <unordered_map>

int main(){
    int N;
    std::unordered_map <std::string,int> mp;
    std::cin >> N;
    std::cin.ignore();
    std::string s;
    for(int i = 0; i < N; i++){
        std::getline(std::cin,s);
        mp[s] = i;
    }
    std::cout << mp.size();
}
