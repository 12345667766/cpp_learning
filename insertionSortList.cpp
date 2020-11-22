#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

// 双向链表
typedef struct ListNode{
    int val;
    ListNode *prev;
    ListNode *next;
    ListNode(int _val) : val(_val), prev(nullptr), next(nullptr) {}
    ListNode() : val(0), prev(nullptr), next(nullptr) {}
} ListNode;

ListNode *_head;
ListNode *_tail;

unordered_map<int, ListNode *> mp;

ListNode* insertList(int val) {
    ListNode *tmp = new ListNode(val);
    mp[val] = tmp;
    _head->next->prev = tmp;
    tmp->next = _head->next;
    _head->next = tmp;
    tmp->prev = _head;
    return tmp;
}

void createList() {
    _head = new ListNode();
    _tail = new ListNode();
    _head->next = _tail;
    _tail->prev = _head;  
    return; 
}

vector<int> traversal(ListNode* head) {
    vector<int> ans;
    ListNode *curr = head;
    while(curr != _tail) {
        ans.push_back(curr->val);
        curr = curr->next;
    }
    return ans;
}

void deleteList(ListNode* head) {
    while(head != _tail) {
        ListNode *tmp = head;
        tmp->prev = nullptr;
        tmp->next = nullptr;
        free(tmp);
        head = head->next;
    }
    _head->next = nullptr;
    _head->prev = nullptr;
    _tail->prev = nullptr;
    _tail->next = nullptr;
    free(_head);
    free(_tail);
    return;
}

void moveToHead(ListNode* curr) {
    _head->next->prev = curr;
    curr->next = _head->next;
    _head->next = curr;
    curr->prev = _head;
}

ListNode* deleteNode(int val) {
    ListNode *addr = mp[val];
    addr->prev->next = addr->next;
    addr->next->prev = addr->prev;
    addr->next = nullptr;
    addr->prev = nullptr;
    return addr;
}


int main(void) {
    createList();
    for (int i = 0; i < 10; i++) {
        insertList(i);
    }
    vector<int> ans = traversal(_head->next);
    for (auto v : ans) {
        cout << v << " ";
    }
    ListNode *tmp = deleteNode(5);
    moveToHead(tmp);
    ans.clear();
    ans = traversal(_head->next);
    for (auto v : ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}