class Solution680 {
    private boolean isPalindrome(char[] chars, int low, int high) {
        if (low == high)
            return true;
        if (high - low == 1)
            return chars[low] == chars[high];
        return chars[low] == chars[high] && isPalindrome(chars, low + 1, high - 1);
    }

    private boolean isPalindromeOneOff(char[] chars, int low, int high) {
        if (low == high || high - low == 1)
            return true;
        if (chars[high] == chars[low])
            return isPalindromeOneOff(chars, low + 1, high - 1);
        return isPalindrome(chars, low + 1, high) || isPalindrome(chars, low, high - 1);
    }

    public boolean validPalindrome(String s) {
        return isPalindromeOneOff(s.toCharArray(), 0, s.length() - 1);
    }
}