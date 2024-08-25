class Solution2288 {
    private String processWord(StringBuilder wordBuilder, int discount) {
        if (wordBuilder.charAt(0) != '$')
            return wordBuilder.toString();
        try {
            long price = Long.parseLong(wordBuilder.substring(1));
            System.out.println("price:" + price);
            return String.format("$%.2f", (double) price * (100 - discount) / 100);
        } catch (NumberFormatException e) {
            return wordBuilder.toString();
        }
    }

    public String discountPrices(String sentence, int discount) {
        StringBuilder sentenceBuilder = new StringBuilder();
        StringBuilder wordBuilder = new StringBuilder();
        for (char c : sentence.toCharArray()) {
            if (c == ' ') {
                sentenceBuilder.append(processWord(wordBuilder, discount));
                sentenceBuilder.append(' ');
                wordBuilder.setLength(0);
            } else {
                wordBuilder.append(c);
            }
        }
        sentenceBuilder.append(processWord(wordBuilder, discount));
        return sentenceBuilder.toString();
    }
}