from typing import List


class Solution56:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals = sorted(intervals, key=lambda point: point[0])

        unions = []
        curr_union = intervals[0]

        for interval in intervals:
            if curr_union[1] >= interval[0]:
                curr_union = [curr_union[0], max(curr_union[1], interval[1])]
            else:
                unions.append(curr_union)
                curr_union = interval
        unions.append(curr_union)

        return unions
