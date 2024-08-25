class Solution557 {
    public String reverseWords(String s) {
        StringBuilder output = new StringBuilder();
        StringBuilder word = new StringBuilder();

        // Iterate char by char
        for (char c : s.toCharArray()) {
            // If char is space and word has length > 0
            // we append the reverse word
            if (Character.isSpaceChar(c) && word.length() > 0) {
                output.append(word.reverse());
                word.setLength(0);
            }

            // Append char to 'output' or 'word'
            // based on whether char is space
            (Character.isSpaceChar(c) ? output : word).append(c);
        }

        // Append last word in reverse if applicable
        output.append(word.reverse());

        return output.toString();
    }
}