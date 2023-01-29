from typing import List


class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        output = [[1]]
        for i in range(numRows - 1):
            new_list = [1]

            last_list = output[-1]
            for j in range(len(last_list) - 1):
                new_list.append(last_list[j] + last_list[j + 1])

            new_list.append(1)
            output.append(new_list)

        return output
