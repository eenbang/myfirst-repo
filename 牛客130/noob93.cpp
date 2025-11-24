#include <iostream>
#include <queue>

int main(){
    std::queue <int> q;
    int n,t,x;
    std::cin >> n;
    while(n--){
        std::cin >> t;
        if(t == 1){
            std::cin >> x;
            q.push(x);
        }
        if(t == 2){
            if(!q.empty()){
                q.pop();
            }
            else std::cout << "ERR_CANNOT_POT" << std::endl;
        }
        if(t == 3){
            if(!q.empty()){
                std::cout << q.front() << std::endl;
            } 
            else std::cout << "ERR_CANNOT_QUERY" << std::endl;

        }
        if(t == 4){
            std::cout << q.size() << std::endl;
        }
    }
    

}