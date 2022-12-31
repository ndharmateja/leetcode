from typing import List

# Extending 15_three_sum solution to find all the four_sums


class Solution18:

    # O(n^2) time to find all three_sums
    def three_sum(self, nums: List[int], start_index: int, target: int):
        output = []
        for i in range(start_index, len(nums)):
            if i > start_index and nums[i] == nums[i - 1]:
                continue

            l = i + 1
            r = len(nums) - 1
            num = nums[i]
            target_two_sum = target - num

            while l < r:
                if nums[l] + nums[r] < target_two_sum:
                    l += 1
                elif nums[l] + nums[r] > target_two_sum:
                    r -= 1
                else:
                    output.append([num, nums[l], nums[r]])
                    l += 1
                    while nums[l] == nums[l - 1] and l < r:
                        l += 1

        return output

    # O(n^3) time
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        output = []
        nums.sort()

        for i in range(0, len(nums) - 3):
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            three_sum_lists = self.three_sum(nums, i + 1, target - nums[i])
            for three_sum_list in three_sum_lists:
                three_sum_list.insert(0, nums[i])
                output.append(three_sum_list)

        return output
