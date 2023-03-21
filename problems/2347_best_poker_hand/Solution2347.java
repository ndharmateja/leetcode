import java.util.HashMap;
import java.util.Map;

class Solution2347 {
    private boolean isFlush(char[] suits) {
        char first = suits[0];
        for (int i = 1; i < suits.length; i++) {
            if (suits[i] != first)
                return false;
        }
        return true;
    }

    public String bestHand(int[] ranks, char[] suits) {
        if (isFlush(suits))
            return "Flush";

        Map<Integer, Integer> rankCounts = new HashMap<>();
        for (int rank : ranks) {
            rankCounts.put(rank, rankCounts.getOrDefault(rank, 0) + 1);
        }

        boolean hasTriplet = false;
        boolean hasPair = false;
        for (int count : rankCounts.values()) {
            if (count >= 3) {
                hasTriplet = true;
                break;
            }
            if (count >= 2) {
                hasPair = true;
            }
        }

        if (hasTriplet)
            return "Three of a Kind";
        if (hasPair)
            return "Pair";

        return "High Card";
    }
}