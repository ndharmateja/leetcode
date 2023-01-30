package data_structures;

import java.util.HashMap;
import java.util.Map;

public class Trie {
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

    public boolean search(String word) {
        TrieNode curr = this.root;
        for (char c : word.toCharArray()) {
            if (!curr.children.containsKey(c))
                return false;
            curr = curr.children.get(c);
        }
        return curr.isWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode curr = this.root;
        for (char c : prefix.toCharArray()) {
            if (!curr.children.containsKey(c))
                return false;
            curr = curr.children.get(c);
        }
        return true;
    }
}