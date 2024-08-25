class Solution14 {
    // O(mn) time and O(1) space solution
    // m - number of strings
    // n - length of each string
    public String longestCommonPrefix(String[] strs) {
        StringBuilder output = new StringBuilder();
        for (int i = 0; i < strs[0].length(); i++) {
            char curr = strs[0].charAt(i);
            for (String str : strs) {
                if (i == str.length() || curr != str.charAt(i)) {
                    return output.toString();
                }
            }
            output.append(curr);
        }
        return output.toString();
    }
}