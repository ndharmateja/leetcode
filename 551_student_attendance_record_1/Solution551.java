class Solution551 {
    public boolean checkRecord(String s) {
        int numAbsents = 0;
        int numConsecutiveLs = 0;
        for (char c : s.toCharArray()) {
            if (c == 'L') {
                if (++numConsecutiveLs >= 3) {
                    return false;
                }
                continue;
            }
            numConsecutiveLs = 0;
            if (c == 'A') {
                if (++numAbsents >= 2) {
                    return false;
                }
            }
        }
        return true;
    }
}
