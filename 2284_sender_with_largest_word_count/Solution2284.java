import java.util.HashMap;
import java.util.Map;

class Solution2284 {
    private int getWordCount(String messsage) {
        int spaces = 0;
        for (char c : messsage.toCharArray()) {
            if (c == ' ')
                spaces++;
        }
        return spaces + 1;
    }

    public String largestWordCount(String[] messages, String[] senders) {
        Map<String, Integer> senderWordCounts = new HashMap<>();
        for (int i = 0; i < senders.length; i++) {
            String sender = senders[i];
            String message = messages[i];
            senderWordCounts.put(sender, senderWordCounts.getOrDefault(sender, 0) + getWordCount(message));
        }

        String maxSender = null;
        int maxWords = 0;

        for (String sender : senderWordCounts.keySet()) {
            int numWords = senderWordCounts.get(sender);
            if (numWords > maxWords || (numWords == maxWords && sender.compareTo(maxSender) > 0)) {
                maxSender = sender;
                maxWords = numWords;
            }
        }

        return maxSender;
    }
}