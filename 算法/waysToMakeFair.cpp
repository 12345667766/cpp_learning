#include <vector>

using namespace std;

class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int size = nums.size();
        vector<int> preSumOdd(size, 0);
        vector<int> preSumEven(size, 0);

        preSumOdd[0] = 0;
        preSumEven[0] = nums[0];
        for (int i = 1; i < size; i++) {
            if (i % 2) {
                preSumOdd[i] = nums[i] + preSumOdd[i - 1];
                preSumEven[i] = preSumEven[i - 1];
            } else {
                preSumOdd[i] = preSumOdd[i - 1];
                preSumEven[i] = nums[i] + preSumEven[i - 1];
            }
        }
        int ans = 0;
        for (int i = 0; i < size; i++) {
            int oddBackSum;
            int evenBackSum;
            int oddPreSum;
            int evenPreSum;
            if (i == 0) {
                int evenSum = preSumOdd[size - 1];
                int oddSum = preSumEven[size - 1] - nums[0];
                if (evenSum == oddSum) {
                    ans++;
                }
            } else if (i == size - 1) {
                int evenSum = preSumEven[size - 2];
                int oddSum = preSumOdd[size - 2];
                if (evenSum == oddSum) {
                    ans++;
                }
            } else {
                oddBackSum = preSumEven[size - 1] - preSumEven[i];
                evenBackSum = preSumOdd[size - 1] - preSumOdd[i];
                oddPreSum = preSumOdd[i - 1];
                evenPreSum = preSumEven[i - 1];
                if ((oddBackSum + oddPreSum) == (evenBackSum + evenPreSum)) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
