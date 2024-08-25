class Solution67 {
    public String addBinary(String a, String b) {
        // String builder for total string
        StringBuilder builder = new StringBuilder();

        // Reverse the strings
        a = (new StringBuilder(a)).reverse().toString();
        b = (new StringBuilder(b)).reverse().toString();
        int carry = 0;

        for (int i = 0; i < Math.max(a.length(), b.length()); i++) {
            // if 'i' is out of bounds, digit will be zero
            int digitA = i < a.length() ? a.charAt(i) - '0' : 0;
            int digitB = i < b.length() ? b.charAt(i) - '0' : 0;
            int sum = carry + digitA + digitB;

            builder.append(sum % 2);
            carry = sum / 2;
        }

        if (carry != 0) {
            builder.append(1);
        }

        return builder.reverse().toString();
    }
}