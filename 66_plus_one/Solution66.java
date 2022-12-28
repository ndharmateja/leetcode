class Solution66 {
    private int[] insertAtBeginning(int[] nums, int value) {
        int[] out = new int[nums.length + 1];
        out[0] = value;
        for (int i = 0; i < nums.length; i++) {
            out[i + 1] = nums[i];
        }
        return out;
    }

    public int[] plusOne(int[] digits) {
        digits[digits.length - 1] += 1;

        for (int i = digits.length - 1; i > 0; i--) {
            if (digits[i] < 10)
                return digits;
            digits[i] = digits[i] % 10;
            digits[i - 1] += 1;
        }

        if (digits[0] < 10)
            return digits;

        int[] out = insertAtBeginning(digits, 1);
        out[1] = out[1] % 10;
        return out;
    }
}