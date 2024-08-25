class Solution392 {
    public boolean isSubsequence(String s, String t) {
        int i = 0, j = 0;
        while (i < s.length() && j < t.length()) {
            // curr char of 's'
            char sChar = s.charAt(i);

            // Loop until we find the matching char in 't'
            while (j < t.length() && t.charAt(j) != sChar) {
                j++;
            }

            // If 'j' still hasn't reached the end of 't'
            // that means we have found the match
            // so now we can increment 'i' and 'j'
            if (j < t.length()) {
                i++;
                j++;
            }
        }

        // If all chars of 's' are covered
        // then it is a subsequence
        // Otherwise it is not
        return i == s.length();
    }
}