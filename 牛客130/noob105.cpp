#include <iostream>
#include <set>
#include <vector>
int main(){
    std::set<int> s;
    std::vector<int> vec;
    int T,n,cin_valve;
    std::cin >> T;
    while(T--){
        std::cin >> n;
        while(n--){
            std::cin >> cin_valve;
            if(!s.count(cin_valve)) vec.push_back(cin_valve);
            s.insert(cin_valve);
        }
        for(int i = 0; i < vec.size(); i++){
            std::cout << vec[i] << '\0';
        }
        std::cout << std::endl;
        s.clear();
        vec.clear();
    }
}