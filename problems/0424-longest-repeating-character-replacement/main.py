from collections import defaultdict

class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        char_counts = defaultdict(int)
        count_to_char_map = defaultdict(set)
        start = 0
        end = 1
        result = 1
        n = len(s)

        max_count = 1
        char_counts[s[0]] = 1
        count_to_char_map[1].add(s[0])

        # Invariant: At any point, the window has the property 
        # that we could form the result with the window length
        # by replacing <= k chars
        while end < n:
            # Add the char at end to the window
            c = s[end]
            end += 1
            new_count = char_counts[c] + 1
            char_counts[c] = new_count
            count_to_char_map[new_count - 1].discard(c)
            count_to_char_map[new_count].add(c)
            if new_count > max_count:
                max_count = new_count

            # Check invariant
            # If invariant is satisfied, record the result
            if max_count >= (end - start) - k:
                result = max(result, end - start)
                continue

            # If invariant is not satisfied, keep removing chars
            # from the start until it is satisfied
            while True:
                c = s[start]
                start += 1

                new_count = char_counts[c] - 1
                char_counts[c] = new_count
                count_to_char_map[new_count + 1].discard(c)
                count_to_char_map[new_count].add(c)

                if not count_to_char_map[max_count]:
                    max_count = new_count

                if max_count >= (end - start) - k:
                    break

            result = max(result, end - start)

        return result