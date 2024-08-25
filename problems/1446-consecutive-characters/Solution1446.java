class Solution1446 {
    public int maxPower(String s) {
        char curr = s.charAt(0);
        int currLength = 1;
        int maxLength = currLength;

        for (int i = 1; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == curr) {
                currLength++;
            } else {
                curr = c;
                maxLength = Math.max(currLength, maxLength);
                currLength = 1;
            }
        }
        maxLength = Math.max(currLength, maxLength);

        return maxLength;
    }
}