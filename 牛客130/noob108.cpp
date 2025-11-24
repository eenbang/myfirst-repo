#include<iostream>
#include<queue>
using namespace std;
priority_queue<string, vector<string>, greater<string>> s;//倒序排列
void insertValue(string x){
    // TODO: 实现插入操作
    s.push(x);  
}

void deleteValue(){
    // TODO: 实现删除操作
    s.pop();
}

string getTop(){
    // TODO: 返回字典序最小的字符串
    return s.top();
}

int main(){
    int q,op;
    string x;
    cin>>q;
    while(q--){
        cin>>op;
        if(op==1){
            cin>>x;
            insertValue(x);
        }
        if(op==2){
            cout<<getTop()<<endl;
        }
        if(op==3){
           deleteValue();
        }
    }
    return 0;
}