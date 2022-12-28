import java.util.Arrays;

class Solution1295 {
    public int findNumbers(int[] nums) {
        return Arrays.stream(nums).filter(num -> (((int) (Math.log10(num)) + 1) % 2) == 0).map(e -> 1).sum();
    }

}