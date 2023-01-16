class Solution125 {

    public boolean isPalindrome(String s) {
        return solution1(s);
    }

    // O(n) time and O(n) space solution
    private boolean solution1(String s) {
        s = s.toLowerCase();
        s = s.replaceAll("[^a-z0-9]", "");
        if (s.length() == 0)
            return true;
        for (int i = 0; i < s.length() / 2; i++) {
            if (s.charAt(i) != s.charAt(s.length() - i - 1)) {
                return false;
            }
        }
        return true;
    }
}