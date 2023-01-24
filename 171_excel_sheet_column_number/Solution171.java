class Solution171 {
    public int titleToNumber(String columnTitle) {
        int output = 0;

        int n = columnTitle.length();
        for (int i = 0; i < n; i++) {
            // 'A' -> 1, 'B' -> 2 etc
            int currCharValue = columnTitle.charAt(n - i - 1) - 'A' + 1;
            output += currCharValue * (int) Math.pow(26, i);
        }

        return output;
    }
}