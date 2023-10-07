public class Solution323 {
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

    public int countComponents(int n, int[][] edges) {
        // Initialize number of components to the number of vertices
        int numComponents = n;
        DisjointSets sets = new DisjointSets(n);

        // Iterate through all the edges and add them to the disjoint sets
        for (int[] edge : edges) {
            int start = edge[0];
            int end = edge[1];

            // If union is successful, that means
            // two different components got connected
            // so we can decrement the number of components
            if (sets.union(start, end)) {
                numComponents--;
            }
        }

        // return the number of components
        return numComponents;
    }
}
