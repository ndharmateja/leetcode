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
    @SuppressWarnings("unused")
    private int solution2(String s) {
        String[] words = s.trim().split(" ");
        return words[words.length - 1].length();
    }

    // Iterate from right
    private int solution3(String s) {
        int count = 0;
        boolean wordEncountered = false;
        for (int i = s.length() - 1; i >= 0; i--) {
            char c = s.charAt(i);
            if (c == ' ') {
                if (wordEncountered)
                    break;
                else
                    continue;
            }
            wordEncountered = true;
            count++;
        }
        return count;
    }

    public int lengthOfLastWord(String s) {
        return solution3(s);
    }
}