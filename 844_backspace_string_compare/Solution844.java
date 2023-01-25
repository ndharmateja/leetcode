class Solution844 {
    private StringBuilder process(String string) {
        StringBuilder builder = new StringBuilder();

        for (char c : string.toCharArray()) {
            if (c == '#' && builder.length() > 0)
                builder.setLength(builder.length() - 1);
            else if (c != '#')
                builder.append(c);
        }

        return builder;
    }

    public boolean backspaceCompare(String s, String t) {
        return process(s).compareTo(process(t)) == 0;
    }
}