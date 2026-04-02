#include <vector>
#include <string>
#include <unordered_map>

class Solution
{
private:
    // Here the argument is copied
    // So we can modify the given input copy and sort it
    // and return that as the key
    // This works well for keys as each string length <= 100
    static std::string get_key(std::string str)
    {
        std::sort(str.begin(), str.end());
        return str;
    }

public:
    /**
     * Say n - #strings, k - length of each string
     * Theta(n * klgk) time and Theta(n) space
     * Each of the n strings is sorted
     * and the space is for the unordered map
     */
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> &strs)
    {
        // We store the map of which index the anagrams of the same word
        // go into in the result. All the anagrams have the same key
        // and that key is the key in the map and value is the index of
        // anagrams of this key in the result
        std::unordered_map<std::string, int> map;
        std::vector<std::vector<std::string>> result;
        for (const std::string &str : strs)
        {
            // Find the key
            std::string key{get_key(str)};

            // If the key already exists
            auto it = map.find(key);
            if (it != map.end())
                result[it->second].push_back(str);

            // If the key doesn't exist already
            // then the index of the current key would be the size of the result itself
            else
            {
                map[key] = result.size();
                result.push_back({str});
            }
        }

        return result;
    }
};