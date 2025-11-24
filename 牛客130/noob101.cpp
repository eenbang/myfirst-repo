#include <iostream>
#include <set>
#include <cmath>
int DistanceMin(int x, std::set <int> s){
    auto it = s.lower_bound(x);
    int ans;
    if(it == s.begin()) ans = *it;
    else if(it == s.end()) ans = *std::prev(it); 
    else{
        int right = *it;
        int left = *std::prev(it);
        if(abs(right - x) < abs(left - x)) ans = right;
        else ans = left;
    }
    return ans;
}

int main(){
    int Q,op,x;
    std::set <int> s;
    std::cin >> Q;
    while(Q--){
        std::cin >> op >> x;
        if(op == 1){
            if(s.count(x)) std::cout << "Already Exist" << std::endl;
            else s.insert(x);
        }
        if(op == 2){
            if(!s.empty()){
                std::cout << DistanceMin(x,s) << std::endl;
                s.erase(DistanceMin(x,s));
            }
            else std::cout << "Empty" << std::endl;
        }
    }
}