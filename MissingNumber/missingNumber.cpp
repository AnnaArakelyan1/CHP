#include <iostream>
#include <vector>
using namespace std;

class MissingNumber{
public:

int findMissingNumber(const vector<int>& nums) {
        int n = nums.size();
        int expectedSum = (n + 1) * (n + 2) / 2;
        int actualSum = 0;
        for (int num : nums) {
            actualSum += num;
        }
        return expectedSum - actualSum;
    }
};

int main() {
    
    vector<int> nums = {1, 2,3, 4, 5,6,7,9};
    MissingNumber mn;
    int missingNumber = mn.findMissingNumber(nums);
    cout << "The missing number : " << missingNumber << endl;
    return 0;
}
