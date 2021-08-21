#include <map>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int redPtr = 0;
        int bluePtr = nums.size() - 1;
        while(redPtr < nums.size() && nums[redPtr++] == 0) { }

        while(bluePtr > redPtr && nums[bluePtr--] == 2) {}
        for (int i = redPtr; i <= bluePtr;) {
            if (redPtr > bluePtr) {
                break;
            }
            if (nums[i] == 0) {
                if (i == redPtr) {
                    i++;
                }
                else {
                    swap(nums[i], nums[redPtr++]);  
                }                                            
            }
            else if (nums[i] == 2) {
                swap(nums[i], nums[bluePtr--]);
            } else {
                i++;
            }
        }
        return;
    }
};

