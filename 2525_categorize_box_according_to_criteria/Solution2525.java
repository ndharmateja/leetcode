class Solution2525 {
    public String categorizeBox(int length, int width, int height, int mass) {
        long volume = (long) length * width * height;

        boolean isBulky = false;
        boolean isHeavy = false;
        if (length >= 10000 || height >= 10000 || width >= 10000 || volume >= 1000000000)
            isBulky = true;
        if (mass >= 100)
            isHeavy = true;

        if (isBulky && isHeavy)
            return "Both";
        if (isBulky)
            return "Bulky";
        if (isHeavy)
            return "Heavy";
        return "Neither";
    }
}