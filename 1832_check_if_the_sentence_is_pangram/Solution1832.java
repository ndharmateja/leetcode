import java.util.HashSet;
import java.util.Set;

class Solution1832 {
    public boolean checkIfPangram(String sentence) {
        Set<Character> alphabets = new HashSet<Character>();
        for (char ch : sentence.toCharArray()) {
            alphabets.add(ch);
        }
        return alphabets.size() == 26;
    }
}