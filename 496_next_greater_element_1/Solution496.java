import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

@SuppressWarnings("unused")
class Solution496 {
    public int[] nextGreaterElement(int[] nums1, int[] nums2) {
        return solution2(nums1, nums2);
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

    // O(nums1.length + nums2.length) time and O(nums2.length) space solution
    // Method:
    // 1. For each value in nums2, find the next greatest
    // element and store it in a hash map (See 739 for more details).
    // 2. Iterate over nums1 and get the next greater element
    // from the hash map and add its values to the output array.
    private int[] solution2(int[] nums1, int[] nums2) {
        Map<Integer, Integer> nextGreaterMap = new HashMap<>();
        int[] output = new int[nums1.length];

        Stack<Integer> stack = new Stack<>();
        for (int num2 : nums2) {
            while (!stack.isEmpty() && stack.peek() < num2) {
                nextGreaterMap.put(stack.pop(), num2);
            }
            stack.add(num2);
        }

        for (int i = 0; i < nums1.length; i++) {
            int num1 = nums1[i];
            output[i] = nextGreaterMap.getOrDefault(num1, -1);
        }

        return output;
    }
}