#include <iostream>
#include <stack>
#include <string>
class Solution {
  public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 返回表达式的值
     * @param s string字符串 待计算的表达式
     * @return int整型
     */
    int solve(std::string s) {
        std::stack <char> zhan;
        std::stack <long long> l;
        std::string ss; // 作为后缀表达式
        for (int i = 0; i < s.size(); i++) {
            //扫描到数字，直接进入后缀表达式
            if(isdigit(s[i]) && i < s.size()){
                while(isdigit(s[i])){
                    ss += s[i];
                    i++;
                }
                ss+= '#';
                i--;
            }
            //扫描到+ - ,若栈top为*+-，则出栈,(与空入栈
            else if (s[i] == '+'){
                if (zhan.empty() || zhan.top() == '(') zhan.push(s[i]);
                else if (zhan.top() == '*' || zhan.top() == '+' || zhan.top() == '-') {
                    ss += zhan.top();
                    zhan.pop();
                    i--;
                }
            } else if (s[i] == '-'){
                if (zhan.empty() || zhan.top() == '(') zhan.push(s[i]);
                else if (zhan.top() == '*' || zhan.top() == '+' || zhan.top() == '-') {
                    ss += zhan.top();
                    zhan.pop();
                    i--;
                }
            }
            //扫描到*，若栈顶为*，则出栈，i--；若栈顶为+-，直接入栈
            else if (s[i] == '*') {
                if (zhan.empty() || zhan.top() == '+' || zhan.top() == '-' ||
                        zhan.top() == '(') zhan.push(s[i]);
                else if (zhan.top() == '*') {
                    ss += zhan.top();
                    zhan.pop();
                    i--;
                }

            }
            //扫描到‘（’，直接入栈
            else if (s[i] == '(') {
                zhan.push(s[i]);
            }
            //扫描到‘）’，从上往下一次出栈放入后缀表达式，并把‘（’扔掉
            else if (s[i] == ')') {
                while (zhan.top() != '(') {
                    ss += zhan.top();
                    zhan.pop();
                }
                zhan.pop();
            }
            
            /*最后处理后缀表达式求值，借助栈（转化操作已经让他为空，故可重复使用!!个屁，char才1字节！！）*/
        }
        while(!zhan.empty()){
                ss += zhan.top();
                zhan.pop();
            }

        long long a = 0;
        long long b = 0;
        for (int i = 0; i < ss.size(); i++) {
            if (ss[i] >= '0' && ss[i] <= '9') {
                a = a * 10 + ss[i] - '0';
            }
            switch (ss[i]) {
                case '#' :
                    l.push(a);
                    a = 0;
                    break;
                case '+' :
                    b += l.top();
                    l.pop();
                    b += l.top();
                    l.pop();
                    l.push(b);
                    b = 0;
                    break;
                case '-' :
                    b -= l.top();
                    l.pop();
                    b += l.top();
                    l.pop();
                    l.push(b);
                    b = 0;
                    break;
                case '*' :
                    b += l.top();
                    l.pop();
                    b *= l.top();
                    l.pop();
                    l.push(b);
                    b = 0;
                    break;
            }


        }
        return l.top();



    }
};/*逆波尔表达式求值，中缀表达式 ——> 后缀表达式
    1. 扫描到数字，直接放入后缀表达式；
    2. 扫描到'('，直接入栈，扫描到')'，从栈顶开始弹出元素放入后缀表达式直到'('被弹出；
    3. 扫描到 '+' '-' '*'，空的话直接入栈；
    非空的话，若扫描到的元素小于等于栈顶元素的优先级，则栈顶元素出栈放入到后缀表达式，继续判断  
             若扫描到的元素大于栈顶元素的优先级，则扫描元素直接入栈
*/

int main(){
    std::string s;
    std::cin >> s;
    Solution sol;  
    std::cout << sol.solve(s) << std::endl;
}