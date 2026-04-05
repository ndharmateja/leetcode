#include <vector>

class Solution
{
public:
    /**
     * Lemma 1: ((a or b) => c) => (a => c)
     * Lemma 2: ((a => b) and (a => c)) => (a => (b and c))
     *
     * Invariant: Whenever we move the pointer with the smaller height inward,
     * we are not missing out on a better solution.
     * Define A[L, R] := Area of water between indices L and R = min(hL, hR) * (R - L)
     *
     * case 1: consider the range [L, R] where hL <= hR
     * claim: for any i in (L, R), A[L, i] < A[L, R]
     * proof:
     * A[L, R] = min(hL, hR) * (R - L) = hL * (R - L) as hL <= hR
     * A[L, i] = min(hL, hi) * (i - L)
     *      case 1a: if hL <= hi, then min(hL, hi) = hL => A[L, i] = hL * (i - L) < A[L, R]
     *      as (i - L) < (R - L)
     *      case 1b: if hL > hi, then min(hL, hi) = hi => A[L, i] = hi * (i - L) < A[L, R]
     *      as hi < hL and (i - L) < (R - L)
     *
     *
     * so, (hL <= hR) => (A[L, i] < A[L, R]) for any i in (L, R)
     * so, (hL == hR or hL < hR) => (A[L, i] < A[L, R]) for any i in (L, R) => we can move the smaller ptr
     * so, (hL == hR) => (A[L, i] < A[L, R]) for any i in (L, R) by lemma 1
     * so by symmetrical argument, (hL == hR) => (A[j, R] < A[L, R]) for any j in (L, R)
     * so, (hL == hR) => (A[L, i] < A[L, R]) for any i in (L, R)) and (A[j, R] < A[L, R]) for any j in (L, R)
     * by lemma 2
     *
     * so essentially, not only can we move the smaller pointer, but we can move both pointers
     * inward if the heights are equal. That is because we initially know that the optimal solution
     * exists in the [0, n-1] range and we are never missing out on a better solution by our moves.
     * And we exhaust our space by the end (derived variable([L, R]) = R - L which is a decreasing
     * natural valued function => the state machine has to terminate), so we must have captured the
     * solution along the way.
     */
    int maxArea(std::vector<int> &heights)
    {
        // Init variables
        int n{static_cast<int>(heights.size())};
        int l{0}, r{n - 1};
        int max_area{0};

        while (l < r)
        {
            // At every range, see if the current area is better than the current solution
            // Note: the current two lines of code is faster than the line below on leetcode
            // max_area = std::max(max_area, (r - l) * std::min(heights[l], heights[r]));
            int h = heights[l] <= heights[r] ? heights[l] : heights[r];
            max_area = std::max(max_area, (r - l) * h);

            // If the left height is smaller, move the lower pointer inward
            if (heights[l] < heights[r])
                l++;

            // If the right height is smaller, move the higher pointer inward
            else if (heights[r] < heights[l])
                r--;

            // If the heights are equal, move both pointers inward
            else
            {
                l++;
                r--;
            }
        }
        return max_area;
    }
};