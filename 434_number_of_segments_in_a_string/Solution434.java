class Solution434 {
    public int countSegments(String s) {
        int numWords = 0;
        boolean isWord = false;
        for (char c : s.toCharArray()) {
            if (isWord && Character.isSpaceChar(c)) {
                isWord = false;
            }
            if (!isWord && !Character.isSpaceChar(c)) {
                numWords++;
                isWord = true;
            }
        }
        return numWords;
    }
}