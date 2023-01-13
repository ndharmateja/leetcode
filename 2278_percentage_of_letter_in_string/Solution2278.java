class Solution2278 {
    public int percentageLetter(String s, char letter) {
        int totalCount = 0;
        int letterCount = 0;
        for (char c : s.toCharArray()) {
            if (c == letter) {
                letterCount++;
            }
            totalCount++;
        }
        return 100 * letterCount / totalCount;
    }
}