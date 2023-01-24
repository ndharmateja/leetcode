class Solution504 {
    public String convertToBase7(int num) {
        if (num == 0)
            return "0";

        StringBuilder builder = new StringBuilder();
        if (num < 0) {
            num = -num;
            builder.append("-");
        }

        int highesExponentOfSeven = (int) Math.floor(Math.log(num) / Math.log(7));
        for (int i = highesExponentOfSeven; i >= 0; i--) {
            int sevenPower = (int) Math.pow(7, i);
            builder.append(num / sevenPower);
            num %= sevenPower;
        }

        return builder.toString();
    }
}