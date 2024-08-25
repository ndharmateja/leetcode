class Solution2409 {
    // gets the day number in a year for a data (say 08-15)
    private int getDayOfYear(String date) {
        int[] days = new int[] { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int month = Integer.parseInt(date.substring(0, 2));
        int day = Integer.parseInt(date.substring(3, 5));

        int numDays = day;
        for (int i = 0; i < month - 1; i++) {
            numDays += days[i];
        }

        return numDays;
    }

    public int countDaysTogether(String arriveAlice, String leaveAlice, String arriveBob, String leaveBob) {
        // Get day number for all the four dates
        int arriveAliceDays = getDayOfYear(arriveAlice);
        int leaveAliceDays = getDayOfYear(leaveAlice);
        int arriveBobDays = getDayOfYear(arriveBob);
        int leaveBobDays = getDayOfYear(leaveBob);

        // Get the interval start and end day numbers
        int intervalStart = Math.max(arriveAliceDays, arriveBobDays);
        int intervalEnd = Math.min(leaveAliceDays, leaveBobDays);

        // Difference between them (+1) is the number of days
        // o if difference is negative
        return Math.max(0, intervalEnd - intervalStart + 1);
    }
}