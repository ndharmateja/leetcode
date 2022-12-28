import java.util.HashSet;

class Solution217 {
    public boolean containsDuplicate(int[] nums) {
        HashSet<Integer> numSet = new HashSet<>();
        for (int num : nums) {
            if (numSet.contains(num))
                return true;
            numSet.add(num);
        }
        return false;
    }
}