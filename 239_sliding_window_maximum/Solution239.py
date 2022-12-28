from collections import deque
from typing import List


class Solution239:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        outputs = []

        # we store the indices
        queue = deque()

        # start and end indices of the sliding window (inclusive)
        start = end = 0

        while end < len(nums):
            # Remove all elements on right that are smaller than the current value
            while len(queue) > 0 and nums[queue[-1]] < nums[end]:
                queue.pop()

            # Add new value to queue
            queue.append(end)

            # Remove left most value if out of bounds
            if (queue[0] < start):
                queue.popleft()

            if end + 1 >= k:
                start += 1
                outputs.append(nums[queue[0]])

            end += 1

        return outputs