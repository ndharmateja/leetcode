class Solution1854 {
    public int maximumPopulation(int[][] logs) {
        int[] population = new int[2051];
        for (int[] log : logs) {
            int birth = log[0];
            int death = log[1];
            for (int i = birth; i < death; i++) {
                population[i] += 1;
            }
        }
        int maxPopulation = Integer.MIN_VALUE;
        int maxYear = -1;
        for (int i = 1950; i < 2051; i++) {
            if (population[i] > maxPopulation) {
                maxPopulation = population[i];
                maxYear = i;
            }
        }
        return maxYear;
    }
}