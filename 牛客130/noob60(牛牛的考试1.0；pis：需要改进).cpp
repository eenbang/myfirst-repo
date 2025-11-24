#include<iostream> 
using namespace std;
string Max(string A,string B,string C,string D){
    int max = A.size(); string ret = A;
    if(max<B.size()) {max=B.size();ret=B;}
    if(max<C.size()) {max=C.size();ret=C;}
    if(max<D.size()) {max=D.size();ret=D;}
    return ret;
}

string Min(string A,string B,string C,string D){
    int min = A.size(); string ret = A;
    if(min>B.size()) {min=B.size();ret=B;}
    if(min>C.size()) {min=C.size();ret=C;}
    if(min>D.size()) {min=D.size();ret=D;}
    return ret;
}

bool Exist_1Max(string A, string B, string C, string D){
    int n = Max(A,B,C,D).size(); int a=A.size(),b=B.size(),c=C.size(),d=D.size();
    if((n==a && n!=b && n!=c && n!=d)||(n==b && n!=a && n!=c && n!=d)||(n==c && n!=a && n!=b && n!=d)
        ||(n==d && n!=a && n!=c && n!=b)) return true;
    else return false;
}

bool Exist_1Min(string A, string B, string C, string D){
    int n = Min(A,B,C,D).size(); int a=A.size(),b=B.size(),c=C.size(),d=D.size();
    if((n==a && n!=b && n!=c && n!=d)||(n==b && n!=a && n!=c && n!=d)||(n==c && n!=a && n!=b && n!=d)
        ||(n==d && n!=a && n!=c && n!=b)) return true;
    else return false;
}

void Choice(string A, string B, string C, string D) {
    if (Exist_1Max(A, B, C, D) && !Exist_1Min(A, B, C, D)) {
        string ret = Max(A, B, C, D);
        if (ret == A) cout << 'A';
        else if (ret == B) cout << 'B';
        else if (ret == C) cout << 'C';
        else cout << 'D';
    } 
    else if (!Exist_1Max(A, B, C, D) && Exist_1Min(A, B, C, D)) {
        string ret = Min(A, B, C, D);
        if (ret == A) cout << 'A';
        else if (ret == B) cout << 'B';
        else if (ret == C) cout << 'C';
        else cout << 'D';
    } 
    else {
        cout << 'C';
    }
    cout << endl; // 每道题一行输出
}

int main(){
    int n;
    string A,B,C,D;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> A >> B >> C >> D;
        Choice(A,B,C,D);
    }
}