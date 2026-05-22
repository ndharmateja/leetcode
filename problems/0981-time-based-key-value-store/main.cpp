#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

class TimeMap
{
private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> map;

    static int binary_search(const std::vector<std::pair<int, std::string>> &values, int timestamp)
    {
        int n{static_cast<int>(values.size())}, lo{0}, hi{n - 1}, mid;
        int result{0};
        while (lo <= hi)
        {
            mid = lo + (hi - lo) / 2;
            int mid_timestamp{values[mid].first};
            if (mid_timestamp == timestamp)
                return mid;
            if (mid_timestamp < timestamp)
            {
                result = mid;
                lo = mid + 1;
            }
            else
                hi = mid - 1;
        }
        return result;
    }

public:
    void set(const std::string &key, std::string value, int timestamp) { map[key].push_back({timestamp, value}); }

    std::string get(const std::string &key, int timestamp)
    {
        auto it = map.find(key);
        if (it == map.end())
            return "";

        const std::vector<std::pair<int, std::string>> &values = it->second;
        auto [front_timestamp, front_value] = values.front();
        auto [back_timestamp, back_value] = values.back();
        if (timestamp < front_timestamp)
            return "";
        if (timestamp == front_timestamp)
            return front_value;
        if (timestamp >= back_timestamp)
            return back_value;
        return values[binary_search(values, timestamp)].second;
    }
};