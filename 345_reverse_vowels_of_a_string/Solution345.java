import java.util.ArrayList;
import java.util.List;
import java.util.Set;

class Solution345 {
    public String reverseVowels(String s) {
        List<Character> vowels = new ArrayList<>();
        Set<Character> vowelsSet = Set.of('a', 'e', 'i', 'o', 'u');

        for (char c : s.toCharArray()) {
            if (vowelsSet.contains(Character.toLowerCase(c)))
                vowels.add(c);
        }

        int i = vowels.size() - 1;
        StringBuilder output = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (vowelsSet.contains(Character.toLowerCase(c))) {
                output.append(vowels.get(i--));
            } else {
                output.append(c);
            }
        }

        return output.toString();
    }
}