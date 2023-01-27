import java.util.HashSet;
import java.util.Set;

class Solution {
    public int numJewelsInStones(String jewels, String stones) {
        Set<Character> jewelsSet = new HashSet<>();
        int count = 0;
        for (char c : jewels.toCharArray())
            jewelsSet.add(c);
        for (char c : stones.toCharArray())
            count += jewelsSet.contains(c) ? 1 : 0;
        return count;
    }
}