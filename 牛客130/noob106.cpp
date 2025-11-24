#include <iostream>
#include <queue>

int main(){
    std::priority_queue <int,std::vector<int>, std::greater<int> > pq;
    int n,op,x;
    std::cin >> n;
    while(n--){
        std::cin >> op;
        if(op == 1){
            std::cin >> x;
            pq.push(x);
        }
        if(op == 2){
            std::cout << pq.top() <<std::endl;
        }
        if(op == 3){
            pq.pop();
        }
    }
}