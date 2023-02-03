class Solution6 {
    public String convert(String s, int numRows) {
        if (numRows == 1)
            return s;
        StringBuilder builder = new StringBuilder();

        // difference between each vertical column in the zigzag
        int offset = 2 * (numRows - 1);
        for (int i = 0; i < numRows; i++) {
            int j = 0;
            while (true) {
                // Indexes of each vertical column for a given row index 'i'
                int index1 = (j++ * offset) + i;
                if (index1 >= s.length())
                    break;
                builder.append(s.charAt(index1));

                // Column indexes between vertical columns
                // We don't need to do this for the first and
                // last rows
                if (i != 0 && i != numRows - 1) {
                    int index2 = index1 + offset - (2 * i);
                    if (index2 >= s.length())
                        break;
                    builder.append(s.charAt(index2));
                }
            }

        }

        return builder.toString();
    }
}