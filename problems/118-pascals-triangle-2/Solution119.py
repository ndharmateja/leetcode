from typing import List


class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        prev_list = [1]
        curr_list = prev_list
        for _ in range(numRows):
            curr_list = [1]

            for j in range(len(prev_list) - 1):
                curr_list.append(prev_list[j] + prev_list[j + 1])

            curr_list.append(1)
            prev_list = curr_list

        return curr_list
