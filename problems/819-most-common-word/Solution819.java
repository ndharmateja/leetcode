import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

class Solution819 {
    public String mostCommonWord(String paragraph, String[] banned) {
        Set<String> bannedSet = new HashSet<>();
        for (String word : banned) {
            bannedSet.add(word);
        }

        Map<String, Integer> wordCounts = new HashMap<>();

        StringBuilder builder = new StringBuilder();
        for (char c : paragraph.toCharArray()) {
            if (Character.isAlphabetic(c)) {
                builder.append(Character.toLowerCase(c));
            } else {
                String word = builder.toString();
                if (word.length() > 0 && !bannedSet.contains(word)) {
                    wordCounts.put(word, wordCounts.getOrDefault(word, 0) + 1);
                }
                builder.setLength(0);
            }
        }
        if (builder.length() > 0) {
            String word = builder.toString();
            if (!bannedSet.contains(word)) {
                wordCounts.put(word, wordCounts.getOrDefault(word, 0) + 1);
            }
        }

        String maxWord = null;
        int maxWordCount = -1;
        for (String word : wordCounts.keySet()) {
            int count = wordCounts.get(word);
            if (count > maxWordCount) {
                maxWord = word;
                maxWordCount = count;
            }
        }

        return maxWord;
    }
}