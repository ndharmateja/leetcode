class Solution1154 {
    public int dayOfYear(String date) {
        int[] days = new int[] { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int year = Integer.parseInt(date.substring(0, 4));
        int month = Integer.parseInt(date.substring(5, 7));
        int day = Integer.parseInt(date.substring(8, 10));

        boolean isLeapYear = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

        int numDays = day;
        for (int i = 0; i < month - 1; i++) {
            numDays += days[i];
        }
        if (isLeapYear && month > 2) {
            numDays++;
        }

        return numDays;
    }
}