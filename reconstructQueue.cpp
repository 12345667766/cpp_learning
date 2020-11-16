#include <vector>
#include <algorithm>

using namespace std;

// 重建队列  按照身高降序排列，身高相同，则按照k值升序排列
// 然后新建数组，对排序后的数组，进行插入，如果数组长度小于要插入的元素的元素的K值，则直接push_back到后面
// 否则，插入到对应位置。 因为之前的元素都比较高，因此可以保证插入到正确的位置

class Solution {
public:
    static bool cmp(const vector<int>& p1, const vector<int>& p2) {
        if (p1[0] > p2[0]) {
            return true;
        }
        if (p1[0] == p2[0]) {
            return p1[1] < p2[1];
        }
        return false;
    }

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), cmp);
        vector<vector<int>> ans;
        for (auto v : people) {
            if (v[1] > ans.size()) {
                ans.push_back(v);
            } else {
                ans.insert(ans.begin() + v[1], v);
            }
        }
        return ans;
    }
};