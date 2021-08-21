#include <unordered_map>
#include <vector>

using namespace std;

typedef struct LRU{
    int key;
    int val;
    LRU *prev;
    LRU *next;
    LRU() : key(0), val(0), prev(nullptr), next(nullptr) {}
    LRU(int _key, int _val) : key(_key), val(_val), prev(nullptr), next(nullptr) {}
} LRU;

class LRUCache {
public:
    LRUCache(int capacity) {
        currSize = 0;
        _capacity = capacity;
        head = new LRU();
        tail = new LRU();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (mp.count(key) == 0) {
            return -1;
        }
        auto ptr = mp[key];
        moveToHead(ptr);
        return mp[key]->val;
    }
    
    void put(int key, int value) {
        if (mp.count(key) == 1) {
            LRU *tmp = mp[key];
            tmp->val = value;
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            moveToHead(tmp);
        } else {
            if (currSize == _capacity) {
                deleteTail();
                LRU *tmp = new LRU(key, value);
                mp[key] = tmp;
                moveToHead(tmp);
            } else {
                currSize++;
                LRU *tmp = new LRU(key, value);
                mp[key] = tmp;
                moveToHead(tmp);
            }
        }
    }


    void moveToHead(LRU* curr) {
        curr->prev = head;
        curr->next = head->next;
        head->next->prev = curr;
        head->next = curr;
    }

    void deleteTail() {
        tail->prev->prev->next = tail;
        tail->prev = tail->prev->prev;
        mp.erase(tail->prev->key);
        tail->prev->prev = nullptr;
        tail->prev->next = nullptr;
        delete(tail->prev);
    }

private:
    int _capacity;
    int currSize;
    LRU *head;
    LRU *tail;
    unordered_map<int, LRU *> mp;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(void) {
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    lru.get(1);
    lru.put(3, 3);
    return 0;
}