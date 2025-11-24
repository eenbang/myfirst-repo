//原理：数组模拟双向链表
#include <iostream>
#include <unordered_map>
#include <vector>

int main(){
    std::unordered_map <std::string,int> name_to_id;
    int n,m;
    std::cin >> n >> m;
    std::vector <std::string> id_to_name(n+1);
    std::vector <int> prev(n+2);
    std::vector <int> next(n+2);
    for(int i = 1; i <= n; i++){
        std::string name;
        std::cin >> name;
        name_to_id[name] = i;
        id_to_name[i] = name;
    } 
    //prev[n+1] = n;
    //next[0] = 1;
    for(int i = 0; i <= n + 1; i++){
        prev[i] = i-1;
        next[i] = i+1;
    }
    while(m--){
        std::string u_name,v_name;
        std::cin >> u_name >> v_name;
        int u_id = name_to_id[u_name];
        int v_id = name_to_id[v_name];

        int prev_u = prev[u_id];
        int next_u = next[u_id];
        next[prev_u] = next_u;
        prev[next_u] = prev_u;

        int prev_v = prev[v_id];
        next[u_id] = v_id;
        prev[v_id] = u_id;
        next[prev_v] = u_id;
        prev[u_id] = prev_v;
    }
    bool first = true;
    for(int curr_id = next[0]; curr_id != n+1; curr_id = next[curr_id]){
        if(!first){
            std::cout << " ";
        }
        std::cout << id_to_name[curr_id];
        first = false; 
    }
    std::cout << std::endl;

}



