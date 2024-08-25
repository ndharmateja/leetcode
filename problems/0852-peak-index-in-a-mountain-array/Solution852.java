class Solution852 {

    private int peakIndexInMountainArray(int[] arr, int low, int high) {
        if (low == high)
            return low;
        int mid = (low + high) / 2;
        if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) {
            return mid;
        }
        if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1])
            return peakIndexInMountainArray(arr, low, mid);
        return peakIndexInMountainArray(arr, mid, high);

    }

    public int peakIndexInMountainArray(int[] arr) {
        return peakIndexInMountainArray(arr, 0, arr.length - 1);
    }
}