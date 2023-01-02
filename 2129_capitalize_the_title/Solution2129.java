import java.util.Arrays;

@SuppressWarnings("unused")
class Solution {
    public String capitalizeTitle(String title) {
        return solution2(title);
    }

    // Using array stream
    private String solution1(String title) {
        return String
                .join(" ",
                        Arrays.stream(title.split(" "))
                                .map(s -> s.length() <= 2
                                        ? s.toLowerCase()
                                        : Character.toUpperCase(s.charAt(0)) + s.substring(1).toLowerCase())
                                .toArray(String[]::new));
    }

    // Iterating char by char
    private String solution2(String title) {
        StringBuilder titleBuilder = new StringBuilder();
        StringBuilder wordBuilder = new StringBuilder();

        for (char ch : title.toCharArray()) {
            if (ch == ' ') {
                if (wordBuilder.length() <= 2) {
                    titleBuilder.append(wordBuilder.toString().toLowerCase());
                } else {
                    titleBuilder.append(Character.toUpperCase(wordBuilder.charAt(0)));
                    titleBuilder.append(wordBuilder.substring(1).toLowerCase());
                }
                titleBuilder.append(" ");
                wordBuilder.setLength(0);
            } else {
                wordBuilder.append(ch);
            }
        }

        if (wordBuilder.length() <= 2) {
            titleBuilder.append(wordBuilder.toString().toLowerCase());
        } else {
            titleBuilder.append(Character.toUpperCase(wordBuilder.charAt(0)));
            titleBuilder.append(wordBuilder.substring(1).toLowerCase());
        }

        return titleBuilder.toString();

    }
}