package data_structures.a_union_find;

public class WeightedQuickUnion implements UnionFind {
    private int[] parent;
    private int[] size;
    private int numSets;

    public WeightedQuickUnion(int n) {
        parent = new int[n];
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

        if (size[pRoot] < size[qRoot]) {
            parent[pRoot] = qRoot;
            size[qRoot] += size[pRoot];
        } else {
            parent[qRoot] = pRoot;
            size[pRoot] += size[qRoot];
        }
    }

    @Override
    public int find(int p) {
        while (p != parent[p]) {
            p = parent[p];
        }
        return p;
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
