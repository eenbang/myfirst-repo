#include<iostream>
#include<stack>
#include<queue>
#include<string>
#include<cctype>

std::string Possible(std::string sIn,std::string sOut){
    std::queue <int> q;
    std::stack <int> num;
    
    int a = 0;
    sOut += " ";
    for(int i = 0; i < sOut.size() + 1; i++){
        if(isdigit(sOut[i])){
            a = a * 10 + sOut[i] - '0';
        }
        else if(sOut[i] == ' '){
            q.push(a);
            a = 0;
        }

    }//创建出栈顺序的队列
    sIn += " ";
    for(int i = 0; i < sIn.size() + 1; i++){
        if(isdigit(sIn[i])){
            a = a * 10 + sIn[i] - '0';
        }
        else if(sIn[i] == ' '){
            num.push(a);
            a = 0;
            while(!num.empty() && !q.empty() && num.top() == q.front()){
                num.pop();
                q.pop();
            }
        }
    }
    if(num.empty()) return "Yes";
    else return "No";
}

int main(){
    int q,n;
    std::string s1,s2;
    std::cin >>q;
    for(int i = 0; i < q; i++ ){
        std::cin >> n;
        std::cin.ignore();
        std::getline(std::cin,s1);
        std::getline(std::cin,s2);
        std::cout << Possible(s1,s2) << std::endl;
    }

}