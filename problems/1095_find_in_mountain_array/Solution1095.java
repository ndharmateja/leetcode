public class Solution1095 {
    interface MountainArray {
        public int get(int index);

        public int length();
    }

    static class MyMountainArray implements MountainArray {
        private int[] array;

        public MyMountainArray(int[] array) {
            this.array = array;
        }

        @Override
        public int get(int index) {
            return this.array[index];
        }

        @Override
        public int length() {
            return this.array.length;
        }
    }

    private static int binarySearchMaxIndex(MountainArray a, int lo, int hi) {
        if (lo > hi)
            return -1;
        int mid = (lo + hi) / 2;

        // If a[mid-1], a[mid] and a[mid+1] are in decreasing order, go right and vice
        // versa
        if (a.get(mid - 1) > a.get(mid) && a.get(mid) > a.get(mid + 1))
            return binarySearchMaxIndex(a, lo, mid - 1);
        if (a.get(mid - 1) < a.get(mid) && a.get(mid) < a.get(mid + 1))
            return binarySearchMaxIndex(a, mid + 1, hi);

        return mid;
    }

    private static int binarySearchAscending(MountainArray a, int lo, int hi, int target) {
        if (lo > hi)
            return -1;
        int mid = (lo + hi) / 2;
        if (a.get(mid) > target)
            return binarySearchAscending(a, lo, mid - 1, target);
        if (a.get(mid) < target)
            return binarySearchAscending(a, mid + 1, hi, target);

        return mid;
    }

    private static int binarySearchDescending(MountainArray a, int lo, int hi, int target) {
        if (lo > hi)
            return -1;
        int mid = (lo + hi) / 2;
        if (a.get(mid) < target)
            return binarySearchDescending(a, lo, mid - 1, target);
        if (a.get(mid) > target)
            return binarySearchDescending(a, mid + 1, hi, target);

        return mid;
    }

    public int findInMountainArray(int target, MountainArray a) {
        int n = a.length();

        // Find the index of the peak
        // peak can only exist in [1, n-2]
        int maxIndex = binarySearchMaxIndex(a, 1, n - 2);
        if (a.get(maxIndex) == target)
            return maxIndex;

        // Search the increasing part => in [0, maxIndex - 1]
        int ascIndex = binarySearchAscending(a, 0, maxIndex - 1, target);
        if (ascIndex != -1)
            return ascIndex;

        // Search the decreasing part => in [maxIndex + 1, n - 1]
        int descIndex = binarySearchDescending(a, maxIndex + 1, n - 1, target);
        if (descIndex != 1)
            return descIndex;

        // If not found anywhere return -1
        return -1;
    }

    public static void main(String[] args) {
        MountainArray a = new MyMountainArray(new int[] { 3, 5, 3, 2, 0 });
        System.out.println(new Solution1095().findInMountainArray(3, a));
    }
}