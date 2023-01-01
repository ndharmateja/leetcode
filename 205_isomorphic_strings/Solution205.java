import java.util.HashMap;
import java.util.Map;

class Solution205 {
    public boolean isIsomorphic(String s, String t) {
        Map<Character, Character> map = new HashMap<>();
        Map<Character, Character> reverseMap = new HashMap<>();

        if (s.length() != t.length())
            return false;

        for (int i = 0; i < s.length(); i++) {
            char sChar = s.charAt(i);
            char tChar = t.charAt(i);

            if (!map.containsKey(sChar)) {
                map.put(sChar, tChar);
            }
            if (!reverseMap.containsKey(tChar)) {
                reverseMap.put(tChar, sChar);
            }
            if (!map.get(sChar).equals(tChar) || !reverseMap.get(tChar).equals(sChar)) {
                return false;
            }
        }

        return true;
    }
}