from typing import List


class Solution:
    def __init__(self):
        self.memo = {0: 0, 1: float('inf'), 2: 1, 3: 1}

    def get_min_rounds(self, task_count):
        if task_count not in self.memo:
            self.memo[task_count] = min(self.get_min_rounds(
                task_count - 2), self.get_min_rounds(task_count - 3)) + 1
        return self.memo[task_count]

    def minimumRounds(self, tasks: List[int]) -> int:
        counts = {}
        for task in tasks:
            counts[task] = counts.get(task, 0) + 1

        total_rounds = 0
        for task_count in counts.values():
            if task_count == 1:
                return -1
            total_rounds += self.get_min_rounds(task_count)

        return total_rounds
