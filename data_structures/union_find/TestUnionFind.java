package data_structures.union_find;

import data_structures.testing.TestUtils;

public class TestUnionFind {
    private static void testUnionFind(UnionFind uf, int n) {
        TestUtils.doAssertion(uf.count() == n);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                TestUtils.doAssertion(!uf.connected(i, j));
            }
        }

        for (int i = 1; i < n; i++) {
            TestUtils.doAssertion(!uf.connected(i, i - 1));
            TestUtils.doAssertion(!uf.connected(i, 0));
            uf.union(i, i - 1);
            TestUtils.doAssertion(uf.connected(i, 0));
            TestUtils.doAssertion(uf.connected(i, 0));
            TestUtils.doAssertion(uf.count() == n - i);
        }

        TestUtils.doAssertion(uf.count() == 1);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                TestUtils.doAssertion(uf.connected(i, j));
            }
        }
    }

    public static void main(String[] args) {
        int n = 100;
        testUnionFind(new QuickFind(n), n);
        System.out.println("Testing QuickFind complete");
        testUnionFind(new WeightedQuickUnion(n), n);
        System.out.println("Testing WeightedQuickUnion complete");
        testUnionFind(new WeightedQuickUnionPathCompression(n), n);
        System.out.println("Testing WeightedQuickUnionPathCompression complete");
    }
}
