class Solution1662 {
    public boolean arrayStringsAreEqual(String[] words1, String[] words2) {
        StringBuilder builder1 = getStringBuilder(words1);
        StringBuilder builder2 = getStringBuilder(words2);

        return builder1.compareTo(builder2) == 0;
    }

    private StringBuilder getStringBuilder(String[] words) {
        StringBuilder builder = new StringBuilder();
        for (String word : words)
            builder.append(word);
        return builder;
    }
}