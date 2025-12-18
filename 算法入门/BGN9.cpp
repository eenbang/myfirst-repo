#include <iostream>
#include <vector>
int main(){
    int t;
    int n;
    int member,average; int sum = 0;
    std::vector <int> vec;
    std::cin >> t;
    while(t--){
        std::cin >> n;
        vec.clear();
        sum = 0;
        for(int i = 0; i < n; i++){
            std::cin >> member;
            sum += member;
            vec.push_back(member);
        }
        if(vec.size() == 1) {
            std::cout << "YES" << std::endl;
            continue;
        } 
        if(sum % n != 0){
            std::cout << "NO" << std::endl;
            continue;
        }
        average = sum / n;
        for(int i = 1; i < n - 1; i++){
            vec[i + 1] = vec[i - 1] + vec[i + 1] - average;
            vec[i - 1] = average;  
        }
        if(vec[n - 1] == vec[n - 2]) std::cout << "YES" << std::endl;
        else std::cout << "NO" << std::endl;
    }
}