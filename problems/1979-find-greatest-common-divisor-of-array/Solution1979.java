class Solution1979 {
    // Euclid's algorithm for GCD
    private int gcd(int a, int b) {
        if (b == 0)
            return a;
        if (a < b)
            return gcd(b, a);
        return gcd(b, a % b);
    }

    public int findGCD(int[] nums) {
        // Find the min and max
        // As 1 <= nums[i] <= 1000
        int min = 1001;
        int max = 0;
        for (int num : nums) {
            min = Math.min(min, num);
            max = Math.max(max, num);
        }
        return gcd(min, max);
    }
}