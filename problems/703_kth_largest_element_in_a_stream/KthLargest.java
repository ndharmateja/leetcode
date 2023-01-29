import java.util.PriorityQueue;

class KthLargest {
    int k;
    PriorityQueue<Integer> pq;

    public KthLargest(int k, int[] nums) {
        this.k = k;
        this.pq = new PriorityQueue<>();
        for (int num : nums) {
            this.add(num);
        }
    }

    // Use min-heap to store atmost 'k' values
    // those will be the top 'k' values
    // at any instant
    public int add(int val) {
        if (this.pq.size() == this.k) {
            // If queue is full and the val
            // is smaller than the smallest
            // we don't add it to the queue
            if (val <= this.pq.peek())
                return pq.peek();

            // If not we remove the smallest
            // element to add this val
            // to the queue
            else
                this.pq.remove();
        }

        // Add the val and return the smallest value
        pq.add(val);
        return pq.peek();
    }
}