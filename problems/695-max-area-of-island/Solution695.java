public class Solution695 {
    public int maxAreaOfIsland(int[][] grid) {
        // Island count
        int maxIslandSize = 0;

        // Run the explorative search algo on each
        // of the unvisited cells (we make a cell visited by
        // marking it with 0)
        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < grid[0].length; c++) {
                if (grid[r][c] == 1) {
                    int islandSize = dfs(r, c, grid);
                    if (islandSize > maxIslandSize)
                        maxIslandSize = islandSize;
                }
            }
        }

        return maxIslandSize;
    }

    // Recursive DFS
    // Returns the number of vertices it explored
    private int dfs(int r, int c, int[][] grid) {
        // Mark r, c as visited (by setting it to 0)
        grid[r][c] = 0;

        // Initialize island count to 1
        // (counting the current one)
        int islandCount = 1;

        // recursively run dfs on the 4 neighbours (if unvisited and valid)
        // left, right, up, down and increment each of its counts to island count
        if (r - 1 >= 0 && grid[r - 1][c] == 1)
            islandCount += dfs(r - 1, c, grid);
        if (r + 1 <= grid.length - 1 && grid[r + 1][c] == 1)
            islandCount += dfs(r + 1, c, grid);
        if (c - 1 >= 0 && grid[r][c - 1] == 1)
            islandCount += dfs(r, c - 1, grid);
        if (c + 1 <= grid[0].length - 1 && grid[r][c + 1] == 1)
            islandCount += dfs(r, c + 1, grid);

        // return island count
        return islandCount;
    }
}
