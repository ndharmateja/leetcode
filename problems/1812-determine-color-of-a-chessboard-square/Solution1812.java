class Solution1812 {
    public boolean squareIsWhite(String coordinates) {
        // Convert to zero index 2D array coordinates
        int row = 8 - coordinates.charAt(1);
        int col = coordinates.charAt(0) - 'a';

        // It is white if both row and col are even or
        // if both are odd
        return (row % 2 == 0 && col % 2 == 0) || (row % 2 != 0 && col % 2 != 0);
    }
}