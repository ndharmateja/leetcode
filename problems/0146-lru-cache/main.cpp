#include <unordered_map>

class LRUCache
{
private:
    struct Node
    {
        int key;
        int val;
        Node *prev;
        Node *next;
        Node() : key{0}, val{0}, prev{nullptr}, next{nullptr} {}
        Node(int key, int val) : key{key}, val{val}, prev(nullptr), next(nullptr) {}
    };
    Node *head_sentinel;
    Node *tail_sentinel;
    int capacity;
    std::unordered_map<int, Node *> key_to_node_map;

    /**
     * Deletes a node given its pointer from the DLL
     * We can assume that nodes exist before and after this node
     * as we are using sentinel nodes
     */
    static void delete_node(Node *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    /**
     * Inserts node pointed by to_insert before the node
     * pointed by node
     * We can assume that node->prev is not null as we
     * are using sentinel nodes
     */
    static void insert_before(Node *node, Node *to_insert)
    {
        to_insert->next = node;
        to_insert->prev = node->prev;
        to_insert->prev->next = to_insert;
        to_insert->next->prev = to_insert;
    }

    void move_last(Node *node)
    {
        // If the node is already at the end, we don't need to do anything
        if (node->next == this->tail_sentinel)
            return;

        delete_node(node);
        insert_before(this->tail_sentinel, node);
    }

public:
    // We are using a DLL
    // The invariant is that the nodes are organized in the order of
    // recency of use. The right most being the most recently used
    // and the left most being the least recently used.
    // So if a key is accessed, to maintain the invariant, we remove
    // the node and insert it at the end as it becomes the most recently used.
    // Invariant is still maintained as the relative ordering of the
    // remaining nodes is not changed
    // The unordered map maps the keys to the Nodes in the DLL for Theta(1) access
    LRUCache(int capacity) : capacity{capacity}, key_to_node_map{static_cast<size_t>(capacity)}
    {
        this->head_sentinel = new Node();
        this->tail_sentinel = new Node();
        this->head_sentinel->next = this->tail_sentinel;
        this->tail_sentinel->prev = this->head_sentinel;
    }

    ~LRUCache()
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
        // Since we are getting value corresponding to this key
        // this key becomes the most recently used
        // So we remove it and add it at the end
        if (this->key_to_node_map.count(key))
        {
            Node *node = this->key_to_node_map.at(key);
            move_last(node);
            return node->val;
        }
        return -1;
    }

    void put(int key, int value)
    {
        // If key is already present, update the value
        // and make it most recently used
        if (this->key_to_node_map.count(key))
        {
            Node *node = this->key_to_node_map.at(key);
            node->val = value;
            move_last(node);
            return;
        }

        // At this point they key is not already present
        // so we create the node corresponding to this key and value
        // and insert it at the end of the list as it is the most recently used

        // If the cache is full, we remove the least recently used node
        // which is the first node from the DLL
        // and also from the map and decrement size
        // We are removing first before inserting the new node because
        // we reserved the capacity of the unordered_map as the capacity itself
        // If we insert first and then delete, the #elements in the map
        // will be capacity + 1
        if (key_to_node_map.size() == capacity)
        {
            // Delete the least recently used node from the DLL
            Node *to_delete = this->head_sentinel->next;
            delete_node(to_delete);

            // Delete the node from heap
            int key_to_delete = to_delete->key;
            delete to_delete;

            // Delete the key from the map
            this->key_to_node_map.erase(key_to_delete);
        }

        // Create node and insert it into the DLL and add the map entry
        // and increment the size
        Node *node = new Node{key, value};
        insert_before(this->tail_sentinel, node);
        this->key_to_node_map[key] = node;
    }
};