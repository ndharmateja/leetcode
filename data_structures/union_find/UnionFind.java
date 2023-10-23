package data_structures.union_find;

public interface UnionFind {

    public abstract void union(int p, int q);

    public abstract int find(int p);

    public int count();

    public boolean connected(int p, int q);
}
