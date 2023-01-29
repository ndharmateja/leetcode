class Solution1704 {
    public boolean halvesAreAlike(String s) {
        int n = s.length() / 2;

        int left = 0, right = 0;
        for (int i = 0; i < s.toCharArray().length; i++) {
            char c = Character.toLowerCase(s.charAt(i));
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                if (i < n)
                    left++;
                else
                    right++;
            }
        }

        return left == right;
    }
}