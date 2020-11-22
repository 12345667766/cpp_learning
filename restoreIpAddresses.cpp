#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> segVec;
    vector<string> ans;

    void dfs(string& s, int segId, int segStart) {
        if (segId == 4) {
            if (segStart == s.size()) {
                string temp;
                for (int i = 0; i < 4; i++) {
                    temp += (to_string(segVec[i]));
                    if (i != 3) {
                        temp += ".";
                    }
                }
                ans.push_back(temp);
            }
            return;
        }
        if (segStart == s.size()) {
            return;
        }
        if (s[segStart] == '0') {
            segVec[segId] = 0;
            dfs(s, segId + 1, segStart + 1);
        }
        int addr = 0;
        for (int segEnd = segStart; segEnd < s.size(); ++segEnd) {
            addr = addr * 10 + (s[segEnd] - '0');
            if (addr > 0 && addr <= 0xFF) {
                segVec[segId] = addr;
                dfs(s, segId + 1, segEnd + 1);
            } else {
                break;
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        segVec.resize(4);
        dfs(s, 0, 0);
        return ans;
    }
};