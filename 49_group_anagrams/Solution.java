import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

class Solution {

    private String sortString(String str) {
        char[] chars = str.toCharArray();
        Arrays.sort(chars);
        return new String(chars);
    }

    public List<List<String>> groupAnagrams(String[] strs) {
        HashMap<String, List<String>> map = new HashMap<>();

        for (String str : strs) {
            String key = sortString(str);
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