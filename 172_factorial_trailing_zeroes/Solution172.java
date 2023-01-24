class Solution172 {
    public int trailingZeroes(int n) {
        int output = 0;

        // Count number of each power of five
        // that are less than 'n'
        int currFivePower = 5;
        while (currFivePower <= n) {
            output += n / currFivePower;
            currFivePower *= 5;
        }

        return output;
    }
}