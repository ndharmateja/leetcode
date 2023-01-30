import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Collections;

class Solution1268 {
    static class TrieNode {
        String text;
        Map<Character, TrieNode> children;
        boolean isWord;

        TrieNode(String text) {
            this.text = text;
            this.isWord = false;
            this.children = new HashMap<>();
        }
    }

    static class Trie {
        TrieNode root;

        public Trie() {
            this.root = new TrieNode("");
        }

        public void insert(String word) {
            TrieNode curr = this.root;
            for (char c : word.toCharArray()) {
                if (!curr.children.containsKey(c)) {
                    curr.children.put(c, new TrieNode(curr.text + c));
                }
                curr = curr.children.get(c);
            }
            curr.isWord = true;
        }

        private void preorderTraversal(TrieNode node, int limit, List<String> suggestions) {
            if (suggestions.size() == limit)
                return;
            if (node.isWord) {
                suggestions.add(node.text);
            }

            List<Character> validChildChars = new ArrayList<>(node.children.keySet());
            Collections.sort(validChildChars);

            for (char c : validChildChars) {
                preorderTraversal(node.children.get(c), limit, suggestions);
            }
        }

        public List<String> getSuggestions(String prefix, int limit) {
            return getSuggestions(new StringBuilder(prefix), limit);
        }

        public List<String> getSuggestions(StringBuilder prefix, int limit) {
            List<String> suggestions = new ArrayList<>();

            // Get to the prefix node
            TrieNode curr = this.root;
            for (int i = 0; i < prefix.length(); i++) {
                char c = prefix.charAt(i);
                // If any node along the path to the prefix node
                // doesn't exist, we return an empty list
                if (!curr.children.containsKey(c)) {
                    return suggestions;
                }
                curr = curr.children.get(c);
            }

            // curr - contains the node with the prefix
            // do search on the current node to get all the suggestions
            // and return the suggestions
            preorderTraversal(curr, limit, suggestions);

            return suggestions;
        }
    }

    // Improvement: Instead of having the search in the Trie class
    // we can have it in the TrieNode class, so we can save on traversing to through
    // the same path over and over again
    public List<List<String>> suggestedProducts(String[] products, String searchWord) {
        List<List<String>> output = new ArrayList<>();

        Trie trie = new Trie();
        for (String product : products)
            trie.insert(product);

        StringBuilder builder = new StringBuilder();
        for (char c : searchWord.toCharArray()) {
            builder.append(c);
            output.add(trie.getSuggestions(builder, 3));
        }

        return output;
    }
}