import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Random;

@SuppressWarnings("unused")
class Solution {
    public int findKthLargest(int[] nums, int k) {
        return solution1(nums, k);
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

    // O(n log n) solution
    // sort the array and return the kth element from the right
    private int solution3(int[] nums, int k) {
        Arrays.sort(nums);
        return nums[nums.length - k];
    }
}