import java.util.HashSet;
import java.util.Set;

class Solution {
    public int thirdMax(int[] nums) {
        Set<Integer> set = new HashSet<>();
        for (int num : nums) {
            set.add(num);
        }

        int maximum = Integer.MIN_VALUE;
        for (int num : set) {
            if (num > maximum) {
                maximum = num;
            }
        }
        set.remove(maximum);

        if (set.isEmpty())
            return maximum;
        int secondMaximum = Integer.MIN_VALUE;
        for (int num : set) {
            if (num > secondMaximum) {
                secondMaximum = num;
            }
        }
        set.remove(secondMaximum);

        if (set.isEmpty())
            return maximum;
        int thirdMaximum = Integer.MIN_VALUE;
        for (int num : set) {
            if (num > thirdMaximum) {
                thirdMaximum = num;
            }
        }

        return thirdMaximum;
    }
}