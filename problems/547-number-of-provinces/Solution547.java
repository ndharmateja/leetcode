import java.util.HashSet;
import java.util.Set;

@SuppressWarnings("unused")
public class Solution547 {
    private class DisjointSets {
        private int[] parent;
        private int[] rank;

        public DisjointSets(int n) {
            this.parent = new int[n];
            this.rank = new int[n];
            for (int i = 0; i < n; i++) {
                this.makeSet(i);
            }
        }

        private void makeSet(int i) {
            this.parent[i] = i;
            this.rank[0] = 0;
        }

        private int find(int i) {
            // Without path compression
            // while (i != parent[i]) {
            // i = parent[i];
            // }
            // return i;

            // Using path compression
            if (i != parent[i]) {
                parent[i] = find(parent[i]);
            }
            return parent[i];
        }

        /*
         * unions sets which contain i and j
         * 
         * @return true if i and j were in different sets, false otherwise
         */
        public boolean union(int i, int j) {
            // Get ids of both elements
            int iId = find(i);
            int jId = find(j);

            // If ids of both elements are the same
            // return false
            if (iId == jId)
                return false;

            // Union by rank
            // Attach the smaller tree to the bigger tree
            if (rank[iId] > rank[jId]) {
                parent[jId] = iId;
            } else if (rank[iId] < rank[jId]) {
                parent[iId] = jId;
            } else {
                // If rank of both is same
                // then attach iId's tree to jId
                parent[iId] = jId;
                rank[jId] += 1;
            }

            return true;
        }
    }

    // Using disjoint sets
    private int solution1(int[][] isConnected) {
        // Initialize number of components to the number of vertices
        int numComponents = isConnected.length;
        DisjointSets sets = new DisjointSets(numComponents);

        // Iterate through all the edges and add them to the disjoint sets
        for (int i = 0; i < isConnected.length; i++) {
            for (int j = 0; j < isConnected.length; j++) {
                if (i == j)
                    continue;

                // If union is successful, that means
                // two different components got connected
                // so we can decrement the number of components
                if (isConnected[i][j] == 1 && sets.union(i, j)) {
                    numComponents--;
                }
            }
        }

        // return the number of components
        return numComponents;

    }

    // Using dfs
    private int solution2(int[][] isConnected) {
        int numComponents = 0;
        Set<Integer> visited = new HashSet<>();
        for (int v = 0; v < isConnected.length; v++) {
            if (!visited.contains(v)) {
                // Explores a complete component
                dfs(v, isConnected, visited);
                numComponents++;
            }
        }

        return numComponents;
    }

    private void dfs(int v, int[][] isConnected, Set<Integer> visited) {
        // Add vertex to visited
        visited.add(v);

        // Run dfs on each of its unvisited neighbours
        for (int i = 0; i < isConnected[v].length; i++) {
            boolean isNeighbour = v != i && isConnected[v][i] == 1;
            if (isNeighbour && !visited.contains(i)) {
                dfs(i, isConnected, visited);
            }
        }
    }

    public int findCircleNum(int[][] isConnected) {
        return solution2(isConnected);
    }
}
