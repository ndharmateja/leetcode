from typing import List


class Solution452:
    def is_valid_intersection(self, intersection):
        return intersection[0] <= intersection[1]

    def findMinArrowShots(self, points: List[List[int]]) -> int:
        points = sorted(points, key=lambda point: point[0])

        num_intersections = 0
        curr_intersection = points[0]

        for point in points:
            curr_intersection = [max(curr_intersection[0], point[0]), min(
                curr_intersection[1], point[1])]
            if not self.is_valid_intersection(curr_intersection):
                curr_intersection = point
                num_intersections += 1

        if self.is_valid_intersection(curr_intersection):
            num_intersections += 1

        return num_intersections
