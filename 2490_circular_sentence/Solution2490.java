class Solution2490 {
    public boolean isCircularSentence(String sentence) {
        String[] words = sentence.trim().split(" ");
        String firstWord = words[0];
        String lastWord = words[words.length - 1];
        if (firstWord.charAt(0) != lastWord.charAt(lastWord.length() - 1))
            return false;
        for (int i = 0; i < words.length - 1; i++) {
            String word = words[i];
            String nextWord = words[i + 1];
            if (word.charAt(word.length() - 1) != nextWord.charAt(0))
                return false;
        }
        return true;
    }
}