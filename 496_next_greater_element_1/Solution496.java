class Solution496 {
    public int[] nextGreaterElement(int[] nums1, int[] nums2) {
        return solution1(nums1, nums2);
    }

    // O(nums1.length * nums2.length) time and O(1) space solution
    // Brute Force
    private int[] solution1(int[] nums1, int[] nums2) {
        int[] output = new int[nums1.length];
        for (int i = 0; i < output.length; i++) {
            output[i] = -1;
            int num1 = nums1[i];
            boolean isNum1Found = false;
            for (int num2 : nums2) {
                if (isNum1Found && num2 > num1) {
                    output[i] = num2;
                    break;
                }
                if (num2 == num1) {
                    isNum1Found = true;
                }
            }
        }

        return output;
    }
}