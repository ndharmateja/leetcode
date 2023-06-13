import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

@SuppressWarnings("unused")
class Solution49 {
    // Key of a string is its sorted chars array string
    // which will be same for all the anagrams
    private String getKey2(String str) {
        char[] chars = str.toCharArray();
        Arrays.sort(chars);
        return Arrays.toString(chars);
    }

    // Key of a string is the counts array string
    // which will be same for all the anagrams
    private String getKey1(String str, int[] counts) {
        Arrays.fill(counts, 0);
        for (char c : str.toCharArray()) {
            counts[c - 'a']++;
        }
        return Arrays.toString(counts);
    }

    public List<List<String>> groupAnagrams(String[] strs) {
        HashMap<String, List<String>> map = new HashMap<>();
        int[] counts = new int[26];
        for (String str : strs) {
            String key = getKey1(str, counts);
            List<String> anagramGroup = map.getOrDefault(key, new ArrayList<>());
            anagramGroup.add(str);
            map.put(key, anagramGroup);
        }

        List<List<String>> anagramGroups = new ArrayList<>();
        for (List<String> anagramGroup : map.values()) {
            anagramGroups.add(anagramGroup);
        }

        return anagramGroups;
    }
}