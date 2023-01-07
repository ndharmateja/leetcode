import java.util.HashMap;
import java.util.Map;

class Solution1189 {
    private Map<Character, Integer> getCharCounts(String string) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char c : string.toCharArray()) {
            counts.put(c, counts.getOrDefault(c, 0) + 1);
        }
        return counts;
    }

    public int maxNumberOfBalloons(String text) {
        Map<Character, Integer> charCounts = getCharCounts(text);
        System.out.println(charCounts);
        for (char c : "balon".toCharArray()) {
            charCounts.put(c, charCounts.getOrDefault(c, 0));
        }

        int numBalloons = Integer.MAX_VALUE;
        for (char c : "ban".toCharArray()) {
            if (charCounts.containsKey(c) && charCounts.get(c) < numBalloons) {
                numBalloons = charCounts.get(c);
            }
        }
        for (char c : "ol".toCharArray()) {
            if (charCounts.containsKey(c) && charCounts.get(c) / 2 < numBalloons) {
                numBalloons = charCounts.get(c) / 2;
            }
        }
        return numBalloons;
    }
}