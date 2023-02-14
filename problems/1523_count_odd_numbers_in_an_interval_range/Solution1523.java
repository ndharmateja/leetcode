class Solution1523 {
    public int countOdds(int low, int high) {
        if (low % 2 == 0)
            low++;
        if (high % 2 == 0)
            high--;
        if (low > high)
            return 0;
        return 1 + ((high - low) / 2);
    }
}