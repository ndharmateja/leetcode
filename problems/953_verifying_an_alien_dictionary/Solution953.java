import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

class Solution953 {
    public boolean isAlienSorted(String[] words, String order) {
        Map<Character, Integer> map = new HashMap<>();
        for (int i = 0; i < order.length(); i++) {
            map.put(order.charAt(i), i);
        }

        // Comparator between two strings
        // based on the given letter ordering
        Comparator<String> comparator = new Comparator<String>() {
            @Override
            public int compare(String o1, String o2) {
                for (int i = 0; i < Math.min(o1.length(), o2.length()); i++) {
                    char c1 = o1.charAt(i);
                    char c2 = o2.charAt(i);
                    if (map.get(c1) > map.get(c2))
                        return 1;
                    if (map.get(c1) < map.get(c2))
                        return -1;
                }
                // If we reach here then the one word is a prefix
                // to the another
                return o1.length() - o2.length();
            }
        };

        for (int i = 0; i < words.length - 1; i++) {
            if (comparator.compare(words[i], words[i + 1]) > 0)
                return false;
        }
        return true;
    }
}