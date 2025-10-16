import java.util.ArrayList;
import java.util.List;

public class Subsequences {
    private static void printAllSubsequences(String string, int i, List<Character> sequence) {
        // When we reach the end of the list
        // that is when the sequence is completed
        // So we print it
        if (i == string.length()) {
            System.out.println(sequence);
            return;
        }

        // For each index 'i' we either choose the element
        // at that index or not choose that element
        // That is how we get all the subsequences

        // 1. Choose the element at 'i' and run it on the next index and
        // then remove the added element after the recursive call is done
        sequence.add(string.charAt(i));
        printAllSubsequences(string, i + 1, sequence);
        sequence.remove(sequence.size() - 1);

        // 2. Do not choose the element at 'i' and run it on the next
        // index recursively
        printAllSubsequences(string, i + 1, sequence);
    }

    private static void printAllSubsequences(String string) {
        printAllSubsequences(string, 0, new ArrayList<>());
    }

    private static void printAllSubsequencesWithTargetSum(List<Integer> list, int i, List<Integer> sequence,
            int sequenceSum,
            int targetSum) {
        // When we reach the end of the list
        // that is when the sequence is completed
        // So we print it if the sum of the sequence matches the target
        if (i == list.size()) {
            if (sequenceSum == targetSum)
                System.out.println(sequence);
            return;
        }

        // For each index 'i' we either choose the element
        // at that index or not choose that element
        // That is how we get all the subsequences

        // 1. Choose the element at 'i' and run it on the next index and
        // then remove the added element after the recursive call is done
        sequence.add(list.get(i));
        printAllSubsequencesWithTargetSum(list, i + 1, sequence, sequenceSum + list.get(i), targetSum);
        sequence.remove(sequence.size() - 1);

        // 2. Do not choose the element at 'i' and run it on the next
        // index recursively
        printAllSubsequencesWithTargetSum(list, i + 1, sequence, sequenceSum, targetSum);
    }

    private static void printAllSubsequencesWithTargetSum(List<Integer> list, int targetSum) {
        printAllSubsequencesWithTargetSum(list, 0, new ArrayList<>(), 0, targetSum);
    }

    // => For this function we don't need the list that is tracking the sequence
    // As we are only interested in the target sum and the count of the sequences
    // we only need to keep track of the sequence sum and pass it across
    // the recursive calls
    private static int numSubsequencesWithTargetSum(List<Integer> list, int i, int sequenceSum, int targetSum) {
        // When we reach the end of the list
        // that is when the sequence is completed
        // So we print it if the sum of the sequence matches the target
        if (i == list.size()) {
            if (sequenceSum == targetSum)
                return 1;
            return 0;
        }

        // For each index 'i' we either choose the element
        // at that index or not choose that element
        // That is how we get all the subsequences

        // 1. Choose the element at 'i' and run it on the next index and
        // then remove the added element after the recursive call is done
        int result = 0;
        result += numSubsequencesWithTargetSum(list, i + 1, sequenceSum + list.get(i), targetSum);

        // 2. Do not choose the element at 'i' and run it on the next
        // index recursively
        result += numSubsequencesWithTargetSum(list, i + 1, sequenceSum, targetSum);

        // Return the count of subsequences with a matching target sum
        return result;
    }

    private static int numSubsequencesWithTargetSum(List<Integer> list, int targetSum) {
        return numSubsequencesWithTargetSum(list, 0, 0, targetSum);
    }

    private static boolean printAnySubsequencesWithTargetSum(List<Integer> list, int i, List<Integer> sequence,
            int sequenceSum,
            int targetSum) {
        // When we reach the end of the list
        // that is when the sequence is completed
        // So we print it if the sum of the sequence matches the target
        if (i == list.size()) {
            if (sequenceSum == targetSum) {
                System.out.println(sequence);
                return true;
            }
            return false;
        }

        // For each index 'i' we either choose the element
        // at that index or not choose that element
        // That is how we get all the subsequences

        // 1. Choose the element at 'i' and run it on the next index and
        // then remove the added element after the recursive call is done
        // If a recursive call returns true, it means that a subsequence with
        // a matching target sum has been found
        // So we can simply exit by returning true (propagating the child's true to
        // above recursive calls)
        sequence.add(list.get(i));
        if (printAnySubsequencesWithTargetSum(list, i + 1, sequence, sequenceSum + list.get(i), targetSum))
            return true;
        sequence.remove(sequence.size() - 1);

        // 2. Do not choose the element at 'i' and run it on the next
        // index recursively
        if (printAnySubsequencesWithTargetSum(list, i + 1, sequence, sequenceSum, targetSum))
            return true;

        // If we reached here, it means that no subsequence with a matching target sum
        // has been found
        // So we return false (propagating the child's false to above recursive calls)
        return false;
    }

    private static void printAnySubsequencesWithTargetSum(List<Integer> list, int targetSum) {
        printAnySubsequencesWithTargetSum(list, 0, new ArrayList<>(), 0, targetSum);
    }

    public static void main(String[] args) {
        // Print all subsequences
        System.out.println("All subsequences of ABCD:");
        printAllSubsequences("ABCD");

        // Print all subsequences with sum 12
        List<Integer> list = new ArrayList<Integer>();
        list.add(2);
        list.add(3);
        list.add(3);
        list.add(4);
        list.add(6);
        list.add(7);
        System.out.println("\nAll subsequences of [2, 3, 3, 4, 6, 7] with sum 12:");
        printAllSubsequencesWithTargetSum(list, 12);

        // Count the number of subsequences with sum 12
        System.out.println("\nNumber of subsequences of [2, 3, 3, 4, 6, 7] with sum 12:");
        System.out.println(numSubsequencesWithTargetSum(list, 12));

        // Print any one subsequence with sum 12
        System.out.println("\nAny one subsequence of [2, 3, 3, 4, 6, 7] with sum 12:");
        printAnySubsequencesWithTargetSum(list, 12);

    }
}