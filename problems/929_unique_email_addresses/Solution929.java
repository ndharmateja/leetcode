import java.util.HashSet;
import java.util.Set;

class Solution929 {
    private String cleanEmail(String email) {
        StringBuilder builder = new StringBuilder();

        // Iterate over character by character
        // and build the domain name
        int i = 0;
        char c;
        boolean toIgnore = false;
        while ((c = email.charAt(i++)) != '@') {
            if (toIgnore)
                continue;
            if (c == '+') {
                toIgnore = true;
                continue;
            }
            if (c == '.')
                continue;
            builder.append(c);
        }

        // Adding @ and the domain to the key
        builder.append('@');
        while (i < email.length()) {
            builder.append(email.charAt(i++));
        }

        // Return the cleaned email
        return builder.toString();
    }

    public int numUniqueEmails(String[] emails) {
        Set<String> uniqueEmails = new HashSet<>();

        for (String email : emails)
            uniqueEmails.add(cleanEmail(email));

        return uniqueEmails.size();
    }
}