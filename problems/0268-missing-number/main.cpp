#include <vector>

class Solution
{
private:
    /**
     * Theta(n) time and Theta(1) space
     */
    static int solution1(const std::vector<int> &nums)
    {
        // The sum of numbers of 0 to n = n(n+1)/2
        // and the missing number is n(n+1)/2 - sum(nums)
        // Ideally we should be using a long long because the sum could overflow
        // but we don't need a long long for the leetcode constraints
        int n{static_cast<int>(nums.size())};
        int sum{(n * (n + 1)) / 2};
        for (int num : nums)
            sum -= num;
        return sum;
    }

    /**
     * Theta(n) time and Theta(1) space
     */
    static int solution2(const std::vector<int> &nums)
    {
        // x ^ x = 0
        // x ^ 0 = x
        // The XOR of 0 ^ 0 ^ 1 ^ 1 ^ 2 ^ 2 ^ ... ^ n-1 ^ n-1 ^ n ^ n = 0
        // irrespective of which order we do the XORs
        // So if we just skip one number (say i) in the XORs, the result will be i
        // 0 ^ 0 ^ 1 ^ 1 ^ 2 ^ 2 ^ ... ^ i-1 ^ i-1 ^ i ^ i+1 ^ i+1 ^ ... ^ n-1 ^ n-1 ^ n ^ n
        // = (0 ^ 0 ^ 1 ^ 1 ^ 2 ^ 2 ^ ... ^ i-1 ^ i-1 ^ i+1 ^ i+1 ^ ... ^ n-1 ^ n-1 ^ n ^ n) ^ i
        // = 0 ^ i
        // = i
        int n{static_cast<int>(nums.size())};
        int result{0};
        for (int i = 0; i < n; i++)
            result = result ^ i ^ nums[i];
        result = result ^ n;
        return result;
    }

public:
    int missingNumber(const std::vector<int> &nums) { return solution1(nums); }
};