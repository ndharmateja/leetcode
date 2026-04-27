#include <vector>
#include <utility>
#include <unordered_map>

struct Node
{
    int key;
    int val;
    int freq;
    Node *prev;
    Node *next;
    Node() : key{0}, val{0}, freq{0}, prev{nullptr}, next{nullptr} {}
    Node(int key, int val) : key{key}, val{val}, freq{1}, prev(nullptr), next(nullptr) {}
};

class LFUCache
{
private:
    int capacity;
    std::unordered_map<int, Node *> key_to_node_map;
    std::vector<std::pair<Node *, Node *>> frequency_ranges;
    Node *head_sentinel;
    Node *tail_sentinel;

    // Helper methods
    static void insert_after(Node *node, Node *to_insert)
    {
        to_insert->prev = node;
        to_insert->next = node->next;
        to_insert->next->prev = to_insert;
        to_insert->prev->next = to_insert;
    }

    static void insert_before(Node *node, Node *to_insert)
    {
        to_insert->prev = node->prev;
        to_insert->next = node;
        to_insert->next->prev = to_insert;
        to_insert->prev->next = to_insert;
    }

    static void remove(Node *node)
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    void increment_frequency(Node *node)
    {
        // Get frequencies
        int old_frequency = node->freq;
        int new_frequency = old_frequency + 1;

        // Store the node after which the node should be inserted
        // This is very important as the pointers of the frequency ranges keep getting updated
        // So we are cleanly updating the frequency ranges first
        // But we are also storing after which node we need to insert the node
        // We need to insert the node after old_frequency_last_node as that is effectively
        // moving it to the first of the next frequency range
        // And we don't need to move anything if the node was already the last node
        // of the frequency range which is a check we perform before removing and inserting
        Node *old_frequency_last_node = frequency_ranges[old_frequency].second;

        /* Update the new_frequency range */
        // Case 1: The old_frequency range is the highest frequency in the vector
        // So we create a new element for the new frequency range
        if (static_cast<int>(frequency_ranges.size()) == new_frequency)
            frequency_ranges.push_back({node, node});

        // Case 2: The new_frequency range is empty as there are no elements in that
        // range. So we create a new range
        else if (!frequency_ranges[new_frequency].first)
            frequency_ranges[new_frequency] = {node, node};

        // Case 3: The new_frequency range is non-empty, so we update the start of the
        // range of the new frequency with this new node
        else
            frequency_ranges[new_frequency].first = node;

        /* Update the old frequency range */
        // Case 1: If the old frequency range had just the one element that range will now be empty
        if (frequency_ranges[old_frequency].first == frequency_ranges[old_frequency].second)
            frequency_ranges[old_frequency] = {nullptr, nullptr};

        // Case 2 and 3: We only need to update the range of the old frequency if the given node is
        // either the start or end of the range
        else if (frequency_ranges[old_frequency].first == node)
            frequency_ranges[old_frequency].first = frequency_ranges[old_frequency].first->next;
        else if (frequency_ranges[old_frequency].second == node)
            frequency_ranges[old_frequency].second = frequency_ranges[old_frequency].second->prev;

        /* Increment the frequency of the node and move it in the DLL */
        // We have to move the node to the end of the current frequency range
        // as it puts it at the start of the start of the next frequency range
        // as for each frequency range we are storing the nodes from left to right
        // as the most recently used to least recently used
        // We only need to move it if it is already not at the end
        node->freq++;
        if (old_frequency_last_node != node)
        {
            remove(node);
            insert_after(old_frequency_last_node, node);
        }
    }

    void delete_node_with_least_frequency()
    {
        // We have to delete the right most node of the left most range
        // We have to first get the node to delete and then update the frequency range
        int min_frequency = head_sentinel->next->freq;
        Node *to_delete = frequency_ranges[min_frequency].second;

        // Update the frequency range
        if (frequency_ranges[min_frequency].first == frequency_ranges[min_frequency].second)
            frequency_ranges[min_frequency] = {nullptr, nullptr};
        else
            frequency_ranges[min_frequency].second = frequency_ranges[min_frequency].second->prev;

        // Remove the key from the hash map
        key_to_node_map.erase(to_delete->key);

        // Remove the node from the list and delete it
        remove(to_delete);
        delete to_delete;
    }

public:
    LFUCache(int capacity) : capacity{capacity}, key_to_node_map(static_cast<size_t>(capacity))
    {
        // Initialize the dll with the sentinel nodes
        this->head_sentinel = new Node();
        this->tail_sentinel = new Node();
        this->head_sentinel->next = this->tail_sentinel;
        this->tail_sentinel->prev = this->head_sentinel;

        // Frequency of 0 won't have any range of nodes
        this->frequency_ranges.push_back({nullptr, nullptr});
        this->frequency_ranges.push_back({nullptr, nullptr});
    }

    // Destructor to delete all the nodes of the dll on the heap
    ~LFUCache()
    {
        Node *curr = this->head_sentinel;
        while (curr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
    }

    int get(int key)
    {
        // See if the key is present in the map
        auto it = key_to_node_map.find(key);

        // If the key is not present we can return -1
        if (it == key_to_node_map.end())
            return -1;

        // If key is present, we increase its frequency by 1 and insert it in the appropriate range
        Node *node = it->second;

        // Move the node to the start of the range of the updated frequency
        // and update the frequency ranges
        increment_frequency(node);

        // Return the value corresponding to the node
        return node->val;
    }

    void put(int key, int value)
    {
        // See if key already exists in map, otherwise insert it
        // We can get away with one hash using try_emplace
        auto [it, inserted] = key_to_node_map.try_emplace(key, nullptr);

        // If we the key already exists, then we need to simply update the value
        // and move the node to the next frequency range
        if (!inserted)
        {
            // Get the corresponding node and update its value
            // and move it to the next frequency range
            Node *node = it->second;
            node->val = value;
            increment_frequency(node);
            return;
        }

        // Delete the node with the smallest frequency
        // We shouldn't do this step after the insertion of the new node
        // as that new node could be immediately deleted
        if (static_cast<int>(key_to_node_map.size()) > capacity)
            delete_node_with_least_frequency();

        // If the key didn't already exist, we have to insert a new node
        Node *new_node = new Node(key, value);
        it->second = new_node;

        // Insert the new node at the start of range of frequency 1
        // which is equivalent to inserting at the head of the dll
        insert_after(head_sentinel, new_node);

        // Update the frequency range of 1
        // If the end of the frequency range is nullptr, it means that
        // this is the only node in the range. so the range becomes
        // {new_node, new_node}
        frequency_ranges[1].first = new_node;
        if (!frequency_ranges[1].second)
            frequency_ranges[1].second = new_node;
    }
};