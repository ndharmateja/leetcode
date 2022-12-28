class Solution1672 {
    public int maximumWealth(int[][] accounts) {
        int max = Integer.MIN_VALUE;
        for (int[] account : accounts) {
            int sum = 0;
            for (int value : account)
                sum += value;
            if (sum > max)
                max = sum;
        }
        return max;
    }
}