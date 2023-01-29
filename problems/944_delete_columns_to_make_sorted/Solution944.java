class Solution944 {
    public int minDeletionSize(String[] strs) {
        int numColumns = strs[0].length();
        int output = 0;
        for (int i = 0; i < numColumns; i++) {
            for (int j = 0; j < strs.length - 1; j++) {
                if (strs[j].charAt(i) > strs[j + 1].charAt(i)) {
                    output++;
                    break;
                }
            }
        }
        return output;
    }
}