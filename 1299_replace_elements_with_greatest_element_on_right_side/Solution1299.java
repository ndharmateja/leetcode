class Solution1299 {
    public int[] replaceElements(int[] arr) {
        int currMax = arr[arr.length - 1];
        arr[arr.length - 1] = -1;
        for (int i = arr.length - 2; i >= 0; i--) {
            int val = arr[i];
            arr[i] = currMax;
            if (val > currMax)
                currMax = val;
        }
        return arr;
    }
}