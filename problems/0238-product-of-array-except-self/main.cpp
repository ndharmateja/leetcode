#include <iostream>
#include <vector>

class Solution
{
private:
    /**
     * Computes prefix products and postfix products
     * Theta(n) time and Theta(n) space
     * We are using one extra vector of size n other than the input and output
     */
    static std::vector<int> solution1(std::vector<int> &nums)
    {
        // Initialize vectors
        int n{static_cast<int>(nums.size())};
        std::vector<int> prefix_products(n);
        std::vector<int> postfix_products(n);

        // Compute the prefix and postfix products
        // Define:
        // prefix_product[i]  := product of values in the range [0, i-1]
        // postfix_product[i] := product of values in the range [i+1, n-1]
        // Eg: [4, 2, -5, 3]
        // prefix_products  = [1, 4, 8, -40]
        // postfix_products = [-30, -15, 3, 1]
        //
        // prefix_products[i] = prefix_products[i - 1] * nums[i - 1] as prefix_products[i - 1]
        // is the product of numbers in the range [0, i-2] and if we multiply that with nums[i - 1]
        // we get the product of numbers in the range [0, i-1] which is exactly prefix_products[i]
        prefix_products[0] = 1;
        for (int i = 1; i < n; ++i)
            prefix_products[i] = prefix_products[i - 1] * nums[i - 1];
        postfix_products[n - 1] = 1;
        for (int i = n - 2; i >= 0; --i)
            postfix_products[i] = postfix_products[i + 1] * nums[i + 1];

        // !Store the result in prefix_products: alias result to reference prefix_products
        // For any number, product except self = product of numbers before it * product of numbers after it
        // so result[i] = prefix_products[i] * postfix_products[i]
        std::vector<int> &result{prefix_products};
        for (int i = 0; i < n; i++)
            result[i] = prefix_products[i] * postfix_products[i];
        return result;
    }

    /**
     * Theta(n) time and Theta(1) space
     */
    static std::vector<int> solution2(std::vector<int> &nums)
    {
        // Initialize vector
        int n{static_cast<int>(nums.size())};
        std::vector<int> prefix_products(n);

        // Compute the prefix products
        // Define:
        // prefix_product[i]  := product of values in the range [0, i-1]
        // postfix_product[i] := product of values in the range [i+1, n-1]
        // Eg: [4, 2, -5, 3]
        // prefix_products = [1, 4, 8, -40]
        prefix_products[0] = 1;
        for (int i = 1; i < n; ++i)
            prefix_products[i] = prefix_products[i - 1] * nums[i - 1];

        // Without explicitly storing postfix products, we compute the result on the fly
        // and store the result in prefix_products vector itself
        // prefix_products =  [  1,   4,  8, -40]
        // postfix_products = [-30, -15,  3,   1] (we are not computing it)
        // result           = [-30, -60, 24, -40]
        //
        // Once we have the prefix products, we have a postfix_product variable that keeps track of
        // the postfix product for that element
        // Eg:
        // Before first iteration: postfix_product = 1, prefix_products =  [1, 4, 8, -40]
        // After first iteration: postfix_product = 3, prefix_products =  [1, 4, 8, -40]
        // After second iteration: postfix_product = -15, prefix_products =  [1, 4, 24, -40]
        // After third iteration: postfix_product = -30, prefix_products =  [1, -60, 24, -40]
        // After fourth iteration: postfix_product = -30, prefix_products =  [-30, -60, 24, -40]
        //
        // We have to ideally start postfix_product with 1 and i from n-1
        // but result[n-1] is just going to be prefix_product[n-1] as postfix_product[n-1] is 1
        // So we can start with postfix_product = nums[n-1] and start i from n-2
        int postfix_product = nums[n - 1];

        // !Alias result to point to prefix_products
        std::vector<int> &result{prefix_products};
        for (int i = n - 2; i >= 0; --i)
        {
            // At any iteration postfix_product stores the postfix_product[i]
            result[i] = prefix_products[i] * postfix_product;

            // update postfix_product with postfix_product[i-1] = nums[i] * postfix_product[i]
            // for the next iteration
            postfix_product = postfix_product * nums[i];
        }
        return result;
    }

public:
    std::vector<int> productExceptSelf(std::vector<int> &nums) { return solution2(nums); }
};