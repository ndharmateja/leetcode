#include <vector>

class Solution
{
private:
    static constexpr int drs[] = {-1, 1, 0, 0};
    static constexpr int dcs[] = {0, 0, -1, 1};

    static int dfs(std::vector<std::vector<int>> &matrix,
                   int r, int c, int m, int n,
                   std::vector<std::vector<int>> &memo,
                   int &max_path_len)
    {
        // If memo contains the answer, it means we have already computed it
        int &result = memo[r][c];
        if (result != -1)
            return result;

        // Base case
        // If this is a source, then its result is 1
        result = 1;

        int max_neighbour_len{0};
        for (int i = 0; i < 4; i++)
        {
            int new_r = r + drs[i];
            int new_c = c + dcs[i];

            if (new_r < 0 || new_r >= m || new_c < 0 || new_c >= n)
                continue;

            if (matrix[new_r][new_c] < matrix[r][c])
                max_neighbour_len = std::max(max_neighbour_len, dfs(matrix, new_r, new_c, m, n, memo, max_path_len));
        }

        result += max_neighbour_len;
        max_path_len = std::max(max_path_len, result);
        return result;
    }
    
    static int sol1(std::vector<std::vector<int>> &matrix)
    {
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
        int max_path_len{0};
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                dfs(matrix, r, c, m, n, memo, max_path_len);
        return max_path_len;
    }

    static void dfs2(std::vector<std::vector<int>> &matrix,
                     int r, int c, int m, int n,
                     std::vector<std::vector<int>> &memo,
                     int &max_path_len)
    {
        // Base case
        // If this is a source, then its result is 1
        int &result = memo[r][c];
        result = 1;

        int max_neighbour_len{0};
        for (int i = 0; i < 4; i++)
        {
            int new_r = r + drs[i];
            int new_c = c + dcs[i];

            if (new_r < 0 || new_r >= m || new_c < 0 || new_c >= n)
                continue;

            if (matrix[new_r][new_c] < matrix[r][c])
            {
                if (memo[new_r][new_c] == -1)
                    dfs2(matrix, new_r, new_c, m, n, memo, max_path_len);
                max_neighbour_len = std::max(max_neighbour_len, memo[new_r][new_c]);
            }
        }

        result += max_neighbour_len;
        max_path_len = std::max(max_path_len, result);
    }

    static int sol2(std::vector<std::vector<int>> &matrix)
    {
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
        int max_path_len{0};
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                if (memo[r][c] == -1)
                    dfs2(matrix, r, c, m, n, memo, max_path_len);
        return max_path_len;
    }

public:
    int longestIncreasingPath(std::vector<std::vector<int>> &matrix) { return sol2(matrix); }
};