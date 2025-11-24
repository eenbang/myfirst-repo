#include <iostream>
#include <set>//用multiset因为队列用堆方法实现无法用迭代器进行遍历，要么使用两个优先队列


int main(){
    std::multiset<int> s;//set均为默认从小到大排列
    int n,op,x;
    std::cin >> n;
    while(n--){
        std::cin >> op;
        if(op == 1) {
            std::cin >> x;
            s.insert(x);
        }
        if(op == 3){
            std::cout << *(s.rbegin()) << std::endl;
        }
        if(op == 2){
            std::cout << *(s.begin()) << std::endl; 
        }
        if(op == 5){
            if(!s.empty()) s.erase(s.find(*(s.rbegin())));
        }
        if(op == 4){
            if(!s.empty()) s.erase(s.find(*(s.begin())));
        }
    }
}