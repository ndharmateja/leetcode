class Solution1678 {
    public String interpret(String command) {
        StringBuilder builder = new StringBuilder();
        StringBuilder word = new StringBuilder();

        for (char c : command.toCharArray()) {
            if (c == 'G' || c == '(') {
                // Append previous word
                if (word.length() == 1)
                    builder.append('G');
                else if (word.length() == 2)
                    builder.append('o');
                else if (word.length() == 4)
                    builder.append("al");

                // Reset word
                word.setLength(0);
            }

            // Add curr char to word
            word.append(c);
        }

        // Append the last word
        if (word.length() == 1)
            builder.append('G');
        else if (word.length() == 2)
            builder.append('o');
        else if (word.length() == 4)
            builder.append("al");

        return builder.toString();
    }
}