#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string getSmallestString(int n, int k) {
        string s;
        int currValue = 0;
        for (int i = 0; i < n; i++) {
            int currMax = k - currValue - (n - i - 1);
            cout << currMax << endl;
            if (currMax > 26) {
                s += 'z';
                currValue += 26;
            } else {
                s += currMax + 'a' - 1;             
                currValue += currMax;
            }
        }
        reverse(s.begin(), s.end());
        return s;
    }
};