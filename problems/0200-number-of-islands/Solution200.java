import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;
import java.util.Stack;

@SuppressWarnings("unused")
public class Solution200 {
    public int numIslands(char[][] grid) {
        // Island count
        int islandCount = 0;

        // Run the explorative search algo on each
        // of the unvisited cells (we make a cell visited by
        // marking it with '0')
        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < grid[0].length; c++) {
                if (grid[r][c] == '1') {
                    dfs(r, c, grid);
                    // dfsIterative(getGridIndex(r, c, grid[0].length), grid);
                    // bfs(getGridIndex(r, c, grid[0].length), grid);
                    islandCount++;
                }
            }
        }

        return islandCount;
    }

    // Recursive DFS
    private void dfs(int r, int c, char[][] grid) {
        // Mark r, c as visited (by setting it to '0')
        grid[r][c] = '0';

        // recursively run dfs on the 4 neighbours (if unvisited and valid)
        // left, right, up, down
        if (r - 1 >= 0 && grid[r - 1][c] == '1')
            dfs(r - 1, c, grid);
        if (r + 1 <= grid.length - 1 && grid[r + 1][c] == '1')
            dfs(r + 1, c, grid);
        if (c - 1 >= 0 && grid[r][c - 1] == '1')
            dfs(r, c - 1, grid);
        if (c + 1 <= grid[0].length - 1 && grid[r][c + 1] == '1')
            dfs(r, c + 1, grid);
    }

    private int getGridIndex(int r, int c, int numCols) {
        return r * numCols + c;
    }

    // Iterative DFS
    private void dfsIterative(int v, char[][] grid) {
        int numRows = grid.length;
        int numCols = grid[0].length;

        Stack<Integer> stack = new Stack<>();
        stack.push(v);

        int vRow = v / numCols;
        int vCol = v % numCols;
        grid[vRow][vCol] = '0';

        while (!stack.isEmpty()) {
            int curr = stack.pop();

            int r = curr / numCols;
            int c = curr % numCols;

            int left = getGridIndex(r - 1, c, numCols);
            int right = getGridIndex(r + 1, c, numCols);
            int up = getGridIndex(r, c - 1, numCols);
            int down = getGridIndex(r, c + 1, numCols);
            if (r - 1 >= 0 && grid[r - 1][c] == '1') {
                stack.push(left);
                grid[r - 1][c] = '0';
            }
            if (r + 1 <= numRows - 1 && grid[r + 1][c] == '1') {
                stack.push(right);
                grid[r + 1][c] = '0';
            }
            if (c - 1 >= 0 && grid[r][c - 1] == '1') {
                stack.push(up);
                grid[r][c - 1] = '0';
            }
            if (c + 1 <= numCols - 1 && grid[r][c + 1] == '1') {
                stack.push(down);
                grid[r][c + 1] = '0';
            }
        }
    }

    // Iterative BFS
    private void bfs(int v, char[][] grid) {
        int numRows = grid.length;
        int numCols = grid[0].length;

        Queue<Integer> queue = new LinkedList<>();
        queue.add(v);

        int vRow = v / numCols;
        int vCol = v % numCols;
        grid[vRow][vCol] = '0';

        while (!queue.isEmpty()) {
            int curr = queue.poll();

            int r = curr / numCols;
            int c = curr % numCols;

            int left = getGridIndex(r - 1, c, numCols);
            int right = getGridIndex(r + 1, c, numCols);
            int up = getGridIndex(r, c - 1, numCols);
            int down = getGridIndex(r, c + 1, numCols);
            if (r - 1 >= 0 && grid[r - 1][c] == '1') {
                queue.add(left);
                grid[r - 1][c] = '0';
            }
            if (r + 1 <= numRows - 1 && grid[r + 1][c] == '1') {
                queue.add(right);
                grid[r + 1][c] = '0';
            }
            if (c - 1 >= 0 && grid[r][c - 1] == '1') {
                queue.add(up);
                grid[r][c - 1] = '0';
            }
            if (c + 1 <= numCols - 1 && grid[r][c + 1] == '1') {
                queue.add(down);
                grid[r][c + 1] = '0';
            }
        }
    }

}
