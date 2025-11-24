#include<iostream>
#include<queue>

int main(){
    std::priority_queue <int,std::vector<int>, std::greater<int> > pq;
    int n,m,cin_valve; int max = 0;
    std::cin >> n >> m;
    while(n--){
        std::cin >> cin_valve;
        pq.push(cin_valve);
        if(cin_valve > max) max = cin_valve;
    }
    while(m--){
        int temp,addScore;
        std::cin >> addScore;
        temp = pq.top() + addScore;
        pq.pop();
        pq.push(temp);
        if(temp > max) max = temp;
        std::cout << max << std::endl;

    }
}
