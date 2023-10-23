package data_structures.a_union_find;

public class QuickFind implements UnionFind {
    private int[] id;
    private int numSets;

    public QuickFind(int n) {
        id = new int[n];
        numSets = n;
        for (int i = 0; i < id.length; i++) {
            id[i] = i;
        }
    }

    @Override
    public void union(int p, int q) {
        int pId = id[p];
        int qId = id[q];

        if (pId == qId)
            return;

        numSets--;
        for (int i = 0; i < id.length; i++) {
            if (id[i] == pId)
                id[i] = qId;
        }
    }

    @Override
    public int find(int p) {
        return id[p];
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
