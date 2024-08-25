class Solution520 {
    private boolean isUpper(String word, int i) {
        return Character.isUpperCase(word.charAt(i));
    }

    private boolean isLower(String word, int i) {
        return Character.isLowerCase(word.charAt(i));
    }

    public boolean detectCapitalUse(String word) {
        if (word.length() == 0 || word.length() == 1) {
            return true;
        }

        boolean isAllCaps = isUpper(word, 0) && isUpper(word, 1);
        boolean isAllLower = isLower(word, 0) && isLower(word, 1);
        boolean isTitle = isUpper(word, 0) && isLower(word, 1);

        if (isLower(word, 0) && isUpper(word, 1))
            return false;

        for (int i = 2; i < word.length(); i++) {
            if (isAllCaps && isLower(word, i))
                return false;
            if ((isAllLower || isTitle) && isUpper(word, i))
                return false;
        }

        return true;
    }
}