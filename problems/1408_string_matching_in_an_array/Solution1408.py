from typing import List


class Solution1408:
    def stringMatching(self, words: List[str]) -> List[str]:
        output_set = set()
        for i in range(len(words)):
            for j in range(len(words)):
                if i == j:
                    continue
                if words[i] in output_set:
                    break
                if words[i] in words[j]:
                    output_set.add(words[i])
        return list(output_set)