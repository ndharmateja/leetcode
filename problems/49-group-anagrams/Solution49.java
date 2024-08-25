import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

@SuppressWarnings("unused")
class Solution49 {
    // We create it once so that it can be used for every string
    private int[] counts = new int[26];

    // Key of a string is its sorted chars array string
    // which will be same for all the anagrams
    private String getKey2(String str) {
        char[] chars = str.toCharArray();
        Arrays.sort(chars);

        // new String(chars) is much faster than Arrays.toString(chars)
        return new String(chars);
    }

    // Key of a string is the counts array string
    // which will be same for all the anagrams
    private String getKey1(String str) {
        Arrays.fill(counts, 0);
        for (char c : str.toCharArray()) {
            counts[c - 'a']++;
        }
        return Arrays.toString(counts);
    }

    private String getKey(String str) {
        return getKey1(str);
    }

    public List<List<String>> groupAnagrams(String[] strs) {
        HashMap<String, List<String>> map = new HashMap<>();
        for (String str : strs) {
            String key = getKey(str);
            if (!map.containsKey(key))
                map.put(key, new ArrayList<>());
            map.get(key).add(str);
        }

        return new ArrayList<>(map.values());
    }
}