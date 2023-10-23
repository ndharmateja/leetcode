package data_structures.a_union_find;

public class WeightedQuickUnionPathCompression implements UnionFind {
    private int[] parent;
    private int[] size;
    private int numSets;

    public WeightedQuickUnionPathCompression(int n) {
        parent = new int[n];
        size = new int[n];
        numSets = n;
        for (int i = 0; i < parent.length; i++) {
            parent[i] = i;
            size[i] = i;
        }
    }

    /**
     * Weighted union based on size of trees
     * This guarantees the height of trees ~log n
     */
    @Override
    public void union(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot)
            return;

        numSets--;
        if (size[pRoot] < size[qRoot]) {
            parent[pRoot] = qRoot;
            size[qRoot] += size[pRoot];
        } else {
            parent[qRoot] = pRoot;
            size[pRoot] += size[qRoot];
        }
    }

    /**
     * Path compression
     * Recursively finds root and also
     * assigns this root as parent to all the nodes
     * along the way
     */
    @Override
    public int find(int p) {
        if (p != parent[p]) {
            parent[p] = find(parent[p]);
        }
        return parent[p];
    }

    @Override
    public int count() {
        return numSets;
    }

    @Override
    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }
}
