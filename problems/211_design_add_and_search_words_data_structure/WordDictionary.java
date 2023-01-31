import java.util.HashMap;
import java.util.Map;

class WordDictionary {
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

    TrieNode root;

    public WordDictionary() {
        this.root = new TrieNode("");
    }

    public void addWord(String word) {
        TrieNode curr = this.root;
        for (char c : word.toCharArray()) {
            if (!curr.children.containsKey(c)) {
                curr.children.put(c, new TrieNode(curr.text + c));
            }
            curr = curr.children.get(c);
        }
        curr.isWord = true;
    }

    // Wildcard search: .ad => will look for bad, mad, dad etc
    public boolean search(String word) {
        return search(word, this.root);
    }

    // We can also get the list of search results
    // by creating an empty list and populating it as
    // we run this method recursively
    private boolean search(String word, TrieNode node) {
        // If we reach the end of the word
        // if the node is a valid word, we return true
        // else we return false
        if (word.length() == 0) {
            if (node.isWord) {
                return true;
            }
            return false;
        }

        // We search of the substring without the first char
        // If curr char is a '.', we search through
        // all the children and if any of them returns true,
        // we return true
        // If curr char is not a '.' we search through
        // that particular child and if it returns true
        // we return true
        char c = word.charAt(0);
        String remainingWord = word.substring(1);
        if (c == '.') {
            for (char child : node.children.keySet()) {
                if (search(remainingWord, node.children.get(child)))
                    return true;
            }
        } else if (node.children.containsKey(c)) {
            if (search(remainingWord, node.children.get(c)))
                return true;
            ;
        }

        // Else we return false
        return false;
    }
}