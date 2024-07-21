import java.util.ArrayList;
import java.util.List;

// Problem link: https://www.lintcode.com/problem/659/
// Method:
// 1. ["apple", "banana", "bubbleboyandmoops"]
// 2. Say delimiter is '#', we encode the list to 
// "5#apple6#banana17#bubbleboyandmoops"
// 3. We store the number of chars of word and a delimiter (delimiter is
// needed because first char of word could be a digit)
// 4. While decoding we can get num chars and get the numchars number of
// characters to form a word (doesn't matter even if the words themselves
// contain delimiters as we have the numChars in the word)
public class Solution271 {
    private final static char DELIMITER = '#';

    /*
     * @param strs: a list of strings
     * 
     * @return: encodes a list of strings to a single string.
     */
    public String encode(List<String> strs) {
        StringBuilder sb = new StringBuilder();

        for (String str : strs) {
            sb.append(str.length());
            sb.append(DELIMITER);
            sb.append(str);
        }

        return sb.toString();
    }

    /*
     * @param str: A string
     * 
     * @return: dcodes a single string to a list of strings
     */
    public List<String> decode(String str) {
        List<String> output = new ArrayList<>();

        int i = 0;
        StringBuilder sb = new StringBuilder();
        int currLength = 0;
        while (i < str.length()) {
            // As soon as we reach the delimiter
            // we parse the next currLength chars and add it to our output
            // and reset currLength and stringBuilder
            char c = str.charAt(i++);
            if (c == DELIMITER) {
                for (int j = 0; j < currLength; j++) {
                    sb.append(str.charAt(i++));
                }
                output.add(sb.toString());
                sb.setLength(0);
                currLength = 0;
                continue;
            }

            // If it is not a delimiter
            // it means this is a digit and part of the number
            // wo add the digit at the end of 'currLength'
            int digit = c - '0';
            currLength = currLength * 10 + digit;
        }

        return output;
    }

    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("");
        // list.add("neet");
        // list.add("code");
        // list.add("love");
        // list.add("you");

        Solution271 s = new Solution271();
        String encoded = s.encode(list);
        System.out.printf("'%s'\n", encoded);
        List<String> decoded = s.decode(encoded);
        System.out.println(decoded.size());
        System.out.println(decoded);
    }

}