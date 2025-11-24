#include<iostream>
#include<queue>
using namespace std;

struct node{
    int chinese, math, english, sum;
    node(int c,int m, int e)
    :chinese(c), math(m), english(e),sum(c+m+e){}
};

bool operator<(node a, node b){
    // TODO: 实现比较逻辑，按照总分、语文、数学、英语的优先级排序
    if(a.sum != b.sum) return a.sum < b.sum;
    else if(a.chinese != b.chinese) return a.chinese < b.chinese;
    else if(a.math != b.math) return a.math < b.math;
    else if(a.english != b.english) return a.english < b.english;
    else return true;
}

priority_queue <node> s;
void insertValue(int chinese, int math, int english){
    // TODO: 实现插入操作
    node insert_student(chinese,math,english);
    s.push(insert_student);
}

void deleteValue(){
    // TODO: 实现删除操作
    s.pop();
}

node getTop(){
    // TODO: 返回成绩最好的学生
    
    return s.top();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q,op;
    int x, y, z;
    cin>>q;
    while(q--){
        cin>>op;
        if(op==1){
            cin>>x>>y>>z;
            insertValue(x, y, z);
        }
        if(op==2){
            node tmp = getTop();
            cout<<tmp.chinese<<" "<<tmp.math<<" "<<tmp.english<<endl;
        }
        if(op==3){
           deleteValue();
        }
    }
    return 0;
}