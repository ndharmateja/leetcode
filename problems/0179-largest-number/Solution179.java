import java.util.Arrays;
import java.util.Comparator;

public class Solution179 {
    // O(n log n) time and O(n) space solution
    public String largestNumber(int[] nums) {
        // Create strings array corresponding to nums
        String[] stringNums = new String[nums.length];
        for (int i = 0; i < stringNums.length; i++) {
            stringNums[i] = Integer.toString(nums[i]);
        }

        // Sort the strings array
        // In our comparator we see which combination of strings
        // forms the higher number and take that order
        // between two strings
        Arrays.sort(stringNums, new Comparator<String>() {
            @Override
            public int compare(String o1, String o2) {
                if (Long.parseLong(o1 + o2) < Long.parseLong(o2 + o1))
                    return 1;
                return -1;
            }
        });

        // Combine all the strings after sorting
        StringBuilder output = new StringBuilder();
        for (String stringNum : stringNums) {
            output.append(stringNum);
        }

        // Remove all the trailing zeroes as long as there is atleast
        // one char in the string
        output = output.reverse();
        while (output.length() > 1 && output.charAt(output.length() - 1) == '0') {
            output.setLength(output.length() - 1);
        }
        output = output.reverse();

        return output.toString();
    }
}
