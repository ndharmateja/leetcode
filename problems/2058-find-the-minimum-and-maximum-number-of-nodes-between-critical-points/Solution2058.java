class Solution2058 {
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

    // Checks if 'node' is a critical point
    // 'prev' is not null
    private boolean isCriticalPoint(ListNode node, ListNode prev) {
        if (node.next == null)
            return false;
        return (node.val > prev.val && node.val > node.next.val) || (node.val < prev.val && node.val < node.next.val);
    }

    // O(n) time and O(1) space solution
    public int[] nodesBetweenCriticalPoints(ListNode head) {
        int firstCriticalPointIndex = -1;
        int currCriticalPointIndex = -1;
        int minCriticalPointsDistance = Integer.MAX_VALUE;

        ListNode prev = head;
        ListNode curr = head.next;
        int i = 1;
        while (curr.next != null) {
            if (isCriticalPoint(curr, prev)) {
                // Check if first critical point
                if (firstCriticalPointIndex == -1) {
                    firstCriticalPointIndex = i;
                    currCriticalPointIndex = i;
                }
                // Otherwise calculate the distance to the previous
                // critical point and update min distance accordingly
                else {
                    minCriticalPointsDistance = Math.min(minCriticalPointsDistance, i - currCriticalPointIndex);
                    currCriticalPointIndex = i;
                }
            }
            prev = curr;
            curr = curr.next;
            i++;
        }

        // If no critical points are found
        // or if only one critical point is found
        if (firstCriticalPointIndex == currCriticalPointIndex)
            return new int[] { -1, -1 };

        return new int[] { minCriticalPointsDistance, currCriticalPointIndex - firstCriticalPointIndex };

    }
}