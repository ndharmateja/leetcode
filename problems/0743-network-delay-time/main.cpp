#include <vector>
#include <algorithm>
#include <limits>

// Reference: https://github.com/ndharmateja/data-structures-cpp/blob/master/data-structures/priority-queues/index-min-pq/index_min_pq.hpp
// Removing type checking and error handling for leet code
// For more details and full code visit the above link
template <typename T>
class IndexMinPQ
{
private:
    // Instance variables
    // pq[i]   => i is the heap index and pq[i] is the user specified index
    // Essentially pq is the heap array where in each index we are storing the
    // user index of the element instead of the actual element itself.
    //
    // qp[i]   => i is the user specified index and qp[i] is the heap index
    //            qp[i] is -1 if user didn't associate i with any element
    // keys[i] => i is the user specified index and keys[i] is the actual element
    // qp and keys are parallel arrays where i is the user specified index
    //     qp[i] holds the heap index and
    //     keys[i] holds the corresponding item
    //
    // Note that if the element at a user index i was removed from the pq, keys[i] need
    // not necessarily be empty. Since qp[i] is going to be -1 keys[i] is going to be
    // irrelevant.
    std::vector<int> qp;
    std::vector<T> keys;
    std::vector<int> pq;
    int n;
    int max_n;

    // Helper methods
    void swap(int i, int j)
    {
        // Swap elements at heap indices i and j
        std::swap(pq[i], pq[j]);

        // When we swap elements at heap indices i and j
        // we also need to swap indices pq[i] and pq[j] in the qp array
        // as the heap indices corresponding to the user indices have been changed
        int user_index_i{pq[i]}, user_index_j{pq[j]};
        std::swap(qp[user_index_i], qp[user_index_j]);
    }

    /**
     * This method returns a reference to the element and not a copy
     */
    const T &element_at(int heap_index) const
    {
        // The actual element for heap index i is keys[pq[i]]
        // pq[i] is the user index of the element at heap index i
        // and keys[pq[i]] is the actual element
        return keys[pq[heap_index]];
    }

    void swim(int i)
    {
        // i and p are the heap indices
        while (i > 0)
        {
            // We need to keep swapping as long as the parent > child
            int p = parent(i);

            // If element_at(p) <= element_at(i), we can break
            // (element_at(p) <= element_at(i)) <=> !(element_at(p) > element_at(i)) <=> !(element_at(i) < element_at(p))
            if (!(element_at(i) < element_at(p)))
                break;

            // Swap i with parent and update i
            swap(i, p);
            i = p;
        }
    }

    void sink(int i)
    {
        // Run the loop as long as there is a left child
        int to_swap;
        while ((to_swap = left_child(i)) < n)
        {
            // If the right child also exists and the right child element
            // is smaller than the left child, then we need to swap ith element
            // with right child, so we increment to_swap index
            if (to_swap < n - 1 && element_at(to_swap + 1) < element_at(to_swap))
                to_swap++;

            // If the element at i less than or equal than the smaller child
            // then we don't need to swap
            // (element_at(i) <= element_at(to_swap)) <=> !(element_at(i) > element_at(to_swap)) <=> !(element_at(to_swap) < element_at(i))
            if (!(element_at(to_swap) < element_at(i)))
                break;

            // Swap with the smaller child and update i
            swap(i, to_swap);
            i = to_swap;
        }
    }

    static int parent(int i) { return (i - 1) / 2; }
    static int left_child(int i) { return 2 * i + 1; };
    static int right_child(int i) { return 2 * i + 2; };

public:
    // Initialize (not reserve) the vectors with the given max_n
    IndexMinPQ(int max_n) : qp(max_n, -1), keys(max_n), pq(max_n), n{0}, max_n{max_n} {}

    void insert(int k, T key)
    {
        // Insert the item at the end and swim
        qp[k] = n;
        keys[k] = key;
        pq[n] = k;
        n++;
        swim(n - 1);
    }

    void change(int k, T key)
    {
        // Change the item associated with index 'k'
        T old_key = keys[k];
        keys[k] = key;

        // swim/sink appropriately based on whether the value increased or decreased
        // If value is decreased, then we only potentially need to swim as heap property
        // is potentially violated with the parent
        // Similarly we potentially need to sink otherwise
        int heap_index = qp[k];
        if (key < old_key)
            swim(heap_index);
        else
            sink(heap_index);
    }

    bool contains(int k) const { return qp[k] != -1; }

    void remove(int k)
    {
        // Get the index of the element in the heap
        int heap_index = qp[k];

        // Optimization: If the heap index itself is n-1, then we are deleting the
        // last node in the heap in which case no swimming or swapping needed
        if (heap_index == n - 1)
        {
            n--;
            qp[k] = -1;
            return;
        }

        // Get the keys that are being swapped
        // ! Get them before changing 'n' and swap
        // ! Make sure to type the variables as const T&, otherwise a copy construtor will be triggered
        const T &removed_key = element_at(heap_index);
        const T &last_element_key = element_at(n - 1);

        // Swap the element with the last element, decrement the n
        // and remove the given index 'k' from qp
        swap(heap_index, --n);
        qp[k] = -1;

        // ! The element we removed might be smaller or larger than the last element
        // So we swim or sink the index based on the value
        if (last_element_key < removed_key)
            swim(heap_index);
        else
            sink(heap_index);
    }

    T min() const { return element_at(0); }

    int min_index() const { return pq.front(); }

    int remove_min()
    {
        // Get the user index of the minimal element and remove it
        int user_index = pq[0];
        remove(user_index);
        return user_index;
    }

    bool empty() const { return !n; }
    int size() const { return n; }
};

class Solution
{
private:
    inline static const int POS_INF = std::numeric_limits<int>::max();

    /**
     * Dijkstra's Algorithm
     */
    static int solution1(const std::vector<std::vector<int>> &edges, int n, int s)
    {
        // Construct the adjacency list from the edge list
        // Note that the indices of the vertices are 1-indexed and belong to [1, num_vertices]
        std::vector<std::vector<std::pair<int, int>>> adj_list(n);
        for (const std::vector<int> &edge : edges)
        {
            // Unpack the edge and also convert it to 0-indexing
            int from = edge[0] - 1;
            int to = edge[1] - 1;
            int wt = edge[2];
            adj_list[from].push_back({to, wt});
        }

        // so we also convert them to 0-indexed while constructing the adjacency list
        // So s also has to be decreased by to convert it to 0-indexed
        s--;

        // Data structures for Dijkstra's
        // dist_to[] keeps track of the distance from the source
        // We don't need the prev pointers as we are not reconstructing the shortest path
        std::vector<int> dist_to(n, POS_INF);

        // IndexMinPQ is a priority queue that contains the distances
        // We use IndexMinPQ as each node gets only stored once in the PQ thereby
        // avoiding multiple copies of the same node. Max of n items are stored in the PQ
        // at any point of time.
        IndexMinPQ<int> pq{n};

        // Update source's distance and add it to the pq
        dist_to[s] = 0;
        pq.insert(s, 0);

        // Main Dijkstra's loop
        while (!pq.empty())
        {
            // Remove the shortest node and relax all its neighbours
            int u = pq.remove_min();

            // Relax all its neighbours
            for (auto [v, wt] : adj_list[u])
            {
                // We don't have to worry about relaxing nodes for which the shortest distance
                // was already finalized as the new_dist will be not less than the shortest dist
                // so it won't go inside the if condition.
                int new_dist = dist_to[u] + wt;
                if (new_dist < dist_to[v])
                {
                    // Update the distance and parent pointer of v
                    dist_to[v] = new_dist;

                    // Insert/Update v's distance into the priority queue
                    if (pq.contains(v))
                        pq.change(v, new_dist);
                    else
                        pq.insert(v, new_dist);
                }
            }
        }

        // We need the min time that it takes for all the n nodes to receive the signal
        // which is the longest among all the shortest path distances
        // If any of the distances are positive infinity, it means that that particular node
        // isn't reachable, so we can immediately return -1
        int max_dist = 0;
        for (int dist : dist_to)
        {
            if (dist == POS_INF)
                return -1;
            max_dist = dist > max_dist ? dist : max_dist;
        }

        // Return the max dist (if we reached here it means that all nodes were reachable)
        return max_dist;
    }

public:
    int networkDelayTime(const std::vector<std::vector<int>> &edges, int n, int s) { return solution1(edges, n, s); }
};