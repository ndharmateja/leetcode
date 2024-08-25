class Solution832 {
    private static void reverse(int[] array) {
        for (int i = 0; i < array.length / 2; i++) {
            int temp = array[i];
            array[i] = array[array.length - i - 1];
            array[array.length - i - 1] = temp;
        }
    }

    private static void invert(int[] array) {
        for (int i = 0; i < array.length; i++)
            array[i] = 1 - array[i];
    }

    public int[][] flipAndInvertImage(int[][] image) {
        for (int[] row : image) {
            reverse(row);
            invert(row);
        }
        return image;
    }
}