import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@SuppressWarnings("unused")
class Solution1833 {
    public int maxIceCream(int[] costs, int coins) {
        return solution2(costs, coins);
    }

    // O(n + m) time and O(m) space solution - m is the max cost
    // Counting sort
    // And iterate from left to right of the frequencies array
    private int solution3(int[] costs, int coins) {
        int maxCost = 0;
        for (int cost : costs) {
            if (cost > maxCost)
                maxCost = cost;
        }

        int[] frequencies = new int[maxCost + 1];
        for (int cost : costs) {
            frequencies[cost]++;
        }

        int sum = 0;
        int count = 0;
        for (int i = 0; i < frequencies.length; i++) {
            int frequency = frequencies[i];
            for (int j = 0; j < frequency; j++) {
                if (sum + i > coins) {
                    return count;
                }
                sum += i;
                count++;
            }
        }

        return count;
    }

    // O(n + k log n) time - if the answer is 'k'
    // Heapify the array and run remove min 'k' times
    private int solution2(int[] costs, int coins) {
        Integer[] costsIntegers = new Integer[costs.length];
        for (int i = 0; i < costsIntegers.length; i++) {
            costsIntegers[i] = costs[i];
        }

        MinHeap<Integer> minHeap = new MinHeap<Integer>(costsIntegers);

        int count = 0;
        int sum = 0;
        while (!minHeap.isEmpty()) {
            int currCost = minHeap.extractMin();
            if (sum + currCost > coins) {
                break;
            }
            count++;
            sum += currCost;
        }

        return count;
    }

    // O(n log n) time
    // Sort the array and greedily buy the cheapest ones
    private int solution1(int[] costs, int coins) {
        Arrays.sort(costs);

        int count = 0;
        int sum = 0;
        for (int cost : costs) {
            if (sum + cost > coins) {
                return count;
            }
            sum += cost;
            count++;
        }

        return count;
    }

    static class MinHeap<T extends Comparable<T>> {
        List<T> array;
        int size = 0;

        public MinHeap(T[] array) {
            this.initializeArray(array);
            this.heapify();
        }

        public MinHeap() {
            this.array = new ArrayList<>();
            this.size = 0;
        }

        private void initializeArray(T[] array) {
            int numElements = 0;
            for (T t : array) {
                if (t != null) {
                    numElements++;
                }
            }

            this.array = new ArrayList<>();
            this.size = numElements;

            for (T t : array) {
                if (t != null) {
                    this.array.add(t);
                }
            }
        }

        // O(n) time
        private void heapify() {
            for (int i = this.parent(this.size - 1); i >= 0; i--) {
                this.siftDown(i);
            }
        }

        private int parent(int i) {
            return (i - 1) / 2;
        }

        private int leftChild(int i) {
            return 2 * i + 1;
        }

        private int rightChild(int i) {
            return 2 * i + 2;
        }

        private void siftUp(int i) {
            while (i > 0 && this.array.get(this.parent(i)).compareTo(this.array.get(i)) < 0) {
                this.swap(this.parent(i), i);
                i = this.parent(i);
            }
        }

        private void siftDown(int i) {
            int minIndex = i;

            int l = this.leftChild(i);
            if (l < size && this.array.get(l).compareTo(this.array.get(minIndex)) < 0) {
                minIndex = l;
            }

            int r = this.rightChild(i);
            if (r < size && this.array.get(r).compareTo(this.array.get(minIndex)) < 0) {
                minIndex = r;
            }

            if (i != minIndex) {
                this.swap(i, minIndex);
                this.siftDown(minIndex);
            }
        }

        private void swap(int i, int j) {
            T temp = this.array.get(i);
            this.array.set(i, this.array.get(j));
            this.array.set(j, temp);
        }

        public T extractMin() {
            T result = this.array.get(0);
            this.array.set(0, this.array.get(this.size - 1));
            this.size--;
            this.siftDown(0);
            return result;
        }

        public T getMin() {
            return this.array.get(this.size - 1);
        }

        public void insert(T t) {
            this.array.add(t);
            this.siftUp(this.size);
            this.size++;
        }

        @Override
        public String toString() {
            return this.array.subList(0, this.size).toString();
        }

        public int size() {
            return this.size;
        }

        public boolean isEmpty() {
            return this.size == 0;
        }
    }
}