#include <iostream>
#include <vector>
#include <algorithm>
int main(){
    std::vector<int> s1,s2;
    int horse = -1;
    for(int i = 0; i < 3; i++){
        std::cin >> horse;
        s1.push_back(horse);
    }
    for(int i = 0; i < 3; i++){
        std::cin >> horse;
        s2.push_back(horse);
    }
    std::sort(s1.begin(),s1.end());
    std::sort(s2.begin(),s2.end());
    if(s2[2] > s1[1] && s2[1] > s1[0]) std::cout << "Yes";
    else std::cout << "No";
}