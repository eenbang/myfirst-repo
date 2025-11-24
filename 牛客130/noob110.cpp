#include <iostream>
#include <set>

int main(){
    std::multiset <int> pq;
    int n,m,cin_valve;
    std::cin >> n >> m;
    while(n--){
        std::cin >> cin_valve;
        pq.insert(cin_valve);
    } 
    while(m--){
        int addCore;
        std::cin >> addCore;
        auto it = pq.begin();
        int temp = *it + addCore;
        pq.erase(pq.find(*it));
        pq.insert(temp);
        std::cout << *pq.rbegin() << std::endl; 
    }

}