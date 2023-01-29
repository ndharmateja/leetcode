import java.util.ArrayList;
import java.util.List;

public class Solution989 {

    private int[][] balanceArrayLengths(int[] num, int[] num2) {
        int maxLength = Math.max(num.length, num2.length);
        int[][] output = new int[2][maxLength];
        int[] num1Balanced = new int[maxLength];
        int[] num2Balanced = new int[maxLength];

        for (int i = 0; i < num.length; i++) {
            num1Balanced[num1Balanced.length - num.length + i] = num[i];
        }
        for (int i = 0; i < num2.length; i++) {
            num2Balanced[num2Balanced.length - num2.length + i] = num2[i];
        }
        output[0] = num1Balanced;
        output[1] = num2Balanced;

        return output;
    }

    public List<Integer> addToArrayForm(int[] num, int k) {
        int[] num2 = Integer.toString(k).chars().map(c -> c - '0').toArray();

        int[][] balanced = balanceArrayLengths(num, num2);
        int[] num1Balanced = balanced[0];
        int[] num2Balanced = balanced[1];

        int carry = 0;

        List<Integer> output = new ArrayList<>();
        for (int i = 0; i < num1Balanced.length; i++) {
            int digit1 = num1Balanced[num1Balanced.length - i - 1];
            int digit2 = num2Balanced[num2Balanced.length - i - 1];
            int sum = carry + digit1 + digit2;
            System.out.println(sum);
            carry = sum / 10;
            output.add(0, sum % 10);
        }

        if (carry != 0) {
            output.add(0, carry);
        }

        return output;
    }

}