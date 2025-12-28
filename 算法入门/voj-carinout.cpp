#include <iostream>
#include <vector>
#include <set>
using namespace std;
//遍历出库清单 Carout。

//如果这辆车还不在车库里，就从 Carin 里面一辆辆拉进来，同时 current_size++。

//如果在这个过程中 current_size 超过了 k，说明发生了抢占，num++。

//找到这辆车后，让它出库，current_size--。

int MinNum(const int n, int k, const vector<int>& Carin, const vector<int>& Carout){
    int num = 0;
    vector <int> pos(n+1);
    for(int i = 0; i < n; i++){
        pos[Carin[i]] = i;
    }
    multiset <int> still_in;
    for(int i = 0; i < n; i++){
        still_in.insert(i);
    }
    for(int i = 0; i  < n; i++){
        int car = Carout[i];
        int p = pos[car];

        if((int)still_in.size() >= k){
            auto it = still_in.begin();
            advance(it,k-1);
            if(p > *it) num++;
        }
        still_in.erase(still_in.find(p));
    }
    return num;
}


int main(){
    // 关流同步，加速大量数据的输入输出
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    vector<int> Carin;
    vector<int> Carout;
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        Carin.push_back(t);
    }
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        Carout.push_back(t);
    }
    cout << MinNum(n,k,Carin,Carout);
}