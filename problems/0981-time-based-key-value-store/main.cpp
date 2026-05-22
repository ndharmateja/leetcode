#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

class TimeMap
{
private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> map;

    /**
     * Binary search to find the index of the element whose timestamp is the largest
     * that is <= to the given timestamp using the candidate variable pattern
     *
     * Assumes that
     * All values in the vector have unique timestamps in ascending order
     * timestamp > values.front().first
     * timestamp < values.back().first
     * So we can infer that there are atleast 3 elements in the values vector
     */
    static int binary_search(const std::vector<std::pair<int, std::string>> &values, int timestamp)
    {
        // 0 is a valid answer, so we can start with it and try to improve it using binary search
        int n{static_cast<int>(values.size())}, lo{0}, hi{n - 1}, mid;
        int result{0};

        // As long as the range is valid, we run binary search
        while (lo <= hi)
        {
            // If the middle element's timestamp matches the given timestamp
            // we can directly return it as we have unique timestamp values
            // and we found the matching timestamp
            mid = lo + (hi - lo) / 2;
            int mid_timestamp{values[mid].first};
            if (mid_timestamp == timestamp)
                return mid;

            // If the middle element's timestamp is smaller than the given timestamp
            // it means we found a better solution
            // So we record it and try to make it better
            if (mid_timestamp < timestamp)
            {
                result = mid;
                lo = mid + 1;
            }

            // If it is not a potential solution, it means we have strayed too far
            // to the right and we need to look in the left half
            else
                hi = mid - 1;
        }

        // Return the answer
        return result;
    }

public:
    void set(const std::string &key, std::string value, int timestamp) { map[key].push_back({timestamp, value}); }

    std::string get(const std::string &key, int timestamp)
    {
        // If the key isn't already there (we use the find() method to get away with one hash)
        // we can return the empty string
        auto it = map.find(key);
        if (it == map.end())
            return "";

        // Get the corresponding vector of pairs for the given key
        const std::vector<std::pair<int, std::string>> &values = it->second;

        // Get the timestamp and the values for the first element
        auto [front_timestamp, front_value] = values.front();

        // If the timestamp is lower than the lowest timestamp (the values are ordered by
        // ascending order of timestamps) then we don't have a timestamp that is <= the
        // given timestamp, so we can return ""
        if (timestamp < front_timestamp)
            return "";

        // ! If a timestamp in our values matches the given timestamp
        // ! we can return it immediately as all the timestamps for a certain key are
        // ! unique and the largest timestamp that is <= the given timestamp will
        // ! be the matching timestamp itself
        // Since all the timestamps for a certain key are unique
        // If the given timestamp is equal to the first value's timestamp
        // we can return its value
        if (timestamp == front_timestamp)
            return front_value;

        // Get the timestamp and the values for the last element
        auto [back_timestamp, back_value] = values.back();

        // If the given timestamp either matches the last element's timestamp
        // or if it is greater then the last element is the element with
        // the largest timestamp <= to the given timestamp
        // So we can return the last element's value
        if (timestamp >= back_timestamp)
            return back_value;

        // Find the index of the element whose timestamp is the largest value
        // that is <= to the given timestamp and return its value
        const std::string &result = values[binary_search(values, timestamp)].second;
        return result;
    }
};