#include <iostream>
#include <set>

int main(){
    long long N,C;
    std::cin >> N >> C;
    std::multiset <long long> s;
    while(N--){
        long long in;
        std::cin >> in;
        s.insert(in);
    }
    int count = 0;
    for(auto it = s.begin(); it != s.end(); it++){
        count += s.count(*it + C);
    }
    std::cout << count << std::endl;
}