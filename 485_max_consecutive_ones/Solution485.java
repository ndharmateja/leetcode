class Solution485 {
    public int findMaxConsecutiveOnes(int[] nums) {
        int currStreakLength = 0;
        int maxStreakLength = 0;
        boolean inOnesStreak = false;
        for (int num : nums) {
            if (inOnesStreak && num == 0) {
                maxStreakLength = Math.max(currStreakLength, maxStreakLength);
                currStreakLength = 0;
                inOnesStreak = false;
            } else if (inOnesStreak && num == 1) {
                currStreakLength++;
            } else if (!inOnesStreak && num == 1) {
                inOnesStreak = true;
                currStreakLength = 1;
            }
        }
        if (inOnesStreak) {
            maxStreakLength = Math.max(currStreakLength, maxStreakLength);
        }
        return maxStreakLength;
    }
}