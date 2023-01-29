import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

class Solution2103 {
    // O(n) time and O(n) space solution
    public int countPoints(String rings) {
        // {'0': {R, G}, '1': {R, G, B}}
        Map<Character, Set<Character>> map = new HashMap<>();
        int n = rings.length() / 2;

        for (int i = 0; i < n; i++) {
            char color = rings.charAt(2 * i);
            char rod = rings.charAt(2 * i + 1);

            if (!map.containsKey(rod))
                map.put(rod, new HashSet<>());
            map.get(rod).add(color);
        }

        int count = 0;
        for (Set<Character> set : map.values()) {
            if (set.size() == 3)
                count++;
        }

        return count;
    }
}