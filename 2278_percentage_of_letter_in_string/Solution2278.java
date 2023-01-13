class Solution2278 {
    // O(n) time and O(1) space solution
    public int percentageLetter(String s, char letter) {
        int letterCount = 0;
        for (char c : s.toCharArray()) {
            if (c == letter)
                letterCount++;
        }
        return 100 * letterCount / s.length();
    }
}