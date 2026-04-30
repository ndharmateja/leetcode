/**
 * Highlights: Custom IndexMinPQ implementation, space optimization using IndexMinPQ
 */

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
     * Computes the Manhattan distance between points u and v
     */
    static int dist_between(const std::vector<std::vector<int>> &points, int u, int v)
    {
        int xu = points[u][0];
        int yu = points[u][1];
        int xv = points[v][0];
        int yv = points[v][1];
        return std::abs(xu - xv) + std::abs(yu - yv);
    }

    /**
     * Prim's Algorithm
     *
     * See problem 743 for more details, as this is very similar to the Dijkstra's implementation
     * that was used in problem 743
     *
     * Prim's is better than Kruskal's for this problem as E = Theta(V^2) and we would need the
     * sorted edge list => Theta(V^2) space and Theta(V^2 log(V^2)) = Theta(V^2 log(V)) time
     */
    static int solution1(const std::vector<std::vector<int>> &points)
    {
        // Initialize the data structures
        int n{static_cast<int>(points.size())}, mst_wt{0};
        std::vector<bool> visited(n, false);
        std::vector<int> dist_to(n, POS_INF);
        IndexMinPQ<int> pq{n};

        // Start Prim's from index 0 (this is arbitrary as we can start from any vertex)
        dist_to[0] = 0;
        pq.insert(0, 0);

        // Prim's main loop
        while (!pq.empty())
        {
            // Remove the minimal node and that edge is going to be in the MST
            // so we add it to the mst_wt and also mark this visited
            int u = pq.remove_min();
            mst_wt += dist_to[u];
            visited[u] = true;

            // For each of the unvisited neighbours (that is all the points
            // that aren't u itself and that haven't been visited)
            for (int v = 0; v < n; v++)
            {
                if (v == u || visited[v])
                    continue;

                // The new distance of v is the edge weight (u, v) which is simply
                // the Manhattan distance between them
                int new_dist = dist_between(points, u, v);

                // If this is new distance is smaller, we update v's distance in the dist_to
                // and in the priority queue
                if (new_dist < dist_to[v])
                {
                    dist_to[v] = new_dist;
                    if (pq.contains(v))
                        pq.change(v, new_dist);
                    else
                        pq.insert(v, new_dist);
                }
            }
        }

        // Return the MST weight
        return mst_wt;
    }

public:
    int minCostConnectPoints(const std::vector<std::vector<int>> &points) { return solution1(points); }
};