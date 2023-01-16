@SuppressWarnings("unused")
class Solution125 {

    public boolean isPalindrome(String s) {
        return solution2(s);
    }

    // O(n) time and O(1) space solution
    // Using left and right pointers
    private boolean solution2(String s) {
        int l = 0;
        int r = s.length() - 1;
        while (l < r) {
            if (!Character.isLetterOrDigit(s.charAt(l))) {
                l++;
                continue;
            }
            if (!Character.isLetterOrDigit(s.charAt(r))) {
                r--;
                continue;
            }
            if (Character.toLowerCase(s.charAt(l++)) != Character.toLowerCase(s.charAt(r--)))
                return false;
        }

        return true;
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