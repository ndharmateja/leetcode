@SuppressWarnings("unused")
class Solution28 {

    // improvement: Use Rabin-Karp's algorithm
    private int solution2(String haystack, String needle) {
        return -1;
    }

    // Using inbuilt library
    private int solution1(String haystack, String needle) {
        return haystack.indexOf(needle, 0);
    }

    public int strStr(String haystack, String needle) {
        return solution1(haystack, needle);
    }
}