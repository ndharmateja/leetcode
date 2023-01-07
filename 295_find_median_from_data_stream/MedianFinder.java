import java.util.Comparator;
import java.util.PriorityQueue;

class MedianFinder {
    PriorityQueue<Integer> minHeap;
    PriorityQueue<Integer> maxHeap;

    public MedianFinder() {
        this.minHeap = new PriorityQueue<>();
        this.maxHeap = new PriorityQueue<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return -(o1 - o2);
            }
        });

    }

    public void addNum(int num) {
        // Add to max heap if it is empty
        if (this.maxHeap.isEmpty()) {
            this.maxHeap.add(num);
            return;
        }

        // Add num to one of the heaps
        if (num <= this.maxHeap.peek())
            this.maxHeap.add(num);
        else
            this.minHeap.add(num);

        // Rebalancing
        if (this.maxHeap.size() - this.minHeap.size() == 2)
            this.minHeap.add(this.maxHeap.poll());
        if (this.minHeap.size() - this.maxHeap.size() == 2)
            this.maxHeap.add(this.minHeap.poll());
    }

    public double findMedian() {
        if (this.maxHeap.size() == this.minHeap.size())
            return (this.maxHeap.peek() + this.minHeap.peek()) / ((double) 2);
        if (this.maxHeap.size() > this.minHeap.size())
            return this.maxHeap.peek();
        return this.minHeap.peek();
    }
}
