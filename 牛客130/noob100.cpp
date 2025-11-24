#include <iostream>
#include <set>

int main(){
    std::multiset <int> M;
    int n,opt,x;
    std::cin >> n;
    while(n--){
        std::cin >> opt;
        if(opt == 1){
            std::cin >> x;
            M.insert(x);
        }
        if(opt == 2){
            std::cin >> x;
            if(M.count(x)) M.erase(M.find(x));
        }
        if(opt == 3){
            std::cin >> x;
            std::cout << M.count(x) << std::endl;
        }
        if(opt == 4){
            std::cout << M.size() << std::endl;
        }
        if(opt == 5){
            std::cin >> x;
            auto it = M.lower_bound(x);
            if(it == M.begin()) std::cout << -1 << std::endl;
            else std::cout << *(--it) << std::endl;
        }
        if(opt == 6) {
            std::cin >> x;
            auto it = M.upper_bound(x);
            if(it == M.end()) std::cout << -1 << std::endl;
            else std::cout << *it << std::endl;
        }
    }
}