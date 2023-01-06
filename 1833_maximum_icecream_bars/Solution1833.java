import java.util.Arrays;

@SuppressWarnings("unused")
class Solution1833 {
    public int maxIceCream(int[] costs, int coins) {
        return solution1(costs, coins);
    }

    // O(n + k log n) time
    // If the answer is 'k'
    // Heapify the array and run remove min 'k' times
    private int solution2(int[] costs, int coins) {
        return -1;
    }

    // O(n log n) time
    // Sort the array and greedily buy the cheapest ones
    private int solution1(int[] costs, int coins) {
        Arrays.sort(costs);

        int count = 0;
        int sum = 0;
        for (int cost : costs) {
            if (sum + cost > coins) {
                return count;
            }
            sum += cost;
            count++;
        }

        return count;
    }
}