import java.util.HashMap;
import java.util.Map;

class Solution290 {

    public boolean wordPattern(String pattern, String s) {
        Map<Character, String> map = new HashMap<>();
        Map<String, Character> reverseMap = new HashMap<>();

        String[] sWords = s.split(" ");
        if (pattern.length() != sWords.length)
            return false;

        for (int i = 0; i < sWords.length; i++) {
            char c = pattern.charAt(i);
            String word = sWords[i];

            if (!map.containsKey(c)) {
                map.put(c, word);
            }
            if (!reverseMap.containsKey(word)) {
                reverseMap.put(word, c);
            }
            if (!map.get(c).equals(word) || !reverseMap.get(word).equals(c)) {
                return false;
            }
        }

        return true;
    }

}