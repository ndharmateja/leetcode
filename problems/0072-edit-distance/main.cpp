#include <string>
#include <vector>
#include <algorithm>

class Solution
{
private:
    /**
     * Bottom up DP solution
     *
     * Theta(mn) time and Theta(mn) space solution
     * where m = len(s1) and n = len(s2)
     */
    static int solution1(const std::string &s1, const std::string &s2)
    {
        // DP solution:
        // say m = len(s1), n = len(s2)
        // dp[i][j]: Edit distance between s1[:i] which is a prefix of s1 of length i
        //           and s2[:j] which is a prefix of s2 of length j (python notation)
        // Base cases: dp[0][j] = j and  dp[i][0] = i as the edit between an empty string and
        //             and a string of length x is x
        // Recurrence relation:
        // dp[i][j] = min{
        //                 dp[i-1][j] + 1,
        //                 dp[i][j-1] + 1,
        //                 dp[i-1][j-1] + (s1[i-1] == s2[j-1] ? 0 : 1)
        //               }
        // Order of filling the table:
        // We fill row by row going from left to right as we need the top value, the left value
        // and the top left values
        // Final answer: dp[m][n]

        // The DP array has to be of size m+1 x n+1
        int m{static_cast<int>(s1.size())}, n{static_cast<int>(s2.size())};
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

        // Base cases
        // Fill the first column with 0s
        for (int i = 0; i <= m; i++)
            dp[i][0] = i;
        // Fill the first row with 0s
        for (int j = 1; j <= n; j++)
            dp[0][j] = j;

        // Fill the DP table row by row from left to right
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = std::min({dp[i - 1][j] + 1,
                                     dp[i][j - 1] + 1,
                                     dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)});

        // Return the answer
        return dp[m][n];
    }

    /**
     * Space optimized bottom up DP. Using a 1xn array (exchange s1 and s2 to keep
     * n as the smaller if necessary). Use a temporary variable to keep of the top left
     * as that would be overwritten as we are using a 1xn array
     *
     * Theta(mn) time and Theta(min{m, n}) space solution
     * where m = len(s1) and n = len(s2)
     */
    static int solution2(const std::string &text1, const std::string &text2)
    {
        // Handle edge cases
        // If one of them is empty, we can return the other string's length
        // This also handles the case of both being empty which returns 0
        if (text1.empty())
            return text2.size();
        if (text2.empty())
            return text1.size();

        // Make sure that n < m to optimize space further
        // so that s2 will always have the smaller string
        // Create references s1 and s2 accordingly
        const std::string &s1 = text1.size() <= text2.size() ? text2 : text1;
        const std::string &s2 = text1.size() <= text2.size() ? text1 : text2;

        // Create the first row with values 0, 1, 2, 3, .., n
        // We use reserve so that it doesn't initialize with 0s
        int m{static_cast<int>(s1.size())}, n{static_cast<int>(s2.size())};
        std::vector<int> dp_row;
        dp_row.reserve(n + 1);
        for (int i = 0; i <= n; i++)
            dp_row.push_back(i);

        // Compute the DP values row by row but overwriting the same vector with the new values
        for (int i = 1; i <= m; i++)
        {
            // The previous top left for (i, j=1) is going to be the value at (i-1,j=0)
            // which is just i-1
            int previous_top_left = i - 1;

            // The value at (i, j=0) is going to be i
            dp_row[0] = i;
            for (int j = 1; j <= n; j++)
            {
                // Store the value at j as the next iteration's top left
                int temp = dp_row[j];

                // DP update
                dp_row[j] = std::min({dp_row[j] + 1,
                                      dp_row[j - 1] + 1,
                                      previous_top_left + (s1[i - 1] == s2[j - 1] ? 0 : 1)});

                // Update the top left value for the next iteration
                previous_top_left = temp;
            }
        }

        // Return the result
        return dp_row[n];
    }

public:
    int minDistance(const std::string &s1, const std::string &s2) { return solution2(s1, s2); }
};