public class Solution684 {
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
         * returns true if i and j were in different sets
         * returns false otherwise
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

    public int[] findRedundantConnection(int[][] edges) {
        DisjointSets sets = new DisjointSets(edges.length);
        for (int[] edge : edges) {
            // convert 1 based vertices to 0 based
            // as we have intialized disjoint sets with #vertices
            int start = edge[0] - 1;
            int end = edge[1] - 1;

            // If the start and end vertices are present in a single set
            // adding this edge will form a cycle
            // so we return this edge (in 1 based - given format)
            if (!sets.union(start, end))
                return edge;
        }

        // We won't reach here
        return null;
    }
}
