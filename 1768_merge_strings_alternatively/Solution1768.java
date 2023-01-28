class Solution1768 {
    public String mergeAlternately(String word1, String word2) {
        StringBuilder builder = new StringBuilder();

        boolean firstWord = true;
        int i = 0;

        while (i < word1.length() && i < word2.length()) {
            if (firstWord)
                builder.append(word1.charAt(i));
            else
                builder.append(word2.charAt(i++));
            firstWord = !firstWord;
        }

        while (i < word1.length()) {
            builder.append(word1.charAt(i++));
        }

        while (i < word2.length()) {
            builder.append(word2.charAt(i++));
        }

        return builder.toString();
    }
}