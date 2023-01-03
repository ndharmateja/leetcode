class Solution151 {
    public String reverseWords(String s) {
        StringBuilder sentenceBuilder = new StringBuilder();
        StringBuilder wordBuilder = new StringBuilder();
        s = s.trim();
        for (char c : s.toCharArray()) {
            if (c != ' ') {
                wordBuilder.append(c);
            } else if (c == ' ' && wordBuilder.length() > 0) {
                sentenceBuilder.append(wordBuilder.reverse());
                sentenceBuilder.append(' ');
                wordBuilder.setLength(0);
            }
        }
        if (wordBuilder.length() > 0)
            sentenceBuilder.append(wordBuilder.reverse());
        return sentenceBuilder.reverse().toString();
    }
}