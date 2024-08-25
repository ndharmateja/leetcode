class Solution2114 {
    private int numWords(String sentence) {
        int numSpaces = 0;
        for (char c : sentence.toCharArray()) {
            if (Character.isSpaceChar(c)) {
                numSpaces++;
            }
        }
        return numSpaces + 1;
    }

    public int mostWordsFound(String[] sentences) {
        int maxWords = 0;
        for (String sentence : sentences)
            maxWords = Math.max(maxWords, numWords(sentence));
        return maxWords;
    }
}