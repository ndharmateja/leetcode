import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

class Solution1160 {

    private Map<Character, Integer> getCharCounts(String string) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char c : string.toCharArray()) {
            counts.put(c, counts.getOrDefault(c, 0) + 1);
        }
        return counts;
    }

    private boolean isValid(String word, Map<Character, Integer> charsCounts) {
        for (Entry<Character, Integer> entry : getCharCounts(word).entrySet()) {
            char c = entry.getKey();
            int count = entry.getValue();
            if (!charsCounts.containsKey(c) || count > charsCounts.get(c))
                return false;
        }
        return true;
    }

    public int countCharacters(String[] words, String chars) {
        int total = 0;
        Map<Character, Integer> charsCounts = getCharCounts(chars);
        for (String word : words) {
            if (isValid(word, charsCounts))
                total += word.length();
        }
        return total;
    }
}