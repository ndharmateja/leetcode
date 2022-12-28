class Solution9 {
    private boolean isPalindrome(String string) {
        if (string.length() == 0 || string.length() == 1)
            return true;
        return string.charAt(0) == string.charAt(string.length() - 1)
                && isPalindrome(string.substring(1, string.length() - 1));
    }

    // Checks palindrome after converting to string
    @SuppressWarnings("unused")
    private boolean solution1(int x) {
        String xString = Integer.toString(x);
        return isPalindrome(xString);
    }

    private int reverseNumber(int x) {
        // number of digits
        int numDigits = (int) Math.floor(Math.log10(x) + 1);
        int reversed = 0;
        for (int i = 0; i < numDigits; i++) {
            int unitsDigit = x % 10;
            x = x / 10;
            reversed += unitsDigit * ((int) Math.pow(10, numDigits - i - 1));
        }
        return reversed;
    }

    // Checks palindrome without converting to string
    private boolean solution2(int x) {
        return x == reverseNumber(x);
    }

    public boolean isPalindrome(int x) {
        return solution2(x);
    }
}