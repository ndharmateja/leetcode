import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution1807 {
    // O(n) time and O(n) space solution
    public String evaluate(String s, List<List<String>> knowledge) {
        // Put all key values in a map
        Map<String, String> map = new HashMap<>();
        for (List<String> keyValue : knowledge) {
            map.put(keyValue.get(0), keyValue.get(1));
        }

        StringBuilder builder = new StringBuilder();
        StringBuilder word = new StringBuilder();
        boolean isBracketPair = false;

        for (char c : s.toCharArray()) {
            // If opening bracket and isBracketPair is false
            // we make the boolean true
            if (c == '(' && !isBracketPair) {
                isBracketPair = true;
            }
            // If closing bracket and isBracketPair is true
            // we add the word (with value from map) to our builder
            // and make the boolean false and reset word
            else if (c == ')' && isBracketPair) {
                builder.append(map.getOrDefault(word.toString(), "?"));
                word.setLength(0);
                isBracketPair = false;
            }
            // if it is part of a bracket pair
            // we add it to the word
            else if (isBracketPair) {
                word.append(c);
            }
            // if it is not a bracket pair
            // we add it to our builder
            else if (!isBracketPair) {
                builder.append(c);
            }
        }

        return builder.toString();
    }
}