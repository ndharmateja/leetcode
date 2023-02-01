class Solution1979 {
    private int gcd(int a, int b) {
        if (b == 0)
            return a;
        if (a < b)
            return gcd(b, a);
        return gcd(b, a % b);
    }

    public int findGCD(int[] nums) {
        int min = Integer.MAX_VALUE;
        int max = Integer.MIN_VALUE;
        for (int num : nums) {
            min = Math.min(min, num);
            max = Math.max(max, num);
        }
        return gcd(min, max);
    }
}