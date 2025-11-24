#include <iostream>
#include <stack>
#include <string>

int main() {
    std::stack<char> s;
    std::string str;
    std::cin >> str;
    
    bool note = true;
    
    for (char c : str) {
        // 遇到左括号，压栈
        if (c == '(' || c == '[') {
            s.push(c);
        }
        // 遇到右括号，弹栈并检查是否匹配
        else if (c == ')' || c == ']') {
            if (s.empty()) {
                note = false; // 如果栈空，则说明没有匹配的左括号
                break;
            }
            char top = s.top();
            s.pop();
            // 判断括号是否匹配
            if ((c == ')' && top != '(') || (c == ']' && top != '[')) {
                note = false;
                break;
            }
        }
    }
    
    // 如果栈非空，说明有多余的左括号
    if (!s.empty()) {
        note = false;
    }
    
    if (note) std::cout << "true";
    else std::cout << "false";
    
    return 0;
}
