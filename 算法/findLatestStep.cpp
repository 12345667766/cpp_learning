#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        string s;
        s.append(arr.size() + 2, '1');
        s[0] = '0';
        s[arr.size() + 1] = '0';
        int step = arr.size();
        if (m == arr.size()) {
            return m;
        }
        for (int i = arr.size() -1; i >= 0; i--) {
            step--;
            s[arr[i]] = '0';
            int left = arr[i] - 1;
            int right = arr[i] + 1;
            int lenLeft = 0;
            while(s[left] != '0') {
                lenLeft++;
                left--;
            }
            int lenRight = 0;
            while(s[right] != '0') {
                lenRight++;
                right++;
            }
            if (lenLeft == m || lenRight == m) {
                break;
            }
        }
        return step == 0 ? -1 : step;
    }
};

int main(void) {
    Solution solution;
    vector<int> arr = {3, 1, 5, 4, 2};
    int m = 2;
    int res = solution.findLatestStep(arr, m);
    cout << res << endl;
    return 0;
}