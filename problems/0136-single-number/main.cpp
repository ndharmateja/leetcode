#include <vector>

class Solution
{
public:
    int singleNumber(std::vector<int> &nums)
    {
        // XOR properties
        // x ^ x = 0
        // x ^ 0 = x
        // x ^ y = y ^ x
        // x ^ (y ^ z) = (x ^ y) ^ z
        //
        // so if we have [2, 1, 2, 4, 1]
        // 2 ^ 1 ^ 2 ^ 4 ^ 1 = (2 ^ 2) ^ (1 ^ 1) ^ 4 = 0 ^ 0 ^ 4 = 4
        // We have to start with 0 as it is the xor identity as x ^ 0 = x
        int result = 0;
        for (const auto &num : nums)
            result ^= num;
        return result;
    }
};