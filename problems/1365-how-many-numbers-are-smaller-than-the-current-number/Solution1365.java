class Solution1365 {
    public int[] smallerNumbersThanCurrent(int[] nums) {
        int[] counts = new int[nums.length];
        for (int i = 0; i < nums.length; i++) {
            int numILessThanJ = 0;
            for (int j = 0; j < nums.length; j++) {
                if (i == j)
                    continue;
                if (nums[i] > nums[j])
                    numILessThanJ++;
            }
            counts[i] = numILessThanJ;
        }
        return counts;
    }
}