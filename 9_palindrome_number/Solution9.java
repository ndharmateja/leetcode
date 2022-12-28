class Solution9 {
    private boolean isPalindrome(String string) {
        if (string.length() == 0 || string.length() == 1)
            return true;
        return string.charAt(0) == string.charAt(string.length() - 1)
                && isPalindrome(string.substring(1, string.length() - 1));
    }

    // Checks palindrome after converting to string
    private boolean solution1(int x) {
        String xString = Integer.toString(x);
        return isPalindrome(xString);
    }

    public boolean isPalindrome(int x) {
        return solution1(x);
    }
}