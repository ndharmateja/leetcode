#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>

class Solution
{
private:
    /**
     * Performs ceiling division of pile / speed
     * Works when speed=1 as well
     *
     * Eg: pile = 7, speed = 2 => (7 + 2 - 1) / 1 = 4 hours
     * Eg: pile = 8, speed = 2 => (8 + 2 - 1) / 1 = 4 hours
     * Eg: pile = 7, speed = 4 => (7 + 4 - 1) / 1 = 2 hours
     * Eg: pile = 8, speed = 4 => (8 + 4 - 1) / 1 = 2 hours
     * Eg: pile = 7, speed = 1 => (7 + 1 - 1) / 1 = 7 hours
     */
    static inline int64_t ceil_division(int pile, int speed) { return (static_cast<int64_t>(pile) + speed - 1) / speed; }

    /**
     * Precondition: speed >= 1
     */
    static bool can_finish(const std::vector<int> &piles, int speed, int num_hours)
    {
        // ! We use int64_t as there could be overflow while calculating the sum
        // ! of all the piles so that we can check at any point if the sum crosses
        // ! the num_hours to return false as num_hours is an integer
        int64_t num_hours_taken{0};
        for (int pile : piles)
        {
            num_hours_taken += ceil_division(pile, speed);
            if (num_hours_taken > num_hours)
                return false;
        }
        return true;
    }

    static int sol1(const std::vector<int> &piles, int num_hours)
    {
        /**
         * Explanation
         * The minimum speed has to be 1 banana per hour
         * The maximum speed (that is useful) is the max number of bananas in a pile
         * among all the piles
         * We can't eat from more than one pile at a time, so having a higher speed
         * won't help
         * Also we are given that num_hours >= number of piles, so eating at max speed (one pile
         * per hour) would finish all the piles in <= num_hours hours
         * So the hi_speed (max pile size) is a valid solution
         * We do binary search in the range of [lo_speed, hi_speed) to find the smallest
         * speed that works (we don't include hi_speed in the binary search as we already
         * record that in the result)
         * We are using candidate variable pattern, we record a valid solution and try to
         * do better until we run out of solutions
         */

        // Edge cases
        // 1. If there is only 1 pile and the #bananas in the pile <= num_hours
        //   then a speed of 1 would be enough
        if (piles.size() == 1 && piles.front() <= num_hours)
            return 1;

        // Init variables for binary search
        auto max_it{std::max_element(piles.begin(), piles.end())};
        int lo_speed{1}, hi_speed{(*max_it) - 1}, mid_speed;
        int result{*max_it};

        // Run binary search as long as lo_speed <= hi_speed
        while (lo_speed <= hi_speed)
        {
            // If the middle speed value works for koko we record it and
            // try to find a better solution by trying to reduce the speed
            mid_speed = lo_speed + (hi_speed - lo_speed) / 2;
            if (can_finish(piles, mid_speed, num_hours))
            {
                result = mid_speed;
                hi_speed = mid_speed - 1;
                continue;
            }

            // If we reach here it means that koko wasn't able to finish the bananas
            // at mid_speed, so we look for the result in the right half
            lo_speed = mid_speed + 1;
        }

        // Return the result
        return result;
    }

public:
    int minEatingSpeed(const std::vector<int> &piles, int num_hours) { return sol1(piles, num_hours); }
};