import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution1807 {
    public String evaluate(String s, List<List<String>> knowledge) {
        Map<String, String> map = new HashMap<>();
        for (List<String> keyValue : knowledge) {
            map.put(keyValue.get(0), keyValue.get(1));
        }

        StringBuilder builder = new StringBuilder();
        StringBuilder word = new StringBuilder();
        boolean isBracketPair = false;

        for (char c : s.toCharArray()) {
            if (c == '(' && !isBracketPair) {
                isBracketPair = true;
            } else if (c == ')' && isBracketPair) {
                builder.append(map.getOrDefault(word.toString(), "?"));
                word.setLength(0);
                isBracketPair = false;
            } else if (isBracketPair) {
                word.append(c);
            } else if (!isBracketPair) {
                builder.append(c);
            }
        }

        return builder.toString();
    }
}