import java.util.HashMap;
import java.util.Map;

class Solution383 {
    private Map<Character, Integer> getCharCounts(String string) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char c : string.toCharArray()) {
            counts.put(c, counts.getOrDefault(c, 0) + 1);
        }
        return counts;
    }

    // O(n) time and O(n) space solution
    public boolean canConstruct(String ransomNote, String magazine) {
        if (ransomNote.length() > magazine.length())
            return false;

        Map<Character, Integer> magazineCharCounts = getCharCounts(magazine);
        Map<Character, Integer> ransomCharCounts = getCharCounts(ransomNote);

        for (char c : ransomCharCounts.keySet()) {
            if (!magazineCharCounts.containsKey(c) || magazineCharCounts.get(c) < ransomCharCounts.get(c)) {
                return false;
            }
        }

        return true;
    }
}