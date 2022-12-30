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
    private final static char delimiter = '#';

    /*
     * @param strs: a list of strings
     * 
     * @return: encodes a list of strings to a single string.
     */
    public String encode(List<String> strs) {
        StringBuilder builder = new StringBuilder();

        for (String str : strs) {
            builder.append(str.length());
            builder.append(delimiter);
            builder.append(str);
        }

        return builder.toString();
    }

    /*
     * @param str: A string
     * 
     * @return: dcodes a single string to a list of strings
     */
    public List<String> decode(String str) {
        List<String> list = new ArrayList<>();

        boolean isNewWord = true;
        int numChars = -1;
        StringBuilder numCharsBuilder = new StringBuilder();
        StringBuilder currWordBuilder = new StringBuilder();

        // Iterate over the chars
        int i = 0;
        while (i < str.length()) {
            char ch = str.charAt(i);

            // if new word and char is digit
            // append digit to numCharsBuilder
            if (isNewWord && Character.isDigit(ch)) {
                numCharsBuilder.append(ch);
                i++;
                continue;
            }

            // If new word and char is delimiter
            // get numChars from numCharsBuilder
            // make isNewWord false and reset numCharsBuilder
            if (isNewWord && ch == delimiter) {
                numChars = Integer.parseInt(numCharsBuilder.toString());
                numCharsBuilder.setLength(0);
                isNewWord = false;
                i++;
                continue;
            }

            // Read 'numChar' number of characters and add word to list
            for (int j = 0; j < numChars; j++) {
                currWordBuilder.append(str.charAt(i + j));
            }

            // Add word to list and reset string builder
            i += numChars;
            list.add(currWordBuilder.toString());
            currWordBuilder.setLength(0);
            isNewWord = true;
        }

        return list;
    }

}