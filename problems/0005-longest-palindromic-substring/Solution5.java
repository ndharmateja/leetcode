public class Solution5 {
    // char at 0 is the initial longest palindrome
    private int start = 0;
    private int end = 0;

    private void runExpandingAroundCenter(String s, int l, int r) {
        int n = s.length();
        while (l >= 0 && r < n && s.charAt(l) == s.charAt(r)) {
            // if length of current pallindrome (from l to r inclusive)
            // is greater than (from start to end inclusive)
            // update start and end
            if (r - l + 1 > end - start + 1) {
                start = l;
                end = r;
            }
            l--;
            r++;
        }
    }

    private String solution1(String s) {
        // Start at char at i and expand outwards to see if it is a palindrome
        // and if it is a palindrome
        // update the start and end positions of the largest palindrome
        for (int i = 0; i < s.length(); i++) {
            // odd lengthed palindromes
            // we can start with palindromes of length 3
            // as 1 lengthed palindrome is already recorded
            // by initializing start = 0, end = 0 => first char is the initial
            // longest palindrome
            runExpandingAroundCenter(s, i - 1, i + 1);

            // even lengthed palindromes
            runExpandingAroundCenter(s, i, i + 1);
        }

        return s.substring(start, end + 1);
    }

    public String longestPalindrome(String s) {
        return solution1(s);
    }

    public static void main(String[] args) {
        System.out.println(new Solution5().longestPalindrome("babad"));
    }
}
