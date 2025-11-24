#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode* curA = headA;
    ListNode* curB = headB;
    while(curA != nullptr){
        while(curB != nullptr){
            if(curA == curB) return curA;
            else{
                curB = curB -> next;
            }
        }
        curA = curA -> next;
        curB = headB;
    }
    return nullptr;
}

//你不需要修改主函数内的代码！
int main() {
    // 读入数据
    int lenA, lenB, commonLen;
    cin >> lenA >> lenB >> commonLen;
    
    // 构建链表
    vector<ListNode*> nodesA(lenA - commonLen);
    vector<ListNode*> nodesB(lenB - commonLen);
    vector<ListNode*> nodesCommon(commonLen);
    
    // 读入并创建链表A的独立部分
    for (int i = 0; i < lenA - commonLen; i++) {
        int val;
        cin >> val;
        nodesA[i] = new ListNode(val);
        if (i > 0) nodesA[i-1]->next = nodesA[i];
    }
    
    // 读入并创建链表B的独立部分
    for (int i = 0; i < lenB - commonLen; i++) {
        int val;
        cin >> val;
        nodesB[i] = new ListNode(val);
        if (i > 0) nodesB[i-1]->next = nodesB[i];
    }
    
    // 读入并创建公共部分
    for (int i = 0; i < commonLen; i++) {
        int val;
        cin >> val;
        nodesCommon[i] = new ListNode(val);
        if (i > 0) nodesCommon[i-1]->next = nodesCommon[i];
    }
    
    // 连接链表
    ListNode* headA = nullptr;
    ListNode* headB = nullptr;
    
    if (lenA - commonLen > 0) {
        headA = nodesA[0];
        if (commonLen > 0) nodesA.back()->next = nodesCommon[0];
    } else if (commonLen > 0) {
        headA = nodesCommon[0];
    }
    
    if (lenB - commonLen > 0) {
        headB = nodesB[0];
        if (commonLen > 0) nodesB.back()->next = nodesCommon[0];
    } else if (commonLen > 0) {
        headB = nodesCommon[0];
    }
    
    // 调用函数获取结果
    ListNode* result = getIntersectionNode(headA, headB);
    
    // 输出结果
    if (result == nullptr) {
        cout << "null" << endl;
    } else {
        cout << result->val << endl;
    }
    
    // 清理内存
    for (auto node : nodesA) delete node;
    for (auto node : nodesB) delete node;
    for (auto node : nodesCommon) delete node;
    
    return 0;
} 