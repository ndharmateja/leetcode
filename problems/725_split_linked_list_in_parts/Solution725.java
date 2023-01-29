class Solution725 {
    static class ListNode {
        int val;
        ListNode next;

        ListNode() {
        }

        ListNode(int val) {
            this.val = val;
        }

        ListNode(int val, ListNode next) {
            this.val = val;
            this.next = next;
        }
    }

    private int getListSize(ListNode head) {
        ListNode curr = head;
        int size = 0;
        while (curr != null) {
            size++;
            curr = curr.next;
        }
        return size;
    }

    // for each i from startIndex to endIndex for the output array
    // For each iteration takes "partSize" nodes from the original list
    // and puts it in the array index i
    private ListNode process(ListNode curr, int partSize, int startIndex, int endIndex, ListNode[] output) {
        for (int i = startIndex; i <= endIndex; i++) {
            // If we reach null, that means we reached the end of the original list
            // so all the remaining elements of the array should be null
            // and they are null by default, so we return
            if (curr == null) {
                return null;
            }

            // We use prev pointer
            // because for each part in the array,
            // the last node should point to null
            ListNode prev = null;

            // Assign the curr as the head of the curr part
            output[i] = curr;

            // Iterate partSize number of times
            // All the nodes are already linked to each other
            // we just have to point the last node to null
            // and store the next unprocessed node (head of the
            // next part) in curr for the next part in next iteration
            for (int j = 0; j < partSize; j++) {
                prev = curr;
                curr = curr.next;
            }
            prev.next = null;
        }

        // We return the next unprocessed node
        // to handle the right part of the list
        return curr;
    }

    public ListNode[] splitListToParts(ListNode head, int k) {
        // Size of the linked list
        int size = getListSize(head);

        // let size = 20, k = 6
        // then parts will be 4, 4, 3, 3, 3, 3
        // partLeftSize = 4, numPartsLeft = 2
        // partRightSize = 3, numPartsRight = 3
        //
        // let size = 3, k = 5
        // then parts will be 1, 1, 1, 0, 0
        // partLeftSize = 1, numPartsLeft = 3
        // partRightSize = 0, numPartsRight = 2
        int partSizeRight = size / k;
        int partSizeLeft = partSizeRight + 1;
        int numPartsLeft = size % k;

        // Array for storing the output
        ListNode[] output = new ListNode[k];

        // Process all the left parts
        // and then the right parts
        ListNode curr = head;
        curr = process(curr, partSizeLeft, 0, numPartsLeft - 1, output);
        process(curr, partSizeRight, numPartsLeft, k - 1, output);

        // Return output
        return output;
    }
}