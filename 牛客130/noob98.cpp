#include <iostream>
#include <queue>
#include <vector>
int main(){
    std::vector <int> vec;
    std::queue <int> q,temp;
    int N,M,cin_valve;
    std::string flag;
    std::cin >> M >> N;
    while(N--){
        std::cin >> cin_valve;
        vec.push_back(cin_valve); 
    }
    q.push(vec[0]);
    int count = 1;
    for (int i = 1; i < vec.size(); i++){
        temp = q;
        flag = "miss";
        while(!temp.empty()){
            if(vec[i] == temp.front()) flag = "hit"; 
            temp.pop();
        }
        if(flag == "miss"){
            count++;
            if(q.size() == M){
                q.pop();
                q.push(vec[i]);
            }
            else{
                q.push(vec[i]);
            }
        }
    }
    std::cout << count;
    
}