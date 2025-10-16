import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Random;

@SuppressWarnings("unused")
class Solution215 {
    public int findKthLargest(int[] nums, int k) {
        return solution2(nums, k);
    }

    // O(n + k log n) solution
    // Heapify and removeMax k times
    private int solution1(int[] nums, int k) {
        // improvement: heapify and implement our own heap for O(n)
        PriorityQueue<Integer> pq = new PriorityQueue<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return -(o1 - o2);
            }
        });
        for (int num : nums) {
            pq.add(num);
        }
        for (int i = 0; i < k - 1; i++) {
            pq.poll();
        }
        return pq.poll();
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    // improvement: many duplicates => we need to do partitioning differently
    private int quickSelect(int[] nums, int k, int low, int high, Random random) {
        // Select random pivot and swap it with the 'high' index
        // random.nextInt(high - low + 1) generates a random number in
        // [0, high - low + 1) or [0, high - low]
        // random.nextInt(high - low + 1) + low generates a random number in [low, high]
        swap(nums, random.nextInt(high - low + 1) + low, high);

        // Partitioning nums[low, high] - same like quick sort
        int p = low;
        int pivot = nums[high];
        for (int i = low; i < high; i++) {
            if (nums[i] <= pivot) {
                swap(nums, p++, i);
            }
        }
        // because pivot is the last element, it needs to be
        // swapped into its place
        swap(nums, p, high);

        // If the pivot index is equal to the the required index
        // we return the value at the pivot index
        if (p == nums.length - k)
            return nums[p];

        // If pivot index is greater than the required index
        // we need to run quick select on the left half
        if (p > nums.length - k)
            return quickSelect(nums, k, low, p - 1, random);

        // If pivot index is less than the required index
        // we need to run quick select on the right half
        return quickSelect(nums, k, p + 1, high, random);
    }

    // Quick select algorithm
    // O(n) time on average
    // O(n^2) time worst case
    // Works like quick sort and partition and element one half based on 'k'
    private int solution2(int[] nums, int k) {
        return quickSelect(nums, k, 0, nums.length - 1, new Random());
    }

    // O(n log n) solution
    // sort the array and return the kth element from the right
    private int solution3(int[] nums, int k) {
        Arrays.sort(nums);
        return nums[nums.length - k];
    }

    public static void main(String[] args) {
        System.out.println(new Solution215().findKthLargest(new int[] { 1, 2, 3, 5 }, 2));
    }
}