@SuppressWarnings("unused")
class Solution74 {
    // Binary search on the first elements of the rows
    // of the matrix
    // We find a row such that the target is greater than
    // or equal to the first element of the row and smaller
    // than the first element of the next row
    // If the element is smaller than the first
    private int getRowIndex(int[][] matrix, int target) {
        int low = 0;
        int high = matrix.length - 1;

        if (target < matrix[low][0])
            return -1;
        if (target >= matrix[high][0])
            return high;

        while (low <= high) {
            if (high - low == 1) {
                return low;
            }

            int mid = (low + high) / 2;
            if (matrix[mid][0] == target) {
                return mid;
            } else if (matrix[mid][0] > target) {
                high = mid;
            } else {
                low = mid;
            }
        }

        return low;
    }

    // Recursive binary search function
    // that tells us whether 'target' exists in our
    // 'nums' array
    private boolean search(int[] nums, int target, int low, int high) {
        if (low > high)
            return false;
        int mid = (low + high) / 2;
        if (nums[mid] == target)
            return true;
        if (nums[mid] < target)
            return search(nums, target, mid + 1, high);
        return search(nums, target, low, mid - 1);
    }

    // O(log(nRows) + log(nCols)) time and O(1) space solution
    // We do a double binary search to first find
    // the row and then find if the element exists in the row
    private boolean solution1(int[][] matrix, int target) {
        // Get row index of the element
        int rowIndex = getRowIndex(matrix, target);
        if (rowIndex == -1) {
            return false;
        }

        // Find if element exists in the row
        int[] row = matrix[rowIndex];
        return search(row, target, 0, row.length - 1);
    }

    // Gets the element at the 'index' index
    // in the flattened matrix
    // The flattened indices look like this
    // [
    // [0, 1, 2, 3],
    // [4, 5, 6, 7]
    // ]
    private int getElement(int[][] matrix, int index) {
        int nRows = matrix.length;
        int nCols = matrix[0].length;
        int row = index / nCols;
        int col = index % nCols;
        return matrix[row][col];
    }

    // O(log(nRows * nCols)) time and O(1) space solution
    // Does a binary search on the flattened 2D array
    private boolean search2D(int[][] nums, int target, int low, int high) {
        if (low > high)
            return false;
        int mid = (low + high) / 2;
        if (getElement(nums, mid) == target)
            return true;
        if (getElement(nums, mid) < target)
            return search2D(nums, target, mid + 1, high);
        return search2D(nums, target, low, mid - 1);
    }

    private boolean solution2(int[][] matrix, int target) {
        int nRows = matrix.length;
        int nCols = matrix[0].length;
        return search2D(matrix, target, 0, nRows * nCols - 1);
    }

    public boolean searchMatrix(int[][] matrix, int target) {
        return solution2(matrix, target);
    }
}