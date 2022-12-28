class Solution58 {
    // Iterate character by character
    @SuppressWarnings("unused")
    private int solution1(String s) {
        String word = "";
        StringBuilder builder = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (c == ' ') {
                if (builder.length() > 0) {
                    word = builder.toString();
                }
                builder.setLength(0);
                continue;
            }
            builder.append(c);
        }
        if (builder.length() > 0) {
            word = builder.toString();
        }
        return word.length();
    }

    // use string split
    private int solution2(String s) {
        String[] words = s.trim().split(" ");
        return words[words.length - 1].length();
    }

    public int lengthOfLastWord(String s) {
        return solution2(s);
    }
}