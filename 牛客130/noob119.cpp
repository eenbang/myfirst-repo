#include <iostream>

struct ListNode{
    std::string name;
    struct ListNode* next;
    ListNode(const std::string& x):name(x),next(nullptr){}
};

int main() {
    int n,m; 
    std::cin >> n >> m;
    std::string name;
    auto head = new ListNode("*");//创建一个虚头
    ListNode* cur = head;
    for(int i = 0; i  < n; i++){
        std::cin >> name;
        cur->next = new ListNode(name);
        cur = cur->next;
    }
    while(m--){
        std::string a,b;
        std::cin >> a >> b;
        ListNode* pre1 = nullptr;
        ListNode* pre2 = nullptr;
        //找到a，b前驱
        cur = head;
        while(cur->next){
            if(cur->next->name == b) pre2 = cur;
            if(cur->next->name == a) {
                if(pre2 == nullptr) break;
                else pre1 = cur;
            }
            cur = cur->next;
        }
        //处理
        if(pre1 == pre2) continue;
        
        ListNode* node1 = pre1->next;
        pre1->next = node1->next;
        node1->next = pre2->next;
        pre2->next = node1;
        
    }
    cur = head->next;
    for(int i = 0; i < n; i++){
        std::cout << cur->name << " ";
        cur = cur->next;    
    }
    
}