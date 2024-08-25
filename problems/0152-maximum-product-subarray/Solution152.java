public class Solution152 {
    /**
     * O(n^3) time brute force solution
     * 
     * @param nums
     * @return
     */
    public int solution1(int[] nums) {
        int maxProduct = Integer.MIN_VALUE;

        for (int num : nums) {
            maxProduct = Integer.max(num, maxProduct);
        }

        // Go over all possible subarrays with length atleast 2
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                int product = 1;
                for (int k = i; k <= j; k++) {
                    product *= nums[k];
                }

                maxProduct = Integer.max(maxProduct, product);
            }
        }

        return maxProduct;
    }

    public int maxProduct(int[] nums) {
        return solution1(nums);
    }
}