class Solution746 {
    public int minCostClimbingStairs(int[] cost) {
        int n = cost.length;
        int[] minCost = new int[n];
        minCost[0] = 0;
        minCost[1] = 0;
        for (int i = 2; i < minCost.length; i++) {
            minCost[i] = Math.min(minCost[i - 1] + cost[i - 1], minCost[i - 2] + cost[i - 2]);
        }
        return Math.min(minCost[n - 1] + cost[n - 1], minCost[n - 2] + cost[n - 2]);
    }
}