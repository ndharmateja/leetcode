class Solution1732 {
    public int largestAltitude(int[] gain) {
        int highestAltitude = 0;
        int currentAltitude = 0;
        for (int gainValue : gain) {
            currentAltitude += gainValue;
            if (currentAltitude > highestAltitude)
                highestAltitude = currentAltitude;
        }
        return highestAltitude;
    }
}